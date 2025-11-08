#include <stdio.h>

int main() {
    int n, frames;
    printf("Enter number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter page reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    int temp[frames], pos = 0, pageFaults = 0;

    for (int i = 0; i < frames; i++)
        temp[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++) {
            if (temp[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            temp[pos] = pages[i];
            pos = (pos + 1) % frames;
            pageFaults++;
        }
    }

    printf("\n--- FCFS Page Replacement ---\n");
    printf("Total Page Faults = %d\n", pageFaults);
    return 0;
}
