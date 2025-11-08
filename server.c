#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_KEY 1234
#define SHM_SIZE 1024

int main() {
    int shmid;
    char *shm_ptr;

    // Create shared memory
    if((shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666)) < 0){
        perror("shmget");
        exit(1);
    }

    // Attach shared memory
    if((shm_ptr = (char *)shmat(shmid, NULL, 0)) == (char *)-1){
        perror("shmat");
        exit(1);
    }

    printf("Enter message to write to shared memory: ");
    fgets(shm_ptr, SHM_SIZE, stdin);

    printf("Message written to shared memory.\n");

    // Detach shared memory
    shmdt(shm_ptr);

    return 0;
}
