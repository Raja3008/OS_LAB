#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

void getInput(int processes, int resources, int max[MAX_PROCESSES][MAX_RESOURCES], int allocation[MAX_PROCESSES][MAX_RESOURCES], int available[MAX_RESOURCES]) {
    printf("Enter the allocation for each process:\n");
    for (int i = 0; i < processes; i++) {
        printf("Process %d:\n", i);
        for (int j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the request for each process:\n");
    for (int i = 0; i < processes; i++) {
        printf("Process %d:\n", i);
        for (int j = 0; j < resources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the available resources:\n");
    for (int j = 0; j < resources; j++) {
        scanf("%d", &available[j]);
    }
}

bool isSafe(int processes, int resources, int max[MAX_PROCESSES][MAX_RESOURCES], int allocation[MAX_PROCESSES][MAX_RESOURCES], int available[MAX_RESOURCES], int safeSequence[MAX_PROCESSES]) {
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {false};
    int need[MAX_PROCESSES][MAX_RESOURCES];

    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }

    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    int count = 0;
    while (count < processes) {
        bool found = false;
        for (int i = 0; i < processes; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < resources; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < resources; j++) {
                        work[j] += allocation[i][j];
                    }
                    safeSequence[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            break;
        }
    }

    for (int i = 0; i < processes; i++) {
        if (!finish[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    int processes, resources;
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int available[MAX_RESOURCES];
    int safeSequence[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &processes);

    printf("Enter the number of resources: ");
    scanf("%d", &resources);

    getInput(processes, resources, max, allocation, available);

    if (isSafe(processes, resources, max, allocation, available, safeSequence)) {
        printf("The system is in a safe state.\nSafe sequence is: ");
        for (int i = 0; i < processes; i++) {
            printf("P%d ", safeSequence[i]);
        }
        printf("\n");
    } else {
        printf("The system is in a deadlock state.\n");
    }

    return 0;
}
