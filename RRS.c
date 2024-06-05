#include <stdio.h>

void sort(int p_id[], int at[], int bt[], int b[], int n) {
    int min, temp;
    for (int i = 0; i < n; i++) {
        min = at[i];
        for (int j = i; j < n; j++) {
            if (at[j] < min) {
                min = at[j];
                temp = at[i]; at[i] = at[j]; at[j] = temp;
                temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
                temp = b[i]; b[i] = b[j]; b[j] = temp;
                temp = p_id[i]; p_id[i] = p_id[j]; p_id[j] = temp;
            }
        }
    }
}

int main() {
    int n, t, c = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter Time Quantum: ");
    scanf("%d", &t);

    int p_id[n], at[n], bt[n], ct[n], tat[n], wt[n], b[n], rt[n], m[n];
    int f = -1, r = -1;
    int q[100];
    double avg_tat = 0.0, avg_wt = 0.0, ttat = 0.0, twt = 0.0;

    for (int i = 0; i < n; i++)
        p_id[i] = i + 1;

    printf("Enter arrival times:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &at[i]);

    printf("Enter burst times:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
        b[i] = bt[i];
        m[i] = 0;
        rt[i] = -1;
    }

    sort(p_id, at, bt, b, n);

    f = r = 0;
    q[0] = p_id[0];


    int p, i;
    while (f >= 0) {
        p = q[f++];
        i = 0;
        while (p != p_id[i])
            i++;
        if (b[i] >= t) {
            if (rt[i] == -1)
                rt[i] = c;
            b[i] -= t;
            c += t;
        } else {
            if (rt[i] == -1)
                rt[i] = c;
            c += b[i];
            b[i] = 0;
        }
        for (int j = 0; j < n; j++) {
            if (at[j] <= c && p_id[j] != p && m[j] == 0) {
                q[++r] = p_id[j];
                m[j] = 1;
            }
        }
        if (b[i] > 0)
            q[++r] = p_id[i];
        else
            ct[i] = c;

        if (f > r)
            f = -1;
    }


    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        rt[i] = rt[i] - at[i];
    }


    for (int i = 0; i < n; i++)
        wt[i] = tat[i] - bt[i];

    printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p_id[i], at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);

    for (int i = 0; i < n; i++) {
        ttat += tat[i];
        twt += wt[i];
    }
    avg_tat = ttat / (double) n;
    avg_wt = twt / (double) n;
    printf("\nAverage turnaround time: %lf ms\n", avg_tat);
    printf("Average waiting time: %lf ms\n", avg_wt);

    return 0;
}
