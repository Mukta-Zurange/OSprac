#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>

#define SHM_KEY 1234
#define SHM_SIZE 1024

int main() {
    int shmid;
    char *shm_ptr;

    // Get shared memory
    if((shmid = shmget(SHM_KEY, SHM_SIZE, 0666)) < 0){
        perror("shmget");
        exit(1);
    }

    // Attach shared memory
    if((shm_ptr = (char *)shmat(shmid, NULL, 0)) == (char *)-1){
        perror("shmat");
        exit(1);
    }

    printf("Message read from shared memory: %s\n", shm_ptr);

    // Detach shared memory
    shmdt(shm_ptr);

    // Optionally, remove shared memory
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
