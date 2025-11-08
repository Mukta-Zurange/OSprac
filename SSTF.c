#include <stdio.h>
#include <stdlib.h>

void SSTF(int req[], int n, int head) {
    int done[50] = {0}, total = 0, count = 0, pos = head;

    printf("\n--- SSTF Disk Scheduling ---\n");
    printf("Sequence of Head Movement: %d", head);

    while (count < n) {
        int min = 9999, index = -1;
        for (int i = 0; i < n; i++) {
            if (!done[i]) {
                int diff = abs(req[i] - pos);
                if (diff < min) {
                    min = diff;
                    index = i;
                }
            }
        }
        total += abs(req[index] - pos);
        pos = req[index];
        done[index] = 1;
        count++;
        printf(" -> %d", pos);
    }
    printf("\nTotal Head Movement: %d\n", total);
    
}

int main() {
    int n, head, req[50];
    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    printf("Enter request sequence: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    SSTF(req, n, head);
    return 0;
}
