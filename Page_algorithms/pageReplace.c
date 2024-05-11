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

// Formats output to be printed to terminal
void output(int fifoCount, int lruCount, int optimalCount) {
    printf("\nAlgorithm\t# Page faults\n");
    printf("FIFO     \t%d\n", fifoCount);
    printf("LRU      \t%d\n", lruCount);
    printf("OPT      \t%d\n", optimalCount);
}


// Implementation of the FIFO page to frame assignment algorithm.
// Logic of this function gotten from: https://www.geeksforgeeks.org/program-page-replacement-algorithms-set-2-fifo/
int fifo(int frameCount, int pageNumArray[], int arraySize) {
    int frameArray[frameCount]; // Array to hold frames
    int pageFaultCount = 0;
    int currentPosition = 0;

    // Iterate over the array to perform the FIFO algorithm
    for (int i = 0; i < arraySize; i++) {
        int currentPage = pageNumArray[i];

        // Set a flag for when page is found
        int pageDiscovered = 0;

        // Check if the current item is in a frame
        for (int j = 0; j < frameCount; j++) {
            if (frameArray[j] == currentPage) {
                // set flag to true
                pageDiscovered = 1;
                break;
            }
        }

        // If the page is not in a frame, then we replace
        // the oldest page with current one
        if (!pageDiscovered) {
            frameArray[currentPosition] = currentPage;
            currentPosition = (currentPosition + 1) % frameCount;
            pageFaultCount++;
        }
    }

    return pageFaultCount;
}

//Implementation of the LRU (Least Recently Used) page to frame assignment algorithm.
// Logic of this function gotten from: https://www.geeksforgeeks.org/program-for-least-recently-used-lru-page-replacement-algorithm/
int lru(int frameCount, int pageNumArray[], int arraySize) {
    int frameArray[frameCount]; // Array to hold frames
    int recentAccess[frameCount]; // Array to track recent access
    int pageFaultCount = 0;

    for (int i = 0; i < frameCount; i++) {
        // Initialize frames with invalid page numbers
        frameArray[i] = -1; 
        // Initialize recent access to 0
        recentAccess[i] = 0;
    }

    for (int i = 0; i < arraySize; i++) {
        int currentPage = pageNumArray[i];
        int pageDiscovered = 0;

        for (int j = 0; j < frameCount; j++) {
            if (frameArray[j] == currentPage) {
                pageDiscovered = 1;
                recentAccess[j] = i + 1; // Update recent access
                break;
            }
        }

        if (!pageDiscovered) {
            int leastRecentIndex = 0;
            for (int j = 1; j < frameCount; j++) {
                if (recentAccess[j] < recentAccess[leastRecentIndex]) {
                    leastRecentIndex = j;
                }
            }

            // Actually replaces the least recently used page
            // with the current
            frameArray[leastRecentIndex] = currentPage;
            recentAccess[leastRecentIndex] = i + 1; // Update recent access
            pageFaultCount++;
        }
    }

    return pageFaultCount;
}

//Implementation of the Optimal page to frame assignment algorithm.
// Logic of this function gotten from: https://www.geeksforgeeks.org/optimal-page-replacement-algorithm/
int optimal(int frameCount, int pageNumArray[], int arraySize) {
    int frameArray[frameCount]; // Array to hold frames
    int pageFaultCount = 0;

    // Initialize frames with a placeholder value
    for (int i = 0; i < frameCount; i++) {
        frameArray[i] = -1;
    }

    for (int i = 0; i < arraySize; i++) {
        int currentPage = pageNumArray[i];
        // initialize a flag for when a page is found in a frame
        int pageDiscovered = 0;

        // Scan the frames to see if the current page
        // is in it
        for (int j = 0; j < frameCount; j++) {
            if (frameArray[j] == currentPage) {
                pageDiscovered = 1;
                break;
            }
        }

        if (!pageDiscovered) {
            // set up our replace index with our current one
            int replaceIndex = i;
            int farthestOccurence = -1;

            for (int j = 0; j < frameCount; j++) {
                int nextPageOccurence = arraySize;
                for (int k = i + 1; k < arraySize; k++) {
                    if (pageNumArray[k] == frameArray[j]) {
                        nextPageOccurence = k;
                        break;
                    }
                }

                // determine it the next occurence of page is greater
                // than the current farthest occurence
                if (nextPageOccurence > farthestOccurence) {
                    farthestOccurence = nextPageOccurence;
                    replaceIndex = j;
                }
            }

            // actually swap out the page to be replaced with
            // the current one
            frameArray[replaceIndex] = currentPage;
            pageFaultCount++;
        }
    }

    return pageFaultCount;

}

int main(int argc, char *argv[]) {

    // If the users does not provide a seed, then we use a default test array
    if (argc == 2) {
        int testPages[] = {8,3,8,7,4,7,8,2,9,0,3,2,6,3,8,1,3,7,3,5,1,1,8,9,7,0,9,6,6,8,8,4,4,9,1,0,7,3,8,0,5,8,8,4,4,4,4,8,4,5,9,9,5,1,4,3,0,8,0,0,7,1,2,3,8,3,4,9,4,1,6,8,2,8,1,6,6,9,2,2,0,3,6,6,5,1,3,0,8,7,6,1,9,1,6,6,1,3,7,0};
        int arraySize = ARRAY_LENGTH(testPages);
        int frameNum = atoi(argv[1]);

        // Get the number of page faults for each algorithm
        int fifoFaultCount = fifo(frameNum, testPages, arraySize);
        int lruFaultCount = lru(frameNum, testPages, arraySize);
        int optimalFaultCount = optimal(frameNum, testPages, arraySize);

        // Print Appropriate Output
        output(fifoFaultCount, lruFaultCount, optimalFaultCount);
        exit(0);
    }

    else if (argc == 3) {
        int frameNum = atoi(argv[1]);
        int seed = atoi(argv[2]);

        // Generate randomized array of page indexes based on provided seed
        int randomPages[MAX_PAGE_REFERENCE_LENGTH];
        srand(seed);
        int arraySize = ARRAY_LENGTH(randomPages);

        // Fills new page array with randomly generated indexes between 0 to 9
        for (int i = 0; i < MAX_PAGE_REFERENCE_LENGTH; i++) {
            randomPages[i] = rand() % (MAX_PAGE_NUMBER + 1);
        }

        // Print out seed generated page array
        if (DEBUG) {
            printf("\n");
            printf("Seed %d's reference string:\n", seed);
            for (int i = 0; i < arraySize; i++) {
                printf("%d ", randomPages[i]);
            }
            printf("\n");
        }

        // Get the number of page faults for each algorithm
        int fifoFaultCount = fifo(frameNum, randomPages, arraySize);
        int lruFaultCount = lru(frameNum, randomPages, arraySize);
        int optimalFaultCount = optimal(frameNum, randomPages, arraySize);

        // Print Appropriate Output
        output(fifoFaultCount, lruFaultCount, optimalFaultCount);
        exit(0);

    }
    
    else {
        printf("Usage: ./a.out <number_of_frames> [seed]\n");
        exit(0);
    }


    return 0;
}
