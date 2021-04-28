// Including necessary libraries
#include <fstream>
#include <thread>
#include <cstring>
#include <windows.h>

// --- BEGIN RETURN CODES ---

#define EXEC_FAILURE 1      // Not enough arguments
#define EXEC_SUCCESS 0      // Execution completed with no errors

#define FILE_IO_ERROR 5     // The algorithm specified has no executable
#define FILEXEC_ERROR 6     // Invalid arguments passed to main

// --- BEGIN CONSTANTS ---

const int CURRENT_SIZE = 5;
const int MAX_SIZE = 255;

const char* testPaths[MAX_SIZE] = {

    /* The file path is relative */

    "input01.txt",
    "input02.txt",
    "input03.txt",
    "input04.txt",
    "input05.txt",
    "input06.txt",
    "input07.txt",
    "input08.txt",
    "input09.txt",
    "input10.txt"
};

const char* filePaths[MAX_SIZE] = {

    /* The file path is relative */

    "bubbleSort.exe",
    "insertionSort.exe",
    "selectionSort.exe",
    "quickSort.exe",
    "mergeSort.exe"
};

const char* algorithmNames[MAX_SIZE] = {

    /* Represents how the algorithms should be
    given as parameters to the main function. */

    "bubbleSort",
    "insertionSort",
    "selectionSort",
    "quickSort",
    "mergeSort"
};

void callProgram(int i, int current) {
    char* command = new char[255];

    strcpy(command, "");
    strcpy(command, filePaths[current]);
    strcat(command, " -");
    strcat(command, testPaths[i]);
    strcat(command, "\0");

    system(command);

    delete[] command;
}

// Main function
int main(int argc, char** argv) {

    /*
     *
     * Command line format:
     *      - List of sorting algorithms
     *
     * Example of call: "driver.exe -quickSort -bubbleSort -mergeSort"
     *
     */

    std::thread threadPool[11];

    int index = 0;

    if(argc == 1) {

        // Empty list of sorting arguments, abort execution
        return EXEC_FAILURE;
    }

    // Flag to check whether any matches were found
    bool found = false;

    // Used to store the current identifier
    int current = 0;

    for(auto argIndex = 1; argIndex < argc; argIndex++) {

        // Reset flag
        found = false;

        // Check for validity
        for(auto index = 0; index < CURRENT_SIZE; index++) {

            if(strcmp(argv[argIndex]+1, algorithmNames[index]) == 0) {

                // Match found, update and exit search
                found = true;
                current = index;
                break;
            }
        }

        if(found) {

            // Call sorting algorithm for each input
            for(auto i = 0; i < 10; i++) {

                threadPool[index] = std::thread(callProgram, i, current);
                index++;

                if(index == 10) {
                    for(auto number = 0; number < 10; number++) {
                        threadPool[number].join();
                    }

                    index = 0;
                }
            }

        } else {

            return FILEXEC_ERROR;
        }
    }

    for(int i = 0; i < index; i++) {
        threadPool[i].join();
    }

    system("pause");

    // End of execution
    return EXEC_SUCCESS;
}
