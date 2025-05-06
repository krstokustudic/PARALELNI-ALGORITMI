#include <iostream>
#include <vector>
#include <omp.h>

void mergeParalel(std::vector<int>& arr, int left, int mid, int right) {
    std::vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while(i <= mid && j <= right) {
        if(arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while(i <= mid) temp[k++] = arr[i++];
    while(j <= right) temp[k++] = arr[j++];

    for(int t = 0; t < temp.size(); ++t)
        arr[left + t] = temp[t];
}

void parallelMergeSort(std::vector<int>& arr, int left, int right, int depth = 0) {
    if(left >= right) return;

    int mid = left + (right - left) / 2;

    if(depth <= 4) { // ograničimo dubinu paralelizacije da se izbjegne previše niti
        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMergeSort(arr, left, mid, depth + 1);
            
            #pragma omp section
            parallelMergeSort(arr, mid + 1, right, depth + 1);
        }
    } else {
        parallelMergeSort(arr, left, mid, depth + 1);
        parallelMergeSort(arr, mid + 1, right, depth + 1);
    }

    mergeParalel(arr, left, mid, right);
}
