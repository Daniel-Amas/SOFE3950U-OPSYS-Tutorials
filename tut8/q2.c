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

typedef struct node {
    Proc data;
    struct node *left;
    struct node *right;
} Node;

typedef struct {
    Node *root;
} BinaryTree;

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

void insertNode(BinaryTree *tree, Proc data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;

    if (tree->root == NULL) {
        tree->root = newNode;
        return;
    }

    Node *current = tree->root;
    while (1) {
        if (strcmp(data.name, current->data.name) < 0) {
            if (current->left == NULL) {
                current->left = newNode;
                break;
            }
            current = current->left;
        } else {
            if (current->right == NULL) {
                current->right = newNode;
                break;
            }
            current = current->right;
        }
    }
}

void printTree(Node *root) {
    if (root != NULL) {
        printf("Parent: %s\n", root->data.name);
        printf("Children: ");
        if (root->left != NULL) printf("%s ", root->left->data.name);
        if (root->right != NULL) printf("%s", root->right->data.name);
        printf("\n\n");
        printTree(root->left);
        printTree(root->right);
    }
}

int main() {
    FILE *file = fopen("processes_tree.txt", "r");
    if (!file) {
        printf("Error opening file.\n");
        return EXIT_FAILURE;
    }

    BinaryTree tree = {NULL};
    Proc temp;
    char parent[256];

    while (fscanf(file, "%s %s %d %d", parent, temp.name, &temp.priority, &temp.memory) == 4) {
        if (strcmp(parent, "NULL") == 0) {
            tree.root = (Node *)malloc(sizeof(Node));
            tree.root->data = temp;
            tree.root->left = tree.root->right = NULL;
        } else {
            insertNode(&tree, temp);
        }
    }
    fclose(file);

    printf("Printing tree:\n\n");
    printTree(tree.root);

    return 0;
}
