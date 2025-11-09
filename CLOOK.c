#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void CLOOK(int req[], int n, int head) {
    int total = 0, pos = head;

    qsort(req, n, sizeof(int), compare);

    printf("\nC-LOOK Disk Scheduling\n");
    printf("Sequence of Head Movement: %d", head);

    int i;
    for (i = 0; i < n; i++)
        if (req[i] >= head)
            break;

    // Move from head towards higher requests
    for (int j = i; j < n; j++) {
        total += abs(req[j] - pos);
        pos = req[j];
        printf(" -> %d", pos);
    }

    // Jump to the lowest request (circular movement)
    if (i > 0) {
        total += abs(req[n - 1] - req[0]);
        pos = req[0];
        printf(" -> %d", pos);

        for (int j = 1; j < i; j++) {
            total += abs(req[j] - pos);
            pos = req[j];
            printf(" -> %d", pos);
        }
    }

    printf("\nTotal Head Movement: %d\n", total);
}

int main() {
    int n, head, req[50];

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    printf("Enter disk request sequence: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    CLOOK(req, n, head);
    return 0;
}
