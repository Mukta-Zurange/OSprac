#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

// Function to print array
void printArray(int arr[], int n) {
    for(int i=0; i<n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Bubble sort for parent
void bubbleSort(int arr[], int n) {
    for(int i=0;i<n-1;i++)
        for(int j=0;j<n-i-1;j++)
            if(arr[j]>arr[j+1]){
                int temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
}

// Insertion sort for child
void insertionSort(int arr[], int n) {
    for(int i=1;i<n;i++){
        int key=arr[i], j=i-1;
        while(j>=0 && arr[j]>key){
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=key;
    }
}

int main() {
    int n;
    printf("Enter number of integers: ");
    scanf("%d", &n);

    int arr[n], arr_child[n];
    printf("Enter integers: ");
    for(int i=0;i<n;i++){
        scanf("%d", &arr[i]);
        arr_child[i] = arr[i]; // copy for child
    }

    pid_t pid = fork();

    if(pid < 0){
        printf("Fork failed!\n");
        return 1;
    }
    else if(pid == 0){
        // Child process
        insertionSort(arr_child, n);
        printf("\nChild process sorted array (Insertion Sort): ");
        printArray(arr_child, n);
        exit(0);
    }
    else{
        // Parent process
        bubbleSort(arr, n);
        printf("\nParent process sorted array (Bubble Sort): ");
        printArray(arr, n);

        wait(NULL); // wait for child to finish
        printf("Child process completed sorting.\n");
    }

    return 0;
}
