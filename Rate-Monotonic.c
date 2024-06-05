#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to swap elements in arrays
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to sort processes by their periods
void sort(int proc[], int b[], int pt[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (pt[j] < pt[i]) {
                swap(&pt[i], &pt[j]);
                swap(&b[i], &b[j]);
                swap(&proc[i], &proc[j]);
            }
        }
    }
}

// Function to compute the greatest common divisor
int gcd(int a, int b) {
    while (b > 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

// Function to compute the least common multiple
int lcmul(int p[], int n) {
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

    int proc[n], b[n], pt[n], rem[n];
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
        proc[i] = i + 1;
    }

    // Sort processes by periods
    sort(proc, b, pt, n);

    // Calculate LCM of periods
    int lcm = lcmul(pt, n);
    printf("LCM = %d\n", lcm);

    // Display process information
    printf("\nRate Monotone Scheduling:\n");
    printf("PID\tBurst\tPeriod\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\n", proc[i], b[i], pt[i]);
    }

    // Feasibility check
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

    // Rate Monotonic Scheduling
    int time = 0, prev = 0, idle = 0;
    while (time < lcm) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (time % pt[i] == 0) {
                rem[i] = b[i];
            }
            if (rem[i] > 0) {
                if (prev != proc[i]) {
                    printf("%dms onwards: Process %d running\n", time, proc[i]);
                    prev = proc[i];
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
