#include <stdio.h>

int main() {
    int n, i, tq, time = 0, done = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int at[n], bt[n], rt[n];
	printf("Enter Arrival Time & Burst Time of:-\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d%d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }
    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    float wt = 0, tat = 0;
    while (done < n) {
        int executed = 0;
        for (i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0) {
                executed = 1;
                if (rt[i] > tq) {
                    time += tq;
                    rt[i] -= tq;
                } else {
                    time += rt[i];
                    wt += time - at[i] - bt[i];
                    tat += time - at[i];
                    rt[i] = 0;
                    done++;
                }
            }
        }
        if (!executed) time++;
    }
    printf("\nAverage Waiting Time = %.2f", wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", tat / n);
}
