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

    int temp[frames], pageFaults = 0;

    for (int i = 0; i < frames; i++)
        temp[i] = -1;

    for (int i = 0; i < n; i++) {
        int flag1 = 0, flag2 = 0;
        for (int j = 0; j < frames; j++) {
            if (temp[j] == pages[i]) {
                flag1 = flag2 = 1;
                break;
            }
        }

        if (flag1 == 0) {
            for (int j = 0; j < frames; j++) {
                if (temp[j] == -1) {
                    temp[j] = pages[i];
                    pageFaults++;
                    flag2 = 1;
                    break;
                }
            }
        }

        if (flag2 == 0) {
            int future[frames];
            for (int x = 0; x < frames; x++) {
                int found = 0;
                for (int y = i + 1; y < n; y++) {
                    if (temp[x] == pages[y]) {
                        future[x] = y;
                        found = 1;
                        break;
                    }
                }
                if (!found)
                    future[x] = 9999;
            }

            int max = -1, pos = 0;
            for (int x = 0; x < frames; x++) {
                if (future[x] > max) {
                    max = future[x];
                    pos = x;
                }
            }

            temp[pos] = pages[i];
            pageFaults++;
        }
    }

    printf("\n--- Optimal Page Replacement ---\n");
    printf("Total Page Faults = %d\n", pageFaults);
    return 0;
}
