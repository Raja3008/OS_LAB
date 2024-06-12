#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int n, total_tickets = 0;
    float total_T = 0.0;

    printf("Enter the number of Processes: ");
    scanf("%d", &n);

    char process_names[n][5];
    int tickets[n];

    srand(time(NULL));

    for (int i = 0; i < n; i++)
    {
        printf("\nProcess %d:\n", i + 1);
        sprintf(process_names[i], "P%d", i + 1);
        printf("Tickets: ");
        scanf("%d", &tickets[i]);
        total_tickets += tickets[i];
        total_T += tickets[i];
    }

    printf("\n--- Proportional Share Scheduling ---\n");
    printf("Enter the Time Period for scheduling: ");
    int m;
    scanf("%d", &m);

    for (int i = 0; i < m; i++)
    {
        int winning_ticket = rand() % total_tickets + 1;
        int accumulated_tickets = 0;
        int winner_index = 0;

        for (int j = 0; j < n; j++)
        {
            accumulated_tickets += tickets[j];
            if (winning_ticket <= accumulated_tickets)
            {
                winner_index = j;
                break;
            }
        }

        printf("Tickets picked: %d, Winner: %s\n", winning_ticket, process_names[winner_index]);
    }

    for (int i = 0; i < n; i++)
    {
        printf("\nThe Process: %s gets %.2f%% of Processor Time.\n", process_names[i], ((tickets[i] / total_T) * 100));
    }

    return 0;
}
