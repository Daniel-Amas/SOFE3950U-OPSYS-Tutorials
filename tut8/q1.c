#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

// Define a structure for process
typedef struct {
    char parent[256];
    char name[256];
    int priority;
    int memory;
} proc;

// Define a structure for binary tree node
typedef struct node {
    proc data;
    struct node *left;
    struct node *right;
} node;

// Function to create a new node
node *createNode(proc data) {
    node *newNode = (node *)malloc(sizeof(node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a node into the binary tree
node *insertNode(node *root, proc data) {
    if (root == NULL)
        return createNode(data);
    
    // Traverse left or right based on comparison with parent name
    if (strcmp(data.parent, root->data.name) < 0)
        root->left = insertNode(root->left, data);
    else
        root->right = insertNode(root->right, data);

    return root;
}

// Function to print the binary tree using inorder traversal
void printTree(node *root) {
    if (root != NULL) {
        printTree(root->left);
        printf("Parent: %s, Name: %s, Priority: %d, Memory: %d\n", root->data.parent, root->data.name, root->data.priority, root->data.memory);
        printTree(root->right);
    }
}

int main(void) {
    FILE *file = fopen("processes_tree.txt", "r");
    if (file == NULL) {
        printf("Failed to open file\n");
        return EXIT_FAILURE;
    }

    // Initialize root of the binary tree
    node *root = NULL;
    char line[512];

    // Read file line by line
    while (fgets(line, sizeof(line), file) != NULL) {
        proc newProc;
        sscanf(line, "%[^,],%[^,],%d,%d", newProc.parent, newProc.name, &newProc.priority, &newProc.memory);
        root = insertNode(root, newProc);
    }

    fclose(file);

    // Print the contents of the binary tree
    printf("Binary Tree Contents:\n");
    printTree(root);

    // Free memory allocated for the binary tree
    return 0;
}
