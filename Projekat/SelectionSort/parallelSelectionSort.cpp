#include <omp.h>
#include <algorithm> 

void selectionSortParallel(int* arr, int n) {
    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;

        #pragma omp parallel
        {
            int local_min_idx = min_idx;

            #pragma omp for nowait
            for (int j = i + 1; j < n; ++j) {
                if (arr[j] < arr[local_min_idx]) {
                    local_min_idx = j;
                }
            }

            #pragma omp critical
            {
                if (arr[local_min_idx] < arr[min_idx]) {
                    min_idx = local_min_idx;
                }
            }
        }

        std::swap(arr[i], arr[min_idx]);
    }
}

