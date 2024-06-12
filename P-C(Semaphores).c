#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFFER_SIZE 10

int mutex = 1;
int full = 0;
int empty = BUFFER_SIZE;
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

void wait(int *s) {
    while (*s <= 0)
        ;
    (*s)--;
}

void signal(int *s) {
    (*s)++;
}

void producer() {
    wait(&mutex);

    int item = rand();
    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;

    full++;
    empty--;

    printf("\nProducer produces item %d\n", item);

    signal(&mutex);
}

void consumer() {
    wait(&mutex);

    int item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;

    full--;
    empty++;

    printf("\nConsumer consumes item %d\n", item);

    signal(&mutex);
}

int main() {
    int choice;

    printf("1. Press 1 for Producer\n");
    printf("2. Press 2 for Consumer\n");
    printf("3. Press 3 for Exit\n");

    while (true) {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            if (mutex == 1 && empty > 0) {
                producer();
            } else {
                printf("Buffer is full!\n");
            }
            break;

        case 2:
            if (mutex == 1 && full > 0) {
                consumer();
            } else {
                printf("Buffer is empty!\n");
            }
            break;

        case 3:
            exit(0);

        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}
