#include <stdio.h>

int main() {
    int n, currentTime = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int p[n], at[n], bt[n], ct[n], tat[n], wt[n], m[n];
    double avg_tat = 0.0, ttat = 0.0, avg_wt = 0.0, twt = 0.0;

    for (int i = 0; i < n; i++) {
        p[i] = i + 1;
        m[i] = 0;
    }
    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", p[i]);
        scanf("%d %d", &at[i], &bt[i]);
    }

    int count = 0, minBurst, selectedProcess;
    while (count < n) {
        minBurst = 10000;  
        selectedProcess = -1;

        for (int i = 0; i < n; i++) {
            if (at[i] <= currentTime && m[i] == 0 && bt[i] < minBurst) {
                minBurst = bt[i];
                selectedProcess = i;
            }
        }

        if (selectedProcess == -1) {
            currentTime++;
            continue;
        }

        m[selectedProcess] = 1;
        count++;
        currentTime += bt[selectedProcess];
        ct[selectedProcess] = currentTime;
        tat[selectedProcess] = ct[selectedProcess] - at[selectedProcess];
        wt[selectedProcess] = tat[selectedProcess] - bt[selectedProcess];
    }

    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i], at[i], bt[i], ct[i], tat[i], wt[i]);
        ttat += tat[i];
        twt += wt[i];
    }

    avg_tat = ttat / (double)n;
    avg_wt = twt / (double)n;
    printf("\nAverage turnaround time: %.2lfms\n", avg_tat);
    printf("Average waiting time: %.2lfms\n", avg_wt);

    return 0;
}
