/*
Name: Connor Heard, Emilio El-Zahr, Kirkland Grace
Date: 5/10/2024
Description: Operating Systems Page Replacement Algorithms
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_PAGE_REFERENCE_LENGTH 100
#define MAX_PAGE_NUMBER 9
#define DEBUG 1

// Macro that returns the length of an array
#define ARRAY_LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))

int fifo(int frameCount, int pageNumArray[]) {
    int frameArray[frameCount];
}

int main(int argc, char *argv[]) {
    int testPages[] = {8,3,8,7,4,7,8,2,9,0,3,2,6,3,8,1,3,7,3,5,1,1,8,9,7,0,9,6,6,8,8,4,4,9,1,0,7,3,8,0,5,8,8,4,4,4,4,8,4,5,9,9,5,1,4,3,0,8,0,0,7,1,2,3,8,3,4,9,4,1,6,8,2,8,1,6,6,9,2,2,0,3,6,6,5,1,3,0,8,7,6,1,9,1,6,6,1,3,7,0};
    

    if (argc == 2) {
        int frameNum = argv[1];

        int fifoFaultCount = fifo(frameNum, testPages);
    }

    else if (argc == 3) {
        int frameNum = argv[1];
        int seed = argv[2];

        // Generate randomized array of page indexes based on provided seed
        int randomPages[MAX_PAGE_REFERENCE_LENGTH];
        srand(seed);

        // Fills new page array with randomly generated indexes between 0 to 9
        for (int i = 0; i < MAX_PAGE_REFERENCE_LENGTH; i++) {
            randomPages[i] = rand() % (MAX_PAGE_NUMBER + 1);
        }

        if (DEBUG) {
            printf(randomPages);
            exit(0);
        }

    }
    
    else {
        printf("Usage: ./pageReplace <number_of_frames> [random_seed]");
        exit(0);
    }


    return 0;
}