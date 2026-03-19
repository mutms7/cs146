#include <stdio.h>

int binsearch(int A[], int key, int n) {
    int low = 0;
    int high = n - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (key < A[mid]) {
            high = mid - 1;
        } else if (key > A[mid]) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return n;
}

void main() {
    int arr[] = {1, 3, 3, 5, 5, 7, 7, 7, 9, 11, 13};
    printf("%d", binsearch(arr, 4, 11));
}