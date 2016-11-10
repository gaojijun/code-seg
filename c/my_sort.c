#include <stdlib.h>
#include <string.h>

/* Exchange the value of two intergers. */
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Insertion sorting algorithm. */
void InsertionSort(int *A, int length){
    int i,j,k,temp;
    for( i=1; i<=length-1; i++ ) {// insert item of A[1...length-1] one by one
        temp = A[i];
        for( j=i-1; j>=0; j-- ) { // compare A[i] with A[i-1...0] one by one
            if( temp < A[j] ){
                A[j+1] = A[j];
            }
            else
                break;
        }
        A[j+1] = temp;
    }
}

void MergeSort(int *A, int length){
    if ( length == 1 ) return;
    if ( length == 2 ) {
        if ( A[0] > A[1]  ) {
            swap(&A[0], &A[1]); 
        }
        return;
    }
    int length1 = length / 2;
    int length2 = (length + 1) / 2;
    int *ap1 = A;
    int *ap2 = A + length1;
    MergeSort(ap1, length1);
    MergeSort(ap2, length2);
    int i, j, k;
    i = 0, j = 0, k = 0;
    int *tempArr = (int *)malloc(length * sizeof(int));
    while ( j <= (length1-1) &&
            k <= (length2-1) ) {
        if ( ap1[j] <= ap2[k] ) { tempArr[i++] = ap1[j++]; }
        else                    { tempArr[i++] = ap2[k++]; } 
    }
    if ( j <= (length1-1) )
        memcpy(tempArr+i, ap1+j, length1-j);
    else
        memcpy(tempArr+i, ap2+k, length2-k);
    memcpy(A, tempArr, length * sizeof(int));
    free(tempArr);
}

void BubbleSort(int *A, int length){
    int i, j;
    for ( i = length-1; i >= 1; i-- ) { // set one item in A[length-1...1] each loop.
        for ( j = 0; j <= i-1; j++ ) {
            if ( A[j] > A[j+1] ) {
                swap(&A[j], &A[j+1]);
            }
        }
    }
}

void SelectionSort(int *A, int length){
    int i, j, max;
    for ( i = length-1; i >= 1; i-- ) { // set one item in A[length-1...1] each loop.
        max = i;
        for ( j = 0; j <= i-1; j++ ) {
            if ( A[j] > A[max] ) {
                max = j;
            }
        }
        swap(&A[max], &A[i]);
    }
}
