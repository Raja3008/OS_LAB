#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sort(int p[], int b[], int pt[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (pt[j] < pt[i]) {
                swap(&pt[i], &pt[j]);
                swap(&b[i], &b[j]);
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

    int p[n], b[n], pt[n], rem[n];
    printf("Enter the CPU burst times:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &b[i]);
        rem[i] = b[i];
    }

    printf("Enter the time periods:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pt[i]);
    }

    for (int i = 0; i < n; i++) {
        p[i] = i + 1;
    }

    sort(p, b, pt, n);

    int lcm = lcm1(pt, n);
    printf("LCM = %d\n", lcm);

    printf("PID\tCPU BT\tPeriod Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\n", p[i], b[i], pt[i]);
    }

    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += (double)b[i] / pt[i];
    }

    double rhs = n * (pow(2.0, (1.0 / n)) - 1.0);
    printf("\n%lf <= %lf => %s\n", sum, rhs, (sum <= rhs) ? "true" : "false");

    if (sum > rhs) {
        printf("The set of processes is not schedulable under Rate Monotonic Scheduling.\n");
        return 0;
    }

    printf("Scheduling occurs for %d ms\n\n", lcm);

    int time = 0, prev = 0, idle = 0;
    while (time < lcm) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (time % pt[i] == 0) {
                rem[i] = b[i];
            }
            if (rem[i] > 0) {
                if (prev != p[i]) {
                    printf("%dms onwards: proess %d running\n", time, p[i]);
                    prev = p[i];
                }
                rem[i]--;
                found = 1;
                idle = 0;
                break;
            }
        }
        if (!found && !idle) {
            printf("%dms onwards: CPU is idle\n", time);
            idle = 1;
        }
        time++;
    }

    return 0;
}
