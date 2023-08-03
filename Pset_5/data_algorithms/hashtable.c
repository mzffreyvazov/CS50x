#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the maximum size of the hash table
#define HASH_TABLE_SIZE 10

// Define the structure for each key-value pair
struct KeyValuePair {
    char key[20];
    int value;
    struct KeyValuePair *next;
};

// Define the hash table structure
struct HashTable {
    struct KeyValuePair *table[HASH_TABLE_SIZE];
};

// Function to compute the hash value of a key
unsigned int hash(const char* key) {
    unsigned int hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash = (hash * 31) + key[i];
    }
    return hash % HASH_TABLE_SIZE;
}

// Function to initialize the hash table
void initHashTable(struct HashTable* ht) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
}

// Function to insert a key-value pair into the hash table
void insert(struct HashTable* ht, const char* key, int value) {
    unsigned int index = hash(key);

    // Create a new key-value pair
    struct KeyValuePair* newPair = (struct KeyValuePair*)malloc(sizeof(struct KeyValuePair));
    strcpy(newPair->key, key);
    newPair->value = value;

    // Check if there's already a key-value pair at the given index
    if (ht->table[index] != NULL) {
        // Collision occurred, handle it (e.g., chaining)
        struct KeyValuePair* currentPair = ht->table[index];
        while (currentPair->next != NULL) {
            currentPair = currentPair->next;
        }
        currentPair->next = newPair;
    } else {
        ht->table[index] = newPair;
    }
}

// Function to retrieve a value based on a given key
int get(struct HashTable* ht, const char* key) {
    unsigned int index = hash(key);

    // Check if the key-value pair exists at the given index
    if (ht->table[index] != NULL) {
        // Search for the key in the chain, if it's a collision
        struct KeyValuePair* currentPair = ht->table[index];
        while (currentPair != NULL) {
            if (strcmp(currentPair->key, key) == 0) {
                return currentPair->value;
            }
            currentPair = currentPair->next;
        }
    }

    // Key not found
    return -1;
}

// Function to free the memory occupied by the hash table
void destroyHashTable(struct HashTable* ht) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        struct KeyValuePair* currentPair = ht->table[i];
        while (currentPair != NULL) {
            struct KeyValuePair* temp = currentPair;
            currentPair = currentPair->next;
            free(temp);
        }
    }
}

int main() {
    struct HashTable ht;
    initHashTable(&ht);

    // Insert some key-value pairs into the hash table
    insert(&ht, "apple", 55);
    insert(&ht, "banana", 73);
    insert(&ht, "orange", 17);

    // Print the whole hash table with indexes and items
    printf("Hash Table:\n");
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        struct KeyValuePair* currentPair = ht.table[i];
        if (currentPair != NULL) {
            printf("[%d]: ", i);
            while (currentPair != NULL) {
                printf("(%s, %d) ", currentPair->key, currentPair->value);
                currentPair = currentPair->next;
            }
            printf("\n");
        } else {
            printf("[%d]: ---\n", i);
        }
    }

    // Retrieve values from the hash table
    printf("Retrieved Values:\n");
    printf("apple [%d]: %d\n", hash("apple"), get(&ht, "apple"));
    printf("banana [%d]: %d\n", hash("banana"), get(&ht, "banana"));
    printf("orange [%d]: %d\n", hash("orange"), get(&ht, "orange"));

    // Free the memory occupied by the hash table
    destroyHashTable(&ht);

    return 0;
}

