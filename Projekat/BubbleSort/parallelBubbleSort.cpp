void bubbleSortParallel(int arr[], int n) {
    bool sorted = false;
    int tmp;
    
    while (!sorted) {
        sorted = true;
        
        #pragma omp parallel private(tmp)
        {
            // Even phase
            #pragma omp for reduction(&&:sorted)
            for (int i = 0; i < n-1; i += 2) {
                if (arr[i] > arr[i+1]) {
                    tmp = arr[i];
                    arr[i] = arr[i+1];
                    arr[i+1] = tmp;
                    sorted = false;
                }
            }
            
            // Odd phase
            #pragma omp for reduction(&&:sorted)
            for (int i = 1; i < n-1; i += 2) {
                if (arr[i] > arr[i+1]) {
                    tmp = arr[i];
                    arr[i] = arr[i+1];
                    arr[i+1] = tmp;
                    sorted = false;
                }
            }
        }
    }
}
