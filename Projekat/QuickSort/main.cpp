#include <iostream>
#include <fstream>
#include <chrono>
#include <omp.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

#include "quick_sequential.cpp"
#include "quick_parallel.cpp"

void generateRandomArray(int* arr, int n, int maxVal = 10000) {
    for (int i = 0; i < n; ++i)
        arr[i] = rand() % maxVal;
}

void copyArray(int* src, int* dest, int n) {
    for (int i = 0; i < n; ++i)
        dest[i] = src[i];
}

double averageSequentialTime(int* original, int* buffer, int n, int runs = 5) {
    double total = 0.0;
    for (int i = 0; i < runs; ++i) {
        copyArray(original, buffer, n);
        auto start = std::chrono::high_resolution_clock::now();
        quickSort(buffer, 0, n - 1);
        auto end = std::chrono::high_resolution_clock::now();
        total += std::chrono::duration<double>(end - start).count();
    }
    return total / runs;
}

double averageParallelTime(int* original, int* buffer, int n, int threads, int runs = 5) {
    double total = 0.0;
    omp_set_num_threads(threads);
    for (int i = 0; i < runs; ++i) {
        copyArray(original, buffer, n);
        double start = omp_get_wtime();
        #pragma omp parallel
        {
            #pragma omp single
            quickSortParallel(buffer, 0, n - 1);
        }
        double end = omp_get_wtime();
        total += (end - start);
    }
    return total / runs;
}

int main() {
    std::srand(time(nullptr));

    std::vector<int> n_values = {1000, 5000, 10000, 20000};
    std::vector<int> thread_values = {1, 2, 4, 8};

    std::ofstream out("QuickSortResults.csv");
    out << std::fixed << std::setprecision(6);
    out << "n;threads;seq_time;par_time;speedup;efficiency;cost\n";

    for (int n : n_values) {
        int* original = new int[n];
        int* seq_arr = new int[n];
        int* par_arr = new int[n];

        generateRandomArray(original, n);
        double seq_time = averageSequentialTime(original, seq_arr, n);

        for (int threads : thread_values) {
            double par_time = averageParallelTime(original, par_arr, n, threads);
            double speedup = seq_time / par_time;
            double efficiency = speedup / threads;
            double cost = par_time * threads;
            if (efficiency > 1.0) efficiency = 1.0;

            out << n << ";" << threads << ";" << seq_time << ";" << par_time << ";"
                << speedup << ";" << efficiency << ";" << cost << "\n";

            std::cout << "n=" << n << ", threads=" << threads
                      << " -> speedup=" << speedup
                      << ", efficiency=" << efficiency << ", cost=" << cost << "\n";
        }

        delete[] original;
        delete[] seq_arr;
        delete[] par_arr;
    }

    out.close();
    std::cout << "\nRezultati su sačuvani u 'QuickSortResults.csv'\n";
    return 0;
}
