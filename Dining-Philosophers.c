#include <stdio.h>
#include <stdlib.h>

#define MAX_PHILOSOPHERS 5

void allow_one_to_eat(int hungry[], int n) {

    int isWaiting[MAX_PHILOSOPHERS];
    for (int i = 0; i < n; i++) {
        isWaiting[i] = 1;
    }

    for (int i = 0; i < n; i++) {
        printf("P %d is granted to eat\n", hungry[i]);
        isWaiting[hungry[i]] = 0;
        for (int j = 0; j < n; j++) {
            if (isWaiting[hungry[j]]) {
                printf("P %d is waiting\n", hungry[j]);
            }
        }

        for (int k = 0; k < n; k++) {
            isWaiting[k] = 1;
        }
        isWaiting[hungry[i]] = 0;
    }
}

void allow_two_to_eat(int hungry[], int n) {

    if (n < 2 || n > MAX_PHILOSOPHERS) {
        printf("Invalid number of philosophers.\n");
        return;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            printf("P %d and P %d are granted to eat\n", hungry[i], hungry[j]);

            for (int k = 0; k < n; k++) {
                if (k != i && k != j) {
                    printf("P %d is waiting\n", hungry[k]);
                }
            }
        }
    }
}

int main() {
    int total_philosophers, hungry_count;
    int hungry_positions[MAX_PHILOSOPHERS];

    printf("DINING PHILOSOPHER PROBLEM\n");
    printf("Enter the total no. of philosophers: ");
    scanf("%d", &total_philosophers);

    if (total_philosophers > MAX_PHILOSOPHERS || total_philosophers < 2) {
        printf("Invalid number of philosophers.\n");
        return 1;
    }

    printf("How many are hungry: ");
    scanf("%d", &hungry_count);

    if (hungry_count < 1 || hungry_count > total_philosophers) {
        printf("Invalid number of hungry philosophers.\n");
        return 1;
    }

    for (int i = 0; i < hungry_count; i++) {
        printf("Enter philosopher %d position: ", i + 1);
        scanf("%d", &hungry_positions[i]);

        if (hungry_positions[i] < 0 || hungry_positions[i] >= total_philosophers) {
            printf("Invalid philosopher position.\n");
            return 1;
        }
    }

    int choice;
    while (1) {
        printf("\n1. One can eat at a time\n");
        printf("2. Two can eat at a time\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                allow_one_to_eat(hungry_positions, hungry_count);
                break;
            case 2:
                allow_two_to_eat(hungry_positions, hungry_count);
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
