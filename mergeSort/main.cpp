// Including necessary libraries
#include <fstream>
#include <iostream>
#include <chrono>

// --- BEGIN RETURN CODES ---

#define EXEC_FAILURE 1      // Not enough arguments
#define EXEC_SUCCESS 0      // Execution completed with no errors

#define FILE_IO_ERROR 5     // The algorithm specified has no executable
#define FILEXEC_ERROR 6     // Invalid arguments passed to main

// --- BEGIN CONSTANTS ---

const int MAX_SIZE = 1000001;

// --- END CONSTANTS ---

void swapElements(int* x, int* y) {
    auto temp = *x;

    *x = *y;
    *y = temp;
}

void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays
    int* L = new int[n1];
    int* R = new int[n2];

    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temp arrays back into arr[l..r]

    // Initial index of first subarray
    int i = 0;

    // Initial index of second subarray
    int j = 0;

    // Initial index of merged subarray
    int k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of
    // L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of
    // R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[],int l,int r){
    if(l>=r){
        return;//returns recursively
    }
    int m =l+ (r-l)/2;
    mergeSort(arr,l,m);
    mergeSort(arr,m+1,r);
    merge(arr,l,m,r);
}

// Main Function
int main(int argc, char** argv)
{
    // Modify argument
    char* file_path = argv[1] + 1;

    // Attempt to open file given as parameter
    std::ifstream fin(file_path);

    if(!fin.good() || fin.eof()) {

        // Invalid stream / file
        return FILE_IO_ERROR;
    }

    // Declare dummy variables for sorting
    int* dummyArray = nullptr;
    int arraySize = 0;

    // Read the amount of elements
    fin >> arraySize;

    if(arraySize > MAX_SIZE) {

        // Avoid allocating too much memory
        return EXEC_FAILURE;
    }

    // Allocate space for array
    dummyArray = new int[arraySize + 1];

    // Read array elements
    for(auto index = 0; index < arraySize; index++) {

        fin >> dummyArray[index];
    }

    // Measure sorting time
    auto time_start = std::chrono::high_resolution_clock::now();

    mergeSort(dummyArray, 0, arraySize - 1);

    auto time_stop = std::chrono::high_resolution_clock::now();

    // Calculate runtime as double
    std::chrono::duration<long double, std::milli> runTime = time_stop - time_start;

    // Open output stream and log results
    std::ofstream fout("results_mergeSort.txt", std::ios_base::app);

    // Formatting
    if(runTime.count() > 60000) {

        fout << "Number of elements: " << arraySize << " --- Runtime: " << (double)(runTime.count() / 60000.0) << " minutes.\n";
    } else if(runTime.count() > 100) {

        fout << "Number of elements: " << arraySize << " --- Runtime: " << (double)(runTime.count() / 1000.0) << " seconds.\n";
    } else {

        fout << "Number of elements: " << arraySize << " --- Runtime: " << (double)runTime.count() << " milliseconds.\n";
    }

    // Close file streams
    fout.close();
    fin.close();

    // Deallocate memory
    delete[] dummyArray;

    // End of execution
    return EXEC_SUCCESS;
}
