#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *right_child;
    struct node *left_child;
};

// Function to create a new node
struct node* new_node(int x) {
    struct node *temp = (struct node*)malloc(sizeof(struct node));
    temp->data = x;
    temp->left_child = NULL;
    temp->right_child = NULL;
    return temp;
}

// Function to search for a value in the BST
struct node* search(struct node *root, int x) {
    if (root == NULL || root->data == x)
        return root;
    else if (x > root->data)
        return search(root->right_child, x);
    else
        return search(root->left_child, x);
}

// Function to insert a value into the BST
struct node* insert(struct node *root, int x) {
    if (root == NULL)
        return new_node(x);
    else if (x > root->data)
        root->right_child = insert(root->right_child, x);
    else
        root->left_child = insert(root->left_child, x);
    return root;
}

// Function to find the minimum value node in a subtree
struct node* find_minimum(struct node *root) {
    while (root && root->left_child != NULL)
        root = root->left_child;
    return root;
}

// Function to delete a node from the BST
struct node* delete(struct node *root, int x) {
    if (root == NULL)
        return NULL;
    
    if (x > root->data)
        root->right_child = delete(root->right_child, x);
    else if (x < root->data)
        root->left_child = delete(root->left_child, x);
    else {
        // Node with only one child or no child
        if (root->left_child == NULL) {
            struct node *temp = root->right_child;
            free(root);
            return temp;
        } else if (root->right_child == NULL) {
            struct node *temp = root->left_child;
            free(root);
            return temp;
        }
        
        // Node with two children: Get the inorder successor (smallest in the right subtree)
        struct node *temp = find_minimum(root->right_child);
        root->data = temp->data;
        root->right_child = delete(root->right_child, temp->data);
    }
    return root;
}

// Function to perform inorder traversal of the BST
void inorder(struct node *root) {
    if (root != NULL) {
        inorder(root->left_child);
        printf(" %d ", root->data);
        inorder(root->right_child);
    }
}

// Driver code
int main() {
    struct node *root = NULL;

    root = insert(root, 20);
    insert(root, 5);
    insert(root, 1);
    insert(root, 15);
    insert(root, 9);
    insert(root, 7);
    insert(root, 12);
    insert(root, 30);
    insert(root, 25);
    insert(root, 40);
    insert(root, 45);
    insert(root, 42);

    printf("Inorder traversal before deletion:\n");
    inorder(root);
    printf("\n");

    root = delete(root, 1);
    root = delete(root, 40);
    root = delete(root, 45);
    root = delete(root, 9);

    printf("Inorder traversal after deletion:\n");
    inorder(root);
    printf("\n");

    return 0;
}
