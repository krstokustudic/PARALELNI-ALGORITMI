#include <iostream>
#include <vector>
#include <omp.h>
#include <cstdlib>


void parallelInsertionSort(std::vector<int>& arr) {
    int n = arr.size();

    #pragma omp parallel for default(none) shared(arr, n)
    for (int i = 1; i < n; ++i) {
        int key, j;

        // Prvo uzmi ključ (mora izvan kritične sekcije)
        #pragma omp critical
        {
            key = arr[i];
            j = i - 1;
        }

        // Premještanje elemenata koji su veći od ključa
        while (j >= 0) {
            int temp;
            #pragma omp critical
            {
                temp = arr[j];
            }

            if (temp > key) {
                #pragma omp critical
                {
                    arr[j + 1] = temp;
                }
                j--;
            } else {
                break;
            }
        }

        #pragma omp critical
        {
            arr[j + 1] = key;
        }
    }
}
