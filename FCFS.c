#include <stdio.h>

int main() {
    int n, bt[100], at[100], p[100], ct[100], wt[100], tat[100], i, j, total1 = 0, total2 = 0, pos, temp;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter burst times and arrival times for each process:\n");
    for (i = 0; i < n; i++) {
        printf("P%d (Arrival Time, Burst Time): ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        p[i] = i + 1;
    }

    for (i = 0; i < n - 1; i++) {
        pos = i;
        for (j = i + 1; j < n; j++) {
            if (at[j] < at[pos]) {
                pos = j;
            }
        }
        temp = at[i];
        at[i] = at[pos];
        at[pos] = temp;

        temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;

        temp = p[i];
        p[i] = p[pos];
        p[pos] = temp;
    }


    for (i = 0; i < n; i++) {
        ct[i] = bt[i];
        if (i > 0) {
            ct[i] += ct[i - 1];
        }
    }

    for (i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        total1 += tat[i];
        total2 += wt[i];
    }


    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i],at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time: %.2f\n", (float)total1 / n);
    printf("Average Waiting Time: %.2f\n", (float)total2 / n);

    return 0;
}
