// Connor Heard & Emilio Elzahr

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

// used to check state of philsopher and state of each chopstick
// if philospher is hungry and both left and right are satisifed
// then they should be able to eat now
// logic for this program gotten from
// https://www.geeksforgeeks.org/dining-philosopher-problem-using-semaphores/
void test(int i) {
    if (state[i] == 0 && state[(i + 1) % numOfPhils] != 1 && state[(i+ numOfPhils - 1) % numOfPhils] != 1){
        state[i] = 1;
        sem_post(&chopsticks[i]);
    }
}

 // waits to grab chopsticks for philospher (denotes when philospher is hungry)
void pickupChopstick(int i) {
    sem_wait(&chopsticks[i]);
    state[i] = 0;
}

// puts chopsticks back down (denotes when philospher is thinking)
void putDownChopstick(int i) {
    sem_post(&chopsticks[i]);
    state[i] = 2;
}

// must be a pointer when working with threading
// determines first action of a philospher when thread is created
void *philosopher(void *arg) {
    int i = *(int *)arg;
    int eatCount = 0;
    while (eatCount < numOfTimesToEat) {
        printf("Philosophers %d is thinking...\n", i);
        sleep(rand() % 3 + 1); // we have to simulate thinking
        printf("Philosopher %d is hungry...\n", i);
        pickupChopstick(i);
        pickupChopstick((i + 1) % numOfPhils);
        printf("Philosopher %d is eating...\n", i);
        sleep(rand() % 3 + 1);
        putDownChopstick(i);
        putDownChopstick((i + 1) % numOfPhils);
        eatCount++;
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {

    // checking for correct number of arguments
    if (argc != 3) {
         printf("Usage: %s <number_of_philosophers> <number_of_times_to_eat>\n", argv[0]);
         return 1;
    }

    // turn user arguments into integers
    numOfPhils = atoi(argv[1]);
    numOfTimesToEat = atoi(argv[2]);

    // random number generator seed
    srand(time(NULL));

    // thread usage
    pthread_t threads[numOfPhils];

    // memory allocation for chopsticks, state, and philosphers
    chopsticks = malloc(numOfPhils * sizeof(sem_t));
    state = malloc(numOfPhils * sizeof(int));
    phils = malloc(numOfPhils * sizeof(int));

    // We have to initialize the semaphore and philosopher states
    for (int i = 0; i < numOfPhils; i++) {
        sem_init(&chopsticks[i], 0, 1);
        state[i] = 2;
        phils[i] = i;
    }

    // now we actually create the "philosophers" and give them a state
    for (int i = 0; i < numOfPhils; i++){
        pthread_create(&threads[i], NULL, philosopher, &phils[i]);
    }

    // then we join threads
    for (int i = 0; i < numOfPhils; i++) {
        pthread_join(threads[i], NULL);
    }

    // pickup semaphores
    for (int i = 0; i < numOfPhils; i++) {
        sem_destroy(&chopsticks[i]);
    }

    free(chopsticks);
    free(state);
    free(phils);
    return 0;
}
