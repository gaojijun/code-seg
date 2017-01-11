// http://hihocoder.com/problemset/problem/1015
// Key word: KMP algorithm

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void compute_PI(int *PI, char *P, int m) {
    int k, q;

    PI[1] = 0;
    k=0;

    for ( q=2; q<=m; q++ ) {
        while ( k > 0 && P[k] != P[q-1] )
            k = PI[k];
        if ( P[k] == P[q-1] )
            k++;
        PI[q] = k;
    }
}

void kmp(char *T, char *P) {
    int m, k;
    int *PI;
    long int n, i, c;

    n = strlen(T);
    m = strlen(P);
    k = 0;
    c = 0;
    PI = (int *)malloc(sizeof(int)*(m+1));
    compute_PI(PI, P, m);

    for ( i=0; i<n; i++ ) {
        while ( k>0 && P[k] != T[i] )
            k = PI[k];
        if ( P[k] == T[i] )
            k++;
        if ( k == m ) {
            c++;   
            k = PI[m];
        }
    }
    printf("%ld\n", c); 
}



main(){
    int N;
    char P[10001], T[1000001];

    scanf("%d", &N);

    while ( N-- ) {
        scanf("%s%s", P, T); 
        kmp(T, P);
    }

    return 0;
}
