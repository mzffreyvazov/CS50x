#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_TABLE_SIZE 10

struct KeyValuePair {
    char key[20];
    struct KeyValuePair *next;
};

struct HashTable {
    struct KeyValuePair *table[HASH_TABLE_SIZE];
};

unsigned int hash(const char* key) {
    unsigned int hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash = (hash * 31) + key[i];
    }
    return hash % HASH_TABLE_SIZE;
}

void initHashTable(struct HashTable* ht) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
}

void insert(struct HashTable* ht, const char* key) {
    unsigned int index = hash(key);

    struct KeyValuePair* newPair = (struct KeyValuePair*)malloc(sizeof(struct KeyValuePair));
    strcpy(newPair->key, key);
    newPair->next = NULL;

    // check if there is a collision
    if (ht->table[index] != NULL) {
        struct KeyValuePair* currentPair = ht->table[index];
        while (currentPair->next != NULL) {
            currentPair = currentPair->next;
        }
        currentPair->next = newPair;
    } else {
        ht->table[index] = newPair;
    }
}

int main() {
    struct HashTable ht;
    initHashTable(&ht);

    insert(&ht, "apple");
    insert(&ht, "banana");
    insert(&ht, "orange");

    printf("Hash Table:\n");
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        struct KeyValuePair* currentPair = ht.table[i];
        if (currentPair != NULL) {
            printf("[%d]: ", i);
            while (currentPair != NULL) {
                printf("(%s) ", currentPair->key);
                currentPair = currentPair->next;
            }
            printf("\n");
        } else {
            printf("[%d]: ---\n", i);
        }
    }

    // Free the memory occupied by the hash table
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        struct KeyValuePair* currentPair = ht.table[i];
        while (currentPair != NULL) {
            struct KeyValuePair* temp = currentPair;
            currentPair = currentPair->next;
            free(temp);
        }
    }

    return 0;
}


        // // Check if there's a collision
        // if (table[hash_value] != NULL) {
        //     node *currentPair = table[hash_value];
        //     while (currentPair->next != NULL) {
        //         currentPair = currentPair->next;
        //     }
        //     currentPair->next = newNode;
        // } else {
        //     table[hash_value] = newNode;
        // }