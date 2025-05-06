#include <omp.h>
#include <algorithm>

void heapifyParallel(int* arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;
    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapifyParallel(arr, n, largest);
    }
}

void heapSortParallel(int* arr, int n) {
    #pragma omp parallel for
    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyParallel(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        std::swap(arr[0], arr[i]);
        heapifyParallel(arr, i, 0);
    }
}
