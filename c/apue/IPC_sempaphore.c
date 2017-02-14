#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/stat.h> // S_IRUSR
#include <sys/ipc.h> // IPC_PRIVATE

#define MODE ( S_IRUSR | S_IWUSR )

void unix_error(const char *s) {
    perror(s);
    exit(1);
}

void P(int sem_id) {
    struct sembuf bufs[1], buf = {0, -1, SEM_UNDO};
    bufs[0] = buf;
    if ( semop(sem_id, bufs, 1) < 0 ) {
        unix_error("semop error");
        rm_sem(sem_id);
    }
}

void V(int sem_id) {
    struct sembuf bufs[1], buf = {0, 1, SEM_UNDO};
    bufs[0] = buf;
    if ( semop(sem_id, bufs, 1) < 0 ) {
        unix_error("semop error");
        rm_sem(sem_id);
    }
}

int init_sem() {
    int sem_id;
    if ( ( sem_id = semget(IPC_PRIVATE, 1, MODE) ) < 0 )
        unix_error("semget error");
    union semun{
        int val;
        struct semid_ds *buf;
        unsigned short *array;
    } u;
    u.val = 1;
    semctl(sem_id, 0, SETVAL, u);
    return sem_id;
}

void rm_sem(int sem_id) {
    if ( semctl(sem_id, 0, IPC_RMID) < 0 )
        unix_error("semctl error");
}

int main() {
    int sem_id = init_sem();
    P(sem_id);
    pid_t pid;
    if ( ( pid=fork() ) < 0 )
        unix_error("fork error");
    if ( pid == 0 ) { // child process
        P(sem_id);
        printf("child goes second\n");
    } else {
        sleep(2);
        printf("parent goes first\n");
        V(sem_id);
        sleep(2);
        rm_sem(sem_id);
    }
    return 0;
}
