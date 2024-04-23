#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int numOfPhils; // number of phils, passed in as argument[1]
int numOfTimesToEat; // number of times to eat each, passed in as argument[2]
sem_t *chopsticks;
int *state;
int *phils;

// functions that may be helpful to create
void test(); // used to check state of philsopher and state of each chopstick
             // if philospher is hungry and both left and right are satisifed
             // then they should be able to eat now

void pickupChopstick(); // waits to grab chopsticks for philospher (denotes when philospher is hungry)
void putDownChopstick(); // puts chopsticks back down (denotes when philospher is thinking)
void *philosopher(); // must be a pointer when working with threading
                     // determines first action of a philospher when thread is created

int main(int argc, char *argv[]) {

    // thread usage
    pthread_t threads[numOfPhils];
    // for threads you will need to incorporate the concept of creating and
    // joining to solve this problem

    // memory allocation for chopsticks, state, and philosphers
    chopsticks = malloc(numOfPhils * sizeof(sem_t));
    state = malloc(numOfPhils * sizeof(int));
    phils = malloc(numOfPhils * sizeof(int));

    // create philosphers and give them a state based on numOfPhils
    // then create a thread for each using


    free(chopsticks);
    free(state);
    free(phils);
    return 0;
}