#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Comparator for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void SCAN(int req[], int n, int head, int disk_size) {
    int total = 0, pos = head;

    // Sort the request queue
    qsort(req, n, sizeof(int), compare);

    printf("\n--- SCAN Disk Scheduling ---\n");
    printf("Sequence of Head Movement: %d", head);

    int i;
    for (i = 0; i < n; i++)
        if (req[i] >= head)
            break;

    // Move towards higher end
    for (int j = i; j < n; j++) {
        total += abs(req[j] - pos);
        pos = req[j];
        printf(" -> %d", pos);
    }

    // Go to disk end
    if (pos != disk_size - 1) {
        total += abs((disk_size - 1) - pos);
        pos = disk_size - 1;
        printf(" -> %d", pos);
    }

    // Reverse direction
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
