#include <stdio.h>

void sort(int p_id[], int p[], int at[], int bt[], int n) {
    int min_index, temp;
    for (int i = 0; i < n - 1; i++) {
        min_index = i;
        for (int j = i + 1; j < n; j++) {
            if (p[j] < p[min_index]) {
                min_index = j;
            }
        }

        temp = at[i];
        at[i] = at[min_index];
        at[min_index] = temp;

        temp = bt[i];
        bt[i] = bt[min_index];
        bt[min_index] = temp;

        temp = p[i];
        p[i] = p[min_index];
        p[min_index] = temp;

        temp = p_id[i];
        p_id[i] = p_id[min_index];
        p_id[min_index] = temp;
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int p_id[n], at[n], bt[n], ct[n], tat[n], wt[n], rt[n], p[n];
    double avg_tat = 0.0, ttat = 0.0, avg_wt = 0.0, twt = 0.0;

    for (int i = 0; i < n; i++) {
        p_id[i] = i + 1;
    }

    printf("Enter priorities, arrival times, and burst times:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d %d", &p[i], &at[i], &bt[i]);
    }

    sort(p_id, p, at, bt, n);

    int c = 0, count = 0;
    int m[n];
    for (int i = 0; i < n; i++) {
        m[i] = 0;
        rt[i] = -1;
    }

    while (count < n) {
        int selected = -1;
        int min_priority = 9999;
        for (int i = 0; i < n; i++) {
            if (at[i] <= c && m[i] == 0 && p[i] < min_priority) {
                min_priority = p[i];
                selected = i;
            }
        }
        if (selected == -1) {
            c++;
            continue;
        }
        if (rt[selected] == -1)
            rt[selected] = c - at[selected];
        
        c += bt[selected];
        ct[selected] = c;
        m[selected] = 1;
        count++;
    }

    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        ttat += tat[i];
        twt += wt[i];
    }
    avg_tat = ttat / (double)n;
    avg_wt = twt / (double)n;

    printf("PID\tPriority\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t %d\t\t%d\t%d\t%d\t%d\t%d\t%d\n", p_id[i], p[i], at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }

    printf("\nAverage turnaround time: %lfms\n", avg_tat);
    printf("\nAverage waiting time: %lfms\n", avg_wt);

    return 0;
}
