#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    printf("\nChild Process (PID: %d, PPID: %d)\n", getpid(), getppid());
    printf("Child displaying array in reverse order:\n");

    // Display in reverse order (skip argv[0])
    for (int i = argc - 1; i > 0; i--) {
        printf("%s ", argv[i]);
    }

    printf("\n\nChild exiting...\n");
    return 0;
}

