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
