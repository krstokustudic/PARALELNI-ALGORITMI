void bubbleSort(int arr[], int n) {
    bool sorted = false;
    int tmp;
    
    while (!sorted) {
        sorted = true;
        
        for (int i = 0; i < n-1; ++i) {
            if (arr[i] > arr[i+1]) {
                tmp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = tmp;
                sorted = false;
            }
        }
    }
}
