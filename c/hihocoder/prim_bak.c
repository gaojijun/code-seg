// http://hihocoder.com/problemset/problem/1097
// Key word: minimum spanning trees, Prim's algorithm

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Road{
    int s, e;
    int distance;
}Road, *RP;

typedef Road elemtype;
typedef struct PrioQueue{
    int len;
    int size;
    int (*cmp)(void *, void *);
    elemtype **data;
}PrioQ;

PrioQ *makePrioQ(int queueSize, int (*cmp)(void *, void *)) {
    PrioQ *q = (PrioQ *)malloc(sizeof(PrioQ));
    q->data = (elemtype **)malloc(sizeof(elemtype*)*queueSize);
    q->size = queueSize;
    q->len = 0;
    q->cmp = cmp;
    return q;
}

void heapAdjust(elemtype **A, int n, int p, int (*cmp)(void *, void *)) {
    int i, l;
    elemtype *a=A[p];
    for ( i=p; (l=2*i+1)<n; i=l ) {
        if ( l+1 < n && (*cmp)(A[l+1], A[l]) < 0 )
            l = l+1;
        if ( (*cmp)(A[l], a) < 0 )
            A[i] = A[l];
        else break;
    }
    A[i] = a;
}

void heapAppend(elemtype **A, int n, elemtype *a, int (*cmp)(void *, void *)) {
    int i, p;
    for ( i=n, p=(i-1)/2; i>0; i=p, p=(i-1)/2 ) {
        if ( (*cmp)(A[p], a) > 0 )
            A[i] = A[p];
        else break;
    }
    A[i] = a;
}

int enPrioQ(PrioQ *q, elemtype *a) {
    if ( q->len == q->size )
        return EOF;
    heapAppend(q->data, q->len, a, q->cmp);
    q->len++;
    return 0;
}

elemtype *dePrioQ(PrioQ *q) {
    if ( q->len == 0 )
        return NULL;
    elemtype *a = q->data[0];
    q->data[0] = q->data[q->len-1];
    heapAdjust(q->data, --q->len, 0, q->cmp);
    return a;
}

void deletePrioQ(PrioQ *q) {
    elemtype *e;
    while ( (e=dePrioQ(q)) != NULL ) {
        free(e);
    }
    free(q->data);
    free(q);
}

int roadcmp(void *a, void *b) {
    return ((RP)a)->distance - ((RP)b)->distance;
}

RP makeR(int s, int e, int distance){
    RP r = (RP)malloc(sizeof(Road));
    r->s = s;
    r->e = e;
    r->distance = distance;
    return r;
}

void getData(PrioQ *p, PrioQ *rq, char *A){
    RP r;
    while ( (r=dePrioQ(rq)) != NULL && A[r->e] )
        free(r);
    if ( r != NULL ) 
        enPrioQ(p, r);
}

void process(PrioQ *roads[], int N){
    int ans=0, e, s;
    char *A = calloc(N, sizeof(char));
    A[0] = 1;
    PrioQ *p = makePrioQ(N-1, roadcmp);
    RP r;
    enPrioQ(p, dePrioQ(roads[0]));
    while ( --N ) {
        r = dePrioQ(p);
        e = r->e;
        s = r->s;
        if ( A[e] ) N++;
        else {
            A[e] = 1;
            ans += r->distance;
            getData(p, roads[e], A);
        }
        free(r);
        getData(p, roads[s], A);
    }
    printf("%d\n", ans);
}

int main(){
    int N, i, j, d;
    scanf("%d", &N);
    if ( !N ) {
        printf("0\n");
        return 0;
    }
    PrioQ *roads[N];
    for ( i=0; i<N; i++ ) {
         roads[i] = makePrioQ(N-1, roadcmp);
         for ( j=0; j<N; j++ ) {
             scanf("%d", &d);
             if ( j==i ) continue;
             enPrioQ(roads[i], makeR(i,j,d));
         }
    }
    process(roads, N);

    for ( i=0; i<N; i++ ) {
        deletePrioQ(roads[i]);
    }
    return 0;
}
