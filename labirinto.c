#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 5

typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void insertRandom(Node* root, int value) {
    if (rand() % 2 == 0) {
        if (root->left == NULL) {
            root->left = createNode(value);
        } else {
            insertRandom(root->left, value);
        }
    } else {
        if (root->right == NULL) {
            root->right = createNode(value);
        } else {
            insertRandom(root->right, value);
        }
    }
}

void generateMaze(Node* root, int maze[SIZE][SIZE]) {
    if (root != NULL) {
        int x = rand() % SIZE;
        int y = rand() % SIZE;

        maze[x][y] = 0;  // Mark cell as part of the maze

        if (x > 0 && maze[x - 1][y] != 0) {
            maze[x - 1][y] = 0;  // Connect to the left cell
            generateMaze(root->left, maze);
        }

        if (y > 0 && maze[x][y - 1] != 0) {
            maze[x][y - 1] = 0;  // Connect to the upper cell
            generateMaze(root->right, maze);
        }

        if (x < SIZE - 1 && maze[x + 1][y] != 0) {
            maze[x + 1][y] = 0;  // Connect to the right cell
            generateMaze(root->left, maze);
        }

        if (y < SIZE - 1 && maze[x][y + 1] != 0) {
            maze[x][y + 1] = 0;  // Connect to the lower cell
            generateMaze(root->right, maze);
        }
    }
}

int main() {
    srand(time(NULL));

    Node* root = createNode(1);

    int maze[SIZE][SIZE];

    // Initialize maze with walls
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            maze[i][j] = 1;
        }
    }

    generateMaze(root, maze);

    // Print the generated maze
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", maze[i][j]);
        }
        printf("\n");
    }

    return 0;
}
