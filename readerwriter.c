#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;  // protects read_count
pthread_mutex_t wrt;    // protects writing
int read_count = 0;     // number of active readers
int shared_data = 0;    // the data being read/written

void reader(int id) {
    pthread_mutex_lock(&mutex);
    read_count++;
    if (read_count == 1) // first reader locks writer
        pthread_mutex_lock(&wrt);
    pthread_mutex_unlock(&mutex);

    // Reading section
    printf("Reader %d is reading shared data: %d\n", id, shared_data);
    sleep(1); // simulate reading

    pthread_mutex_lock(&mutex);
    read_count--;
    if (read_count == 0) // last reader unlocks writer
        pthread_mutex_unlock(&wrt);
    pthread_mutex_unlock(&mutex);
}

void writer(int id) {
    pthread_mutex_lock(&wrt); // lock for writing

    // Writing section
    printf("Writer %d is writing.\nEnter new value for shared data: ", id);
    scanf("%d", &shared_data);
    printf("Writer %d updated shared data to %d\n", id, shared_data);
    sleep(1); // simulate writing

    pthread_mutex_unlock(&wrt); // unlock after writing
}

int main() {
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&wrt, NULL);

    int choice, id = 1;

    while (1) {
        printf("\nEnter:\n1 to Read\n2 to Write\n3 to Exit\nChoice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            reader(id++);
        } else if (choice == 2) {
            writer(id++);
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
