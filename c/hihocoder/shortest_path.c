// http://hihocoder.com/problemset/problem/1081
// Key word: algorithm, shortest path

#include <stdio.h>

#define N 1000
#define INFINITE 100000000
#define setMin(min, a) if ( (a)<(min) ) min=(a)

int M[N+1][N+1], w[N+1], v, visit[N+1];
int start, end, roads, s, e, d, min, mini;
int i, j, p, t, ans=0;

int main() {
    for (i=1;i<=N;i++) {
        for (j=1;j<=N;j++) {
            M[i][j] = INFINITE;
        }
        w[i] = INFINITE;
        visit[i] = 0;
    }
    scanf("%d%d%d%d", &v, &roads, &start, &end);
    while( roads-- ) {
        scanf("%d%d%d", &s, &e, &d);
        setMin(M[s][e], d);
        setMin(M[e][s], d);
    }
    p = start;
    w[p] = 0;
    while ( --v ) {
        visit[p] = 1;
        min = INFINITE;
        for ( i=1;i<=N;i++ ) {
            if ( visit[i] ) continue;
            setMin(w[i], M[p][i]+w[p]);
            if ( w[i] < min ) {
                min = w[i];
                mini = i;
            }
        }
        p = mini;
    }
    printf("%d\n", w[end]);
    return 0;
}
