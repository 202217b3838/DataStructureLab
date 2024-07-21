#include <stdio.h>

#define MAX_NODES 15

char tree[] = {'\0', 'D', 'A', 'F', 'E', 'B', 'R', 'T', 'G', 'Q', '\0', '\0', 'V', '\0', 'J', 'L'};

// Function to get the index of the right child
int get_right_child(int index) {
    if (index > 0 && index <= MAX_NODES) {
        int right_child_index = (2 * index) + 1;
        if (right_child_index <= MAX_NODES && tree[right_child_index] != '\0') {
            return right_child_index;
        }
    }
    return -1;
}

// Function to get the index of the left child
int get_left_child(int index) {
    if (index > 0 && index <= MAX_NODES) {
        int left_child_index = 2 * index;
        if (left_child_index <= MAX_NODES && tree[left_child_index] != '\0') {
            return left_child_index;
        }
    }
    return -1;
}

// Preorder Traversal: Root, Left, Right
void preorder(int index) {
    if (index > 0 && index <= MAX_NODES && tree[index] != '\0') {
        printf(" %c ", tree[index]);
        preorder(get_left_child(index));
        preorder(get_right_child(index));
    }
}

// Postorder Traversal: Left, Right, Root
void postorder(int index) {
    if (index > 0 && index <= MAX_NODES && tree[index] != '\0') {
        postorder(get_left_child(index));
        postorder(get_right_child(index));
        printf(" %c ", tree[index]);
    }
}

// Inorder Traversal: Left, Root, Right
void inorder(int index) {
    if (index > 0 && index <= MAX_NODES && tree[index] != '\0') {
        inorder(get_left_child(index));
        printf(" %c ", tree[index]);
        inorder(get_right_child(index));
    }
}

int main() {
    printf("Preorder:\n");
    preorder(1);
    printf("\nPostorder:\n");
    postorder(1);
    printf("\nInorder:\n");
    inorder(1);
    printf("\n");

    return 0;
}
