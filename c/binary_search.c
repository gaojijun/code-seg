#include <stdio.h>

int bin_search(int arr[], int length, int target) {
    int start = 0, end = length - 1;
    int mid;
    while ( start <= end ) {
        mid = (start + end) / 2;
        if ( arr[mid] == target ) {
            return mid;
        } else if ( arr[mid] < target ) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    return -1;
}

int main() {
    int arr[] = {2, 3, 4, 5};
    int a = bin_search(arr, 4, 2);
    int b = bin_search(arr, 4, 3);
    int c = bin_search(arr, 4, 4);
    int d = bin_search(arr, 4, 5);
    int e = bin_search(arr, 4, 6);
    printf("%d\n", a);
    printf("%d\n", b);
    printf("%d\n", c);
    printf("%d\n", d);
    printf("%d\n", e);
    return 0;
}
