#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Compare function for sorting
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter elements: ");
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    // Sort in parent before fork
    qsort(arr, n, sizeof(int), compare);

    pid_t pid = fork();

    if (pid == 0) {
        // Child process — execute os2bchild
        char *args[n + 2];
        args[0] = (char *)"./os2bchild"; // executable name

        for (int i = 0; i < n; i++) {
            args[i + 1] = (char *)malloc(10);
            sprintf(args[i + 1], "%d", arr[i]);
        }
        args[n + 1] = NULL;

        execve(args[0], args, NULL);
        perror("execve failed");
        exit(1);
    } 
    else if (pid > 0) {
        printf("\nParent Process (PID: %d)\n", getpid());
        printf("Parent performing qsort...\n");
        printf("Parent Sorted Array: ");
        for (int i = 0; i < n; i++) printf("%d ", arr[i]);
        printf("\nParent passing sorted array to child...\n");

        wait(NULL);
    } 
    else {
        perror("fork failed");
    }

    return 0;
}

