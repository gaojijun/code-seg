#include <stdio.h>
#include <string.h>
#include "my_sort.c"

void test_swap() {
    int a,b;
    a = 1;
    b = 2;
    swap(&a, &b);
    if ( a == 2 && b == 1)
        printf("swap test passed!\n");
    else
        printf("swap test failed!\n");

}

void test_InsertionSort() {
    int a[6] = {4,2,3,5,1,0}; 
    int b[6] = {0,1,2,3,4,5};
    int i;
    InsertionSort(a, 6);
    if ( memcmp(a, b, sizeof(a)) == 0 )
        printf("Insertion test passed!\n");
    else {
        printf("Insertion test failed!\n");
        for ( i=0; i<6; i++ )
            printf("test_InsertionSort: %d-%d\n", i, a[i]);
    }
}

int main() {
    test_swap();
    test_InsertionSort();
    return 0;
}
