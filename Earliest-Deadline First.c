#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sort(int p[], int d[], int b[], int pt[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (d[j] < d[i]) {
                swap(&d[j], &d[i]);
                swap(&pt[i], &pt[j]);
                swap(&b[j], &b[i]);
                swap(&p[i], &p[j]);
            }
        }
    }
}

int gcd(int a, int b) {
    while (b > 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int lcm1(int p[], int n) {
    int lcm = p[0];
    for (int i = 1; i < n; i++) {
        lcm = (lcm * p[i]) / gcd(lcm, p[i]);
    }
    return lcm;
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int p[n], b[n], pt[n], d[n], rem[n];
    printf("Enter the CPU burst times:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &b[i]);
        rem[i] = b[i];
    }

    printf("Enter the deadlines:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &d[i]);
    }

    printf("Enter the time periods:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pt[i]);
    }

    for (int i = 0; i < n; i++) {
        p[i] = i + 1;
    }

    sort(p, d, b, pt, n);

    int l = lcm1(pt, n);

    printf("PID\tCPU BT\tDeadline\tPeriod Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\n", p[i], b[i], d[i], pt[i]);
    }

    printf("Scheduling occurs for %d ms\n\n", l);

    int time = 0, prev = 0, idle = 0;
    int nextDeadlines[n];
    for (int i = 0; i < n; i++) {
        nextDeadlines[i] = d[i];
        rem[i] = b[i];
    }

    while (time < l) {
        for (int i = 0; i < n; i++) {
            if (time % pt[i] == 0 && time != 0) {
                nextDeadlines[i] = time + d[i];
                rem[i] = b[i];
            }
        }

        int minDeadline = l + 1;
        int taskToExecute = -1;
        for (int i = 0; i < n; i++) {
            if (rem[i] > 0 && nextDeadlines[i] < minDeadline) {
                minDeadline = nextDeadlines[i];
                taskToExecute = i;
            }
        }

        if (taskToExecute != -1) {
            printf("%dms: Task %d is running.\n", time, p[taskToExecute]);
            rem[taskToExecute]--;
            idle = 0;
        } else {
            if (!idle) {
                printf("%dms: CPU is idle.\n", time);
                idle = 1;
            }
        }

        time++;
    }

    return 0;
}
