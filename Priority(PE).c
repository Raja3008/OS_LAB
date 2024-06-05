#include<stdio.h>

void sort(int p_id[], int p[], int at[], int bt[], int b[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i] > p[j]) {

                int temp = p[i];
                p[i] = p[j];
                p[j] = temp;

                temp = at[i];
                at[i] = at[j];
                at[j] = temp;

                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                temp = b[i];
                b[i] = b[j];
                b[j] = temp;

                temp = p_id[i];
                p_id[i] = p_id[j];
                p_id[j] = temp;
            }
        }
    }
}

void main() {
    int n, c = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int p_id[n], at[n], bt[n], ct[n], tat[n], wt[n], m[n], b[n], rt[n], p[n];
    double avg_tat = 0.0, ttat = 0.0, avg_wt = 0.0, twt = 0.0;

    for (int i = 0; i < n; i++) {
        p_id[i] = i + 1;
        m[i] = 0;
    }

    printf("Enter priorities:\n");
    for (int i = 0; i < n; i++) scanf("%d", &p[i]);

    printf("Enter arrival times:\n");
    for (int i = 0; i < n; i++) scanf("%d", &at[i]);

    printf("Enter burst times:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
        b[i] = bt[i];
        m[i] = -1;
        rt[i] = -1;
    }

    sort(p_id, p, at, bt, b, n);


    int count = 0, x = -1;
    while (count < n) {
        int priority = __INT_MAX__;
        for (int i = 0; i < n; i++) {
            if (at[i] <= c && b[i] > 0 && p[i] < priority) {
                x = i;
                priority = p[i];
            }
        }

        if (x != -1) {
            if (rt[x] == -1) rt[x] = c - at[x];
            b[x]--;
            c++;
            if (b[x] == 0) {
                count++;
                ct[x] = c;
                m[x] = 1;
                x = -1;
            }
        } else {
            c++;
        }
    }


    for (int i = 0; i < n; i++) tat[i] = ct[i] - at[i];

    for (int i = 0; i < n; i++) wt[i] = tat[i] - bt[i];

    printf("PID\tPrior\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t %d\t\t%d\t%d\t%d\t%d\t%d\t%d\n", p_id[i], p[i], at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);

    for (int i = 0; i < n; i++) {
        ttat += tat[i];
        twt += wt[i];
    }

    avg_tat = ttat / (double)n;
    avg_wt = twt / (double)n;
    printf("\nAverage turnaround time: %lfms\n", avg_tat);
    printf("\nAverage waiting time: %lfms\n", avg_wt);
}

