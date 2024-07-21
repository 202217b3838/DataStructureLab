#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Linked List node
struct node {
    char* key;
    char* value;
    struct node* next;
};

// Function to initialize a new node
void setNode(struct node* node, char* key, char* value) {
    node->key = strdup(key); // Allocate memory and copy key
    node->value = strdup(value); // Allocate memory and copy value
    node->next = NULL;
}

// Hash Map structure
struct hashMap {
    int numOfElements, capacity;
    struct node** arr;
};

// Function to initialize the hash map
void initializeHashMap(struct hashMap* mp) {
    mp->capacity = 100;
    mp->numOfElements = 0;
    mp->arr = (struct node**)malloc(sizeof(struct node*) * mp->capacity);
    for (int i = 0; i < mp->capacity; i++) {
        mp->arr[i] = NULL;
    }
}

// Hash function to calculate bucket index
int hashFunction(struct hashMap* mp, char* key) {
    int bucketIndex;
    int sum = 0, factor = 31;
    for (int i = 0; i < strlen(key); i++) {
        sum = (sum + ((int)key[i] * factor)) % mp->capacity;
        factor = (factor * 31) % __INT16_MAX__;
    }
    bucketIndex = sum % mp->capacity;
    return bucketIndex;
}

// Function to insert a key-value pair into the hash map
void insert(struct hashMap* mp, char* key, char* value) {
    int bucketIndex = hashFunction(mp, key);
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    setNode(newNode, key, value);

    if (mp->arr[bucketIndex] == NULL) {
        mp->arr[bucketIndex] = newNode;
    } else {
        newNode->next = mp->arr[bucketIndex];
        mp->arr[bucketIndex] = newNode;
    }
    mp->numOfElements++;
}

// Function to delete a key from the hash map
void delete(struct hashMap* mp, char* key) {
    int bucketIndex = hashFunction(mp, key);
    struct node* prevNode = NULL;
    struct node* currNode = mp->arr[bucketIndex];

    while (currNode != NULL) {
        if (strcmp(key, currNode->key) == 0) {
            if (prevNode == NULL) {
                mp->arr[bucketIndex] = currNode->next;
            } else {
                prevNode->next = currNode->next;
            }
            free(currNode->key);
            free(currNode->value);
            free(currNode);
            mp->numOfElements--;
            return;
        }
        prevNode = currNode;
        currNode = currNode->next;
    }
}

// Function to search for a value associated with a key
char* search(struct hashMap* mp, char* key) {
    int bucketIndex = hashFunction(mp, key);
    struct node* bucketHead = mp->arr[bucketIndex];
    while (bucketHead != NULL) {
        if (strcmp(bucketHead->key, key) == 0) {
            return bucketHead->value;
        }
        bucketHead = bucketHead->next;
    }
    return "Oops! No data found.\n";
}

// Main function to test the hash map
int main() {
    struct hashMap* mp = (struct hashMap*)malloc(sizeof(struct hashMap));
    initializeHashMap(mp);

    insert(mp, "Yogaholic", "Anjali");
    insert(mp, "pluto14", "Vartika");
    insert(mp, "elite_Programmer", "Manish");
    insert(mp, "GFG", "BITS");
    insert(mp, "decentBoy", "Mayank");

    printf("%s\n", search(mp, "elite_Programmer"));
    printf("%s\n", search(mp, "Yogaholic"));
    printf("%s\n", search(mp, "pluto14"));
    printf("%s\n", search(mp, "decentBoy"));
    printf("%s\n", search(mp, "GFG"));
    printf("%s\n", search(mp, "randomKey"));

    printf("\nAfter deletion:\n");
    delete(mp, "decentBoy");
    printf("%s\n", search(mp, "decentBoy"));

    // Free memory for the hash map
    for (int i = 0; i < mp->capacity; i++) {
        struct node* currNode = mp->arr[i];
        while (currNode != NULL) {
            struct node* nextNode = currNode->next;
            free(currNode->key);
            free(currNode->value);
            free(currNode);
            currNode = nextNode;
        }
    }
    free(mp->arr);
    free(mp);

    return 0;
}
