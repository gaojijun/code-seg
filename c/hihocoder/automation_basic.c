// http://hihocoder.com/problemset/problem/1441
// Key word: KMP algorithm, suffix automation(SAM)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTR 51

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

int kmp(char *T, char *P, int endpos[]) {
    int m, k;
    int *PI;
    int n, i, c;

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
            endpos[c++] = i;
            k = PI[m];
        }
    }
    return c;
}

void shortest(char *T, char *P, int count) {
    char *p;
    int endpos[MAXSTR];
    for ( p=P+1; *p!='\0'; p++ )
        if ( kmp(T, p, endpos) > count ) break;
    printf("%s ", p-1);
}

void longest(char *T, char *P, int *endpos, int count) {
    int i, j, t, m=strlen(P);
    for ( i=1; i<=endpos[0]-m+1; i++ ) {
        t = m-1+i;
        for ( j=0; j<count-1; j++ ) {
            if ( T[endpos[j]-t] != T[endpos[j+1]-t] ) break;
        }
        if ( j<count-1) break;
    }
    i--;
    int longest_start = endpos[0]-(m-1+i);
    for ( j=0; j<i; j++ )
        printf("%c", T[longest_start+j]);
    printf("%s ", P);
}

main(){
    int N, endpos[MAXSTR], count, i;
    char P[MAXSTR], T[MAXSTR];

    scanf("%s%d", T, &N);
    while ( N-- ) {
        scanf("%s", P); 
        count = kmp(T, P, endpos);
        shortest(T, P, count);
        longest(T, P, endpos, count);
        for ( i=0; i<count-1; i++ )
            printf("%d ", endpos[i]+1);
        printf("%d\n", endpos[i]+1);
    }

    return 0;
}
