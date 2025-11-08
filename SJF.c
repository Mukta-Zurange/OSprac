#include <stdio.h>
#include <limits.h>

int main() {
    int n, i, time = 0, remain = 0, min, end;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int at[n], bt[n], rt[n];
	printf("Enter Arrival Time & Burst Time of:-\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d%d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }

    float wt = 0, tat = 0;
    while (remain < n) {
        min = INT_MAX;
        int shortest = -1;
        for (i = 0; i < n; i++)
            if (at[i] <= time && rt[i] > 0 && rt[i] < min)
                min = rt[i], shortest = i;

        if (shortest == -1) { time++; continue; }

        rt[shortest]--; time++;
        if (rt[shortest] == 0) {
            remain++;
            end = time;
            wt += end - at[shortest] - bt[shortest];
            tat += end - at[shortest];
        }
    }
    printf("\nAvg WT = %.2f\nAvg TAT = %.2f\n", wt/n, tat/n);
}
