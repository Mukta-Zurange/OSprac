#include <stdio.h>

int findLRU(int time[], int n) {
    int min = time[0], pos = 0;
    for (int i = 1; i < n; i++)
        if (time[i] < min)
            min = time[i], pos = i;
    return pos;
}

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

    int temp[frames], time[frames], counter = 0, pageFaults = 0;

    for (int i = 0; i < frames; i++)
        temp[i] = -1;

    for (int i = 0; i < n; i++) {
        int flag1 = 0, flag2 = 0;
        for (int j = 0; j < frames; j++) {
            if (temp[j] == pages[i]) {
                counter++;
                time[j] = counter;
                flag1 = flag2 = 1;
                break;
            }
        }

        if (flag1 == 0) {
            for (int j = 0; j < frames; j++) {
                if (temp[j] == -1) {
                    counter++;
                    temp[j] = pages[i];
                    time[j] = counter;
                    pageFaults++;
                    flag2 = 1;
                    break;
                }
            }
        }

        if (flag2 == 0) {
            int pos = findLRU(time, frames);
            counter++;
            temp[pos] = pages[i];
            time[pos] = counter;
            pageFaults++;
        }
    }

    printf("\n--- LRU Page Replacement ---\n");
    printf("Total Page Faults = %d\n", pageFaults);
    return 0;
}
