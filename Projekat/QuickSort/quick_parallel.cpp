#include <omp.h>
#include <algorithm>

void quickSortParallel(int* arr, int low, int high, int depth = 0) {
    if (low < high) {
        int pivot = arr[high];
        int i = (low - 1);
        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        int pi = i + 1;

        if (depth <= 3) {
            #pragma omp parallel sections
            {
                #pragma omp section
                quickSortParallel(arr, low, pi - 1, depth + 1);
                #pragma omp section
                quickSortParallel(arr, pi + 1, high, depth + 1);
            }
        } else {
            quickSortParallel(arr, low, pi - 1, depth + 1);
            quickSortParallel(arr, pi + 1, high, depth + 1);
        }
    }
}
