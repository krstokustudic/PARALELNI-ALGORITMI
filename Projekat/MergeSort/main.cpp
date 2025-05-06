#include <iostream>
#include <fstream>
#include <chrono>
#include <omp.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

#include "merge_sekv.cpp"
#include "merge_paralel.cpp"

void generateRandomArray(std::vector<int>& arr, int maxVal = 10000) {
    for (int& x : arr)
        x = rand() % maxVal;
}

void copyArray(const std::vector<int>& src, std::vector<int>& dest) {
    for (size_t i = 0; i < src.size(); ++i)
        dest[i] = src[i];
}

double averageSequentialTime(const std::vector<int>& original, std::vector<int>& buffer, int runs = 5) {
    double total = 0.0;
    for (int i = 0; i < runs; ++i) {
        copyArray(original, buffer);
        auto start = std::chrono::high_resolution_clock::now();
        mergeSort(buffer, 0, buffer.size() - 1); // sekvencijalna verzija
        auto end = std::chrono::high_resolution_clock::now();
        total += std::chrono::duration<double>(end - start).count();
    }
    return total / runs;
}

double averageParallelTime(const std::vector<int>& original, std::vector<int>& buffer, int threads, int runs = 5) {
    double total = 0.0;
    omp_set_num_threads(threads);
    for (int i = 0; i < runs; ++i) {
        copyArray(original, buffer);
        double start = omp_get_wtime();
        #pragma omp parallel
        {
            #pragma omp single
            parallelMergeSort(buffer, 0, buffer.size() - 1);
        }
        double end = omp_get_wtime();
        total += (end - start);
    }
    return total / runs;
}

int main() {
    std::srand(static_cast<unsigned>(time(nullptr)));

    std::vector<int> n_values = {1000, 5000, 10000, 20000};
    std::vector<int> thread_values = {1, 2, 4, 8};

    std::ofstream out("MergeSortResults.csv");
    out << std::fixed << std::setprecision(6);
    out << "n;threads;seq_time;par_time;speedup;efficiency;cost\n";

    for (int n : n_values) {
        std::vector<int> original(n);
        std::vector<int> seq_arr(n);
        std::vector<int> par_arr(n);

        generateRandomArray(original);

        double seq_time = averageSequentialTime(original, seq_arr);

        for (int threads : thread_values) {
            double par_time = averageParallelTime(original, par_arr, threads);

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
    }

    out.close();
    std::cout << "\nRezultati su sačuvani u 'MergeSortResults.csv'\n";
    return 0;
}
