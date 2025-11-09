#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t mutex;  // protects read_count
pthread_mutex_t wrt;    // protects writing
int read_count = 0;     // number of active readers
int shared_data = 0;    // the data being read/written

void *reader(void *arg) {
    int id = *(int*)arg;
    free(arg);

    pthread_mutex_lock(&mutex);
    read_count++;
    if (read_count == 1)  // first reader locks writer
        pthread_mutex_lock(&wrt);
    pthread_mutex_unlock(&mutex);

    // Reading section
    printf("Reader %d is reading shared data: %d\n", id, shared_data);
    sleep(1); // simulate reading

    pthread_mutex_lock(&mutex);
    read_count--;
    if (read_count == 0)  // last reader unlocks writer
        pthread_mutex_unlock(&wrt);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void *writer(void *arg) {
    int id = *(int*)arg;
    free(arg);

    pthread_mutex_lock(&wrt); // lock for writing

    // Writing section
    printf("Writer %d is writing.\nEnter new value for shared data: ", id);
    scanf("%d", &shared_data);
    printf("Writer %d updated shared data to %d\n", id, shared_data);
    sleep(1); // simulate writing

    pthread_mutex_unlock(&wrt); // unlock after writing
    return NULL;
}

int main() {
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&wrt, NULL);

    int choice, id = 1;

    while (1) {
        printf("\nEnter:\n1 to Read\n2 to Write\n3 to Exit\nChoice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            pthread_t t;
            int *arg = malloc(sizeof(*arg));
            *arg = id++;
            pthread_create(&t, NULL, reader, arg);
            pthread_detach(t); // detach so it runs concurrently
        } else if (choice == 2) {
            pthread_t t;
            int *arg = malloc(sizeof(*arg));
            *arg = id++;
            pthread_create(&t, NULL, writer, arg);
            pthread_join(t, NULL); // wait for writer to finish
        } else if (choice == 3) {
            printf("Exiting...\n");
            break;
        } else {
            printf("Invalid choice! Try again.\n");
        }
    }

    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&wrt);

    return 0;
}
