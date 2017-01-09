// http://hihocoder.com/problemset/problem/1039
// Key word: doubly linked list

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct linkNode{
    char c;
    struct linkNode *prev, *next;
}LN, *LL;

void append(LL *prev, char c) {
    LL n = (LL)malloc(sizeof(LN));
    n->c = c;
    n->prev = *prev;
    (*prev)->next = n;
    *prev = n;
}

LL buildList(char *A, int i, int n, char c) {
    LL head = (LL)malloc(sizeof(LN)), prev=head;
    head->prev = NULL;
    head->c = A[0];
    int j;
    for ( j=1; j<=i; j++ )
        append(&prev, A[j]);
    append(&prev, c);
    for ( j=i+1; j<n; j++ )
        append(&prev, A[j]);
    prev->next = NULL;
    return head;
}

void freeList(LL head) {
    LL p, pre;
    for ( pre=head; pre; pre=p ) {
        p = pre->next;
        free(pre); 
    }
}

int traverse(LL head) {
    int count = 0, flag;
    LL active = head, p, q;
    while ( active ) {
        for ( p=active, active=NULL; p; p=q ) {
            flag = 0;
            for ( q=p->next; q && q->c == p->c; q=p->next ) {
                p->next = q->next;
                free(q);
                count++;
                flag = 1;
            }
            if ( flag ) {
                if ( q ) q->prev = p->prev;
                p->prev->next = q;
                if ( !active ) active = p->prev;
                free(p);
                count++;
            }
        }
    }
    return count;
}

void process(char *A){
    int n = strlen(A), i, max=0, count;
    char c;
    LL head;
    for ( i=0; i<=n-1; i++ ) {
        for ( c='A'; c<='C'; c++ ) {
            head = buildList(A, i, n, c);
            count = traverse(head);
            if ( count > max ) max = count;
            freeList(head);
        }
    }
    printf("%d\n", max);
}

main() {
    int T;
    scanf("%d", &T);
    char A[102];
    A[0] = '$';
    while ( T-- ) {
        scanf("%s", A+1);
        process(A);
    }
    return 0;
}
