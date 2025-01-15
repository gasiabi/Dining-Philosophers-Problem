#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define PHIL_COUNT 5

// Zmienne globalne
char state[8]; // Stan filozofów
// m - medytuje, C - czeka, L - bierze lewy widelec, P - bierze prawy widelec, l - odkłada lewy widelec, p - odkłada prawy widelec, J - je, "-" - kończy jeść
sem_t forks[PHIL_COUNT]; // Semafory
pthread_mutex_t print_lock; // mutex, który zapewnia, że operacje wypisywane przez wątki nie będą się na siebie nakładać

// wyczytywanie stanu aktualnego
void print_state(int phil_id, const char *action) {
    pthread_mutex_lock(&print_lock);
    printf("Filozof %d: [%s] %s\n", phil_id + 1, state, action);
    fflush(stdout);
    pthread_mutex_unlock(&print_lock);
}

void *philosopher_task(void *arg) {
    int phil_id = *(int *)arg;

    for (int i = 0; i < 7; i++) { // Każdy filozofów wykonuje 7 cykli jedzenia
        // Medytowanie
        state[phil_id] = 'm';
        print_state(phil_id, "medytuje");
        usleep((rand() % 5 + 1) * 500000);

        // Czekanie i zabranie lewego widelca
        state[phil_id] = 'C';
        print_state(phil_id, "czeka na lewy widelec");
        sem_wait(&forks[phil_id]);
        state[phil_id] = 'L';
        print_state(phil_id, "bierze lewy widelec");

        // Czekanie i zabranie prawego widelca
        state[phil_id] = 'C';
        print_state(phil_id, "czeka na prawy widelec");
        sem_wait(&forks[(phil_id + 1) % PHIL_COUNT]);
        state[phil_id] = 'P';
        print_state(phil_id, "bierze prawy widelec");

        // Jedzenie
        state[phil_id] = 'J';
        print_state(phil_id, "je");
        usleep((rand() % 5 + 1) * 500000); 
        
        // Odkładanie widelców
        state[phil_id] = 'l';
        print_state(phil_id, "odklada lewy widelec");
        sem_post(&forks[phil_id]);
        state[phil_id] = 'p';
        print_state(phil_id, "odklada prawy widelec");
        sem_post(&forks[(phil_id + 1) % PHIL_COUNT]);

        // Koniec jedzenia
        state[phil_id] = '-';
        print_state(phil_id, "konczy jedzenie");
    }

    free(arg); // uwolnienie pamieci
    return NULL;
}

int main() {
    pthread_t philosophers[PHIL_COUNT];
    pthread_mutex_init(&print_lock, NULL);

    // zainicjowanie stanów i semaforów
    for (int i = 0; i < PHIL_COUNT; i++) {
        state[i] = '-';
        sem_init(&forks[i], 0, 1);
    }
    state[PHIL_COUNT] = '\0'; 

    // tworzenie wątków filozofów
    for (int i = 0; i < PHIL_COUNT; i++) {
        int *id = malloc(sizeof(int));
        if (id == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        *id = i;
        if (pthread_create(&philosophers[i], NULL, philosopher_task, id) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    // czekanie aż wszystkie wątki się skończą
    for (int i = 0; i < PHIL_COUNT; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // wyczyszczenie
    for (int i = 0; i < PHIL_COUNT; i++) {
        sem_destroy(&forks[i]);
    }
    pthread_mutex_destroy(&print_lock);

    printf("Wszyscy filozofowie zakonczyli swoje dzialania.\n");
    return 0;
}
