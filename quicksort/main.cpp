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

int partition (int arr[], int low, int high)
{
    int pivot = arr[high]; // pivot
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++; // increment index of smaller element
            swapElements(&arr[i], &arr[j]);
        }
    }
    swapElements(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
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

    quickSort(dummyArray, 0, arraySize - 1);

    auto time_stop = std::chrono::high_resolution_clock::now();

    // Calculate runtime as double
    std::chrono::duration<long double, std::milli> runTime = time_stop - time_start;

    // Open output stream and log results
    std::ofstream fout("results_quickSort.txt", std::ios_base::app);

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
