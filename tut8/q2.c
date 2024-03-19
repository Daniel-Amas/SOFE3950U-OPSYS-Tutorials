#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MEMORY 1024

typedef struct {
    char name[256];
    int priority;
    int pid;
    int address;
    int memory;
    int runtime;
    bool suspended;
} Proc;

typedef struct {
    Proc array[MEMORY];
    int front, rear, size;
} Queue;

void initializeQueue(Queue *q) {
    q->front = q->rear = q->size = 0;
}

bool isEmpty(Queue *q) {
    return q->size == 0;
}

void push(Queue *q, Proc data) {
    if (q->size == MEMORY) {
        printf("Queue is full\n");
        return;
    }
    q->array[q->rear++] = data;
    q->rear %= MEMORY;
    q->size++;
}

Proc pop(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        exit(EXIT_FAILURE);
    }
    Proc data = q->array[q->front++];
    q->front %= MEMORY;
    q->size--;
    return data;
}

void executeProcess(Proc process, int avail_mem[]) {
    printf("Executing process:\n");
    printf("Name: %s\n", process.name);
    printf("Priority: %d\n", process.priority);
    printf("Memory: %d\n", process.memory);
    printf("Runtime: %d\n", process.runtime);
    
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Child process
        // Execute process binary here using exec
        printf("Executing %s\n", process.name);
        sleep(process.runtime);
        printf("%s completed.\n", process.name);
        exit(EXIT_SUCCESS);
    } else { // Parent process
        process.pid = pid;
        process.address = -1; // Update with the actual memory address
        avail_mem[process.address] = 1; // Mark memory as used
        waitpid(pid, NULL, 0); // Wait for child process to finish
        avail_mem[process.address] = 0; // Free the memory
    }
}

int main() {
    Queue priority, secondary;
    initializeQueue(&priority);
    initializeQueue(&secondary);
    int avail_mem[MEMORY] = {0};

    FILE *file = fopen("processes_q2.txt", "r");
    if (!file) {
        printf("Error opening file.\n");
        return EXIT_FAILURE;
    }

    Proc temp;
    while (fscanf(file, "%255[^,], %d, %d, %d\n", temp.name, &temp.priority, &temp.memory, &temp.runtime) == 4) {
        temp.pid = 0;
        temp.address = 0;
        temp.suspended = false;
        if (temp.priority == 0)
            push(&priority, temp);
        else
            push(&secondary, temp);
    }
    fclose(file);

    while (!isEmpty(&priority)) {
        Proc process = pop(&priority);
        executeProcess(process, avail_mem);
    }

    while (!isEmpty(&secondary)) {
        Proc process = pop(&secondary);
        // Check if enough memory is available
        if (process.memory <= MEMORY) {
            executeProcess(process, avail_mem);
        } else {
            printf("Insufficient memory for %s, pushing it back to the queue.\n", process.name);
            push(&secondary, process);
        }
    }

    return 0;
}
