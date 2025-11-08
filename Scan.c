#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1]) {
                int t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
}

void SCAN(int req[], int n, int head, int disk_size) {
    int total = 0, pos = head;
    sort(req, n);

    printf("\n--- SCAN Disk Scheduling ---\n");
    printf("Sequence of Head Movement: %d", head);

    int i;
    for (i = 0; i < n; i++)
        if (req[i] >= head)
            break;

    // move towards higher end
    for (int j = i; j < n; j++) {
        total += abs(req[j] - pos);
        pos = req[j];
        printf(" -> %d", pos);
    }

    // go to disk end
    if (pos != disk_size - 1) {
        total += abs((disk_size - 1) - pos);
        pos = disk_size - 1;
        printf(" -> %d", pos);
    }

    // then reverse direction
    for (int j = i - 1; j >= 0; j--) {
        total += abs(req[j] - pos);
        pos = req[j];
        printf(" -> %d", pos);
    }

    printf("\nTotal Head Movement: %d\n", total);
}

int main() {
    int n, head, disk_size;
    int req[50];

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    printf("Enter request sequence: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter total disk size (number of cylinders): ");
    scanf("%d", &disk_size);

    SCAN(req, n, head, disk_size);
    return 0;
}
