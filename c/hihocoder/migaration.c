// http://hihocoder.com/problemset/problem/1053
// Key words: binary search, qsort on structures.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define setMax(max, x) if ( x>max ) max = x
#define min(x, y) ( (x) < (y) ? (x) : (y) )
#define max(x, y) ( (x) > (y) ? (x) : (y) )
#define MAXRES 100000

typedef struct Resident{
    long int people;
    int xy;
}Res;
int R;
long int mh[MAXRES], ma[MAXRES];

int cmp(const void *a, const void *b){
    return (*((Res **)a))->xy - (*((Res **)b))->xy;
}

int isOK(int x, int N, Res *res[]){
    Res *r;
    int i, j=0;
    long int n, d, t;
    memset(mh, 0, sizeof(long int)*N);
    memset(ma, 0, sizeof(long int)*N);
    for ( i=0; i<N; i++ ) {
        r = res[i];
        n = r->people + mh[i] - ma[i];
        if ( (d=n-x) == 0 ) continue;
        else if ( d > 0 ) {
            if ( i+1<N && res[i]->xy == res[i+1]->xy ) {
                mh[j] += d;
                continue;
            }
            for ( j=max(i+1, j); j<N && (res[j]->xy - res[i]->xy) <= R; j++ ) {
                if ( mh[j] < x ) {
                    t = min(d, x-mh[j]);
                    d -= t;
                    mh[j] += t;
                    if ( d==0 ) break;
                }
            } 
            if ( d>0 ) return 0;
        } else {
            d=x-n;
            for ( j=max(i+1, j); j<N && (res[j]->xy - res[i]->xy) <= R; j++ ) {
                t = min(d, res[j]->people - ma[j]);
                d -= t;
                ma[j] += t;
                if ( d==0 ) break;
            }
        }
    }
    return 1;
}

void process(int h, int l, int N, Res *res[]){
    int m;
    while ( l<h ) {
        m = (l+h)/2;
        if ( isOK(m, N, res) ) h = m;
        else l = m+1;
    }
    printf("%d\n", l);
}

int main(){
    int T, h, l, N, i;
    long int total;
    scanf("%d", &T);
    Res *res[MAXRES], data[MAXRES];
    while(T--){
        scanf("%d%d", &N, &R);
        total = 0;
        h = 0;
        for ( i=0; i<N; i++ ) {
            res[i] = &data[i];
            scanf("%d%ld", &res[i]->xy, &res[i]->people);
            total += res[i]->people;
            setMax(h, res[i]->people);
        }
        qsort(res, N, sizeof(Res *), cmp);
        l = total / N;
        if ( total % N ) l += 1;
        process(h, l, N, res);
    }
    return 0;
}
