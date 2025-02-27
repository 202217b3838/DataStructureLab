#include <stdio.h>
#include <stdlib.h>

// Node structure to define the structure of the node
typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

// Function to create a new node
Node* newNode(int val) {
    Node* temp = (Node*)malloc(sizeof(Node));
    if (!temp) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    temp->data = val;
    temp->left = temp->right = NULL;
    return temp;
}

// Function to insert nodes
Node* insert(Node* root, int data) {
    if (root == NULL) {
        return newNode(data);
    }

    Node** queue = (Node**)malloc(100 * sizeof(Node*)); // Queue for traversal
    int front = 0, rear = 0;
    queue[rear++] = root;
    
    while (front != rear) {
        Node* temp = queue[front++];
        
        if (temp->left == NULL) {
            temp->left = newNode(data);
            free(queue);
            return root;
        } else {
            queue[rear++] = temp->left;
        }

        if (temp->right == NULL) {
            temp->right = newNode(data);
            free(queue);
            return root;
        } else {
            queue[rear++] = temp->right;
        }
    }

    free(queue);
    return root;
}

// Function to delete the given deepest node (d_node) in binary tree
void deletDeepest(Node* root, Node* d_node) {
    if (root == NULL) {
        return;
    }

    Node** queue = (Node**)malloc(100 * sizeof(Node*)); // Queue for traversal
    int front = 0, rear = 0;
    queue[rear++] = root;
    Node* temp;

    while (front != rear) {
        temp = queue[front++];

        if (temp == d_node) {
            free(d_node);
            free(queue);
            return;
        }

        if (temp->right) {
            if (temp->right == d_node) {
                temp->right = NULL;
                free(d_node);
                free(queue);
                return;
            } else {
                queue[rear++] = temp->right;
            }
        }

        if (temp->left) {
            if (temp->left == d_node) {
                temp->left = NULL;
                free(d_node);
                free(queue);
                return;
            } else {
                queue[rear++] = temp->left;
            }
        }
    }

    free(queue);
}

// Function to delete element in binary tree
Node* deletion(Node* root, int key) {
    if (root == NULL) {
        return NULL;
    }

    if (root->left == NULL && root->right == NULL) {
        if (root->data == key) {
            free(root);
            return NULL;
        }
        return root;
    }

    Node** queue = (Node**)malloc(100 * sizeof(Node*)); // Queue for traversal
    int front = 0, rear = 0;
    queue[rear++] = root;
    Node* temp;
    Node* key_node = NULL;

    while (front != rear) {
        temp = queue[front++];
        if (temp->data == key) {
            key_node = temp;
        }

        if (temp->left) {
            queue[rear++] = temp->left;
        }

        if (temp->right) {
            queue[rear++] = temp->right;
        }
    }

    if (key_node) {
        int x = temp->data;
        key_node->data = x;
        deletDeepest(root, temp);
    }

    free(queue);
    return root;
}

// Inorder tree traversal (Left - Root - Right)
void inorderTraversal(Node* root) {
    if (!root) {
        return;
    }
    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}

// Preorder tree traversal (Root - Left - Right)
void preorderTraversal(Node* root) {
    if (!root) {
        return;
    }
    printf("%d ", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

// Postorder tree traversal (Left - Right - Root)
void postorderTraversal(Node* root) {
    if (root == NULL) {
        return;
    }
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%d ", root->data);
}

// Function for Level order tree traversal
void levelorderTraversal(Node* root) {
    if (root == NULL) {
        return;
    }

    Node** queue = (Node**)malloc(100 * sizeof(Node*)); // Queue for traversal
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front != rear) {
        Node* temp = queue[front++];
        printf("%d ", temp->data);

        if (temp->left) {
            queue[rear++] = temp->left;
        }

        if (temp->right) {
            queue[rear++] = temp->right;
        }
    }

    free(queue);
}

// Driver function to check the above algorithm
int main() {
    Node* root = NULL;

    // Insertion of nodes
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
  //  root = insert(root, 50); // Added for better example

    printf("Preorder traversal: ");
    preorderTraversal(root);
    printf("\nInorder traversal: ");
    inorderTraversal(root);
    printf("\nPostorder traversal: ");
    postorderTraversal(root);
    printf("\nLevel order traversal: ");
    levelorderTraversal(root);

    // Delete the node with data = 20
    root = deletion(root, 20);
    printf("\nInorder traversal after deletion: ");
    inorderTraversal(root);

    // Free allocated memory
    while (root != NULL) {
        root = deletion(root, root->data);
    }

    return 0;
}
