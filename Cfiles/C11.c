#include <stdio.h>

int lowsearch(int A[], int key, int n) {
    //assume: A[0] <= key <= A[n-1]
    int low = 0;
    int high = n-1;
    if (A[n-1] < key) {
        return n;
    }
    // low = 0, high = n
    // let i be the minimum index such that key <= A[i]

    while (low < high) {
        // loop invariant: low(before) <= i <= high(before) -> low(after) <= i <= high(after)
        int mid = (low + high) / 2;
        // mid = (low+high)/2, low <= mid < high
        if (key < A[mid]) {
            // key < A[mid] -> 
            // i < mid -> 
            // i <= mid-1
            high = mid - 1;
            // low <= i <= high (mid-1)
        } else if (key > A[mid]) {
            // key > A[mid] -> 
            // i > mid -> 
            // i >= mid+1
            low = mid + 1;
            // low (mid+1) <= i <= high
        } else {
            // key = A[mid] -> 
            // i <= mid
            high = mid;
            // low <= i <= high (mid)
        }
    }
    // low <= i <= high AND low = high
    // therefore low = i

    return low;
}

void main() {
    int arr[] = {1, 1, 3, 3, 4, 4, 6};
    printf("\n%d\n", lowsearch(arr, 6, 7));
}