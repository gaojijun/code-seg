// http://hihocoder.com/problemset/problem/1097
// Key word: minimum spanning trees, Prim's algorithm

#include <stdio.h>
#include <string.h>

int main(){
    int N, i, j, ans=0, pre, min, p;
    scanf("%d", &N);
    if ( !N ) { printf("0\n");return 0;}
    int M[N][N], w[N];
    char A[N];
    memset(A, 0, sizeof(char)*N);

    for ( i=0; i<N; i++ ) {
        w[i] = 10000;
        for ( j=0; j<N; j++ )
            scanf("%d", &M[i][j]);
    }

    for ( j=1, pre=0, A[0]=1; j<N; j++, pre=p ) {
        min = 10000;
        for ( i=0; i<N; i++ ) {
            if ( A[i] ) continue;
            if ( M[pre][i] < w[i] ) {
                w[i] = M[pre][i];
            }
            if ( w[i] < min ) {
                min = w[i];
                p = i;
            }
        }
        A[p] = 1;
        ans += min;
    }
    printf("%d\n", ans);
    return 0;
}
