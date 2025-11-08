#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5

int buffer[SIZE], in = 0, out = 0;
int produced_count = 0, consumed_count = 0;

sem_t empty, full;
pthread_mutex_t mutex;

void produce_item(int item) {
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);

    buffer[in] = item;
    printf("Produced %d at %d\n", item, in);
    in = (in + 1) % SIZE;
    produced_count++;

    pthread_mutex_unlock(&mutex);
    sem_post(&full);
}

void consume_item() {
    sem_wait(&full);
    pthread_mutex_lock(&mutex);

    int item = buffer[out];
    printf("Consumed %d at %d\n", item, out);
    out = (out + 1) % SIZE;
    consumed_count++;

    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
}

int main() {
    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    int choice, item;

    while (1) {
        printf("\nEnter:\n1 to Produce\n2 to Consume\n3 to Exit\nChoice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            if (produced_count - consumed_count == SIZE) {
                printf("Buffer full! Cannot produce more items now.\n");
                continue;
            }
            printf("Enter item to produce: ");
            scanf("%d", &item);
            produce_item(item);
        } else if (choice == 2) {
            if (produced_count == consumed_count) {
                printf("No items to consume.\n");
                continue;
            }
            consume_item();
        } else if (choice == 3) {
            printf("Exiting...\n");
            break;
        } else {
            printf("Invalid choice! Try again.\n");
        }
    }

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}

