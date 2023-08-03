#include <stdio.h>
#include <stdlib.h>

// Define the structure for a linked list node
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node with the given data
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode != NULL) {
        newNode->data = data;
        newNode->next = NULL;
    }
    return newNode;
}

// Function to insert a new node at the beginning of the linked list
void insertAtBeginning(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (newNode != NULL) {
        newNode->next = *head;
        *head = newNode;
    } else {
        printf("Memory allocation failed. Unable to insert node.\n");
    }
}

// Function to insert a new node at the end of the linked list
void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (newNode != NULL) {
        if (*head == NULL) {
            *head = newNode;
        } else {
            struct Node* temp = *head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    } else {
        printf("Memory allocation failed. Unable to insert node.\n");
    }
}

// Function to delete the first occurrence of a node with the given data
void deleteNode(struct Node** head, int data) {
    if (*head == NULL) {
        printf("Linked list is empty. Unable to delete node.\n");
        return;
    }

    struct Node* temp = *head;
    struct Node* prev = NULL;

    while (temp != NULL) {
        if (temp->data == data) {
            if (prev != NULL) {
                prev->next = temp->next;
            } else {
                *head = temp->next;
            }
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    printf("Node with data %d not found in the linked list.\n", data);
}

// Function to display the linked list
void displayList(struct Node* head) {
    struct Node* temp = head;
    printf("Linked list: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Function to free the memory occupied by the linked list
void destroyList(struct Node** head) {
    struct Node* temp;
    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

int main() {
    struct Node* head = NULL;

    // Insert nodes at the beginning of the linked list
    insertAtBeginning(&head, 3);
    insertAtBeginning(&head, 2);
    insertAtBeginning(&head, 1);

    // Display the linked list
    displayList(head);

    // Insert nodes at the end of the linked list
    insertAtEnd(&head, 4);
    insertAtEnd(&head, 5);

    // Display the linked list
    displayList(head);

    // Delete a node from the linked list
    deleteNode(&head, 2);

    // Display the linked list after deletion
    displayList(head);

    // Free the memory occupied by the linked list
    destroyList(&head);

    return 0;
}
