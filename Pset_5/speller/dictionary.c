// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include "dictionary.h"
#include <string.h>
#include <strings.h>
#include <stdlib.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int hash_value = hash(word);

    // Search for the key in the chain, if it's a collision
    node* newNode = table[hash_value];
    while (newNode != NULL) {
        if (strcasecmp(newNode->word, word) == 0) {
            return true;
        }
        newNode = newNode->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // unsigned int hash = 0;
    // for (int i = 0; word[i] != '\0'; i++) {
    //     hash = (hash * 31) + word[i];
    // }
    // return hash % N;

    unsigned long total = 0;
    for (int i = 0; i < strlen(word); i++) {
        total += tolower(word[i]);
    }
    return total % N;
    }

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open the dictionary file.
    FILE *file = fopen(dictionary, "r");

    // Check if the file was opened successfully.
    if (file == NULL) {
        printf("Failed to open %s file.\n", dictionary);
        return false;
    }


    // Read strings form the file
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        // Get the hash value for word word
        unsigned int hash_value = hash(word);

        // Create a new node for the word
        node *newNode = malloc(sizeof(node));
        if (newNode == NULL) {
            return false;
        }
        strcpy(newNode->word, word);
        newNode->next = table[hash_value];
        table[hash_value] = newNode;
        word_count++;

    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (word_count > 0) {
        return word_count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++) {
        node* currentNode = table[i];
        while (currentNode != NULL) {
            node* temp = currentNode;
            currentNode = currentNode->next;
            free(temp);

        }

    }
    return true;
}
