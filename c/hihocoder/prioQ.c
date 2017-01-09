// Key word: priority queue, minimum heap

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char elemtype;

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

void deletePrioQ(PrioQ *q) {
    free(q->data);
    free(q);
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

int stringcmp(void *a, void *b) {
    return strcmp((char *)a, (char *)b);
}

int _main() {
    char s1[] = "ccc";
    char s2[] = "bbb";
    char s3[] = "aaa";
    PrioQ *q = makePrioQ(5, stringcmp);
    printf("%d\n", enPrioQ(q, s1));
    printf("%d\n", enPrioQ(q, s3));
    printf("%d\n", enPrioQ(q, s2));
    printf("%s\n", dePrioQ(q));
    printf("%s\n", dePrioQ(q));
    printf("%s\n", dePrioQ(q));
    return 0;
}
