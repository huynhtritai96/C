### Linked List in C

A **linked list** is a dynamic data structure used in C programming to store a sequence of elements. Unlike arrays, which have a fixed size, linked lists can dynamically grow and shrink. Each element in a linked list is a **node**, and each node contains:
1. **Data**: The actual information or value stored in the node.
2. **Pointer to the next node**: A reference (or pointer) that points to the next node in the sequence.

There are different types of linked lists:
1. **Singly Linked List**: Each node points to the next node in the list.
2. **Doubly Linked List**: Each node points to both the next node and the previous node.
3. **Circular Linked List**: The last node points back to the first node, forming a circle.

In this example, I will show how to implement a **singly linked list** in C.

### Singly Linked List Implementation

```c
#include <stdio.h>
#include <stdlib.h>

// Define the node structure
struct Node {
    int data;              // Data to be stored in the node
    struct Node* next;     // Pointer to the next node
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the beginning of the linked list
void insertAtBeginning(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

// Function to insert a node at the end of the linked list
void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Function to delete a node by value
void deleteNode(struct Node** head, int data) {
    struct Node* temp = *head, *prev = NULL;
    
    if (temp != NULL && temp->data == data) {
        *head = temp->next; // Head now points to the next node
        free(temp);
        return;
    }
    
    while (temp != NULL && temp->data != data) {
        prev = temp;
        temp = temp->next;
    }
    
    if (temp == NULL) {
        printf("Node with value %d not found.\n", data);
        return;
    }

    prev->next = temp->next;
    free(temp);
}

// Function to display the linked list
void displayList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Main function to test the linked list
int main() {
    struct Node* head = NULL;

    insertAtBeginning(&head, 3);
    insertAtBeginning(&head, 2);
    insertAtBeginning(&head, 1);
    
    printf("Linked List after inserting 1, 2, 3 at the beginning:\n");
    displayList(head);

    insertAtEnd(&head, 4);
    insertAtEnd(&head, 5);

    printf("Linked List after inserting 4, 5 at the end:\n");
    displayList(head);

    deleteNode(&head, 3);
    printf("Linked List after deleting node with value 3:\n");
    displayList(head);

    return 0;
}
```

### Explanation of the Code:

1. **Node Structure**: 
   ```c
   struct Node {
       int data;
       struct Node* next;
   };
   ```
   Each node in the linked list contains an integer (`data`) and a pointer to the next node (`next`).

2. **Creating a New Node**:
   ```c
   struct Node* createNode(int data) {
       struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
       newNode->data = data;
       newNode->next = NULL;
       return newNode;
   }
   ```
   This function dynamically allocates memory for a new node and initializes the data and next pointer.

3. **Inserting at the Beginning**:
   ```c
   void insertAtBeginning(struct Node** head, int data) {
       struct Node* newNode = createNode(data);
       newNode->next = *head;
       *head = newNode;
   }
   ```
   This function inserts a new node at the start of the linked list. It updates the `next` pointer of the new node to point to the current head, and then updates the head to point to the new node.

4. **Inserting at the End**:
   ```c
   void insertAtEnd(struct Node** head, int data) {
       struct Node* newNode = createNode(data);
       if (*head == NULL) {
           *head = newNode;
           return;
       }
       struct Node* temp = *head;
       while (temp->next != NULL) {
           temp = temp->next;
       }
       temp->next = newNode;
   }
   ```
   This function inserts a node at the end of the linked list. If the list is empty, it sets the new node as the head. Otherwise, it traverses the list to find the last node and updates its `next` pointer.

5. **Deleting a Node by Value**:
   ```c
   void deleteNode(struct Node** head, int data) {
       struct Node* temp = *head, *prev = NULL;
       
       if (temp != NULL && temp->data == data) {
           *head = temp->next;
           free(temp);
           return;
       }
       
       while (temp != NULL && temp->data != data) {
           prev = temp;
           temp = temp->next;
       }
       
       if (temp == NULL) {
           printf("Node with value %d not found.\n", data);
           return;
       }
       
       prev->next = temp->next;
       free(temp);
   }
   ```
   This function searches for a node with the given value and removes it from the list.

6. **Displaying the List**:
   ```c
   void displayList(struct Node* head) {
       struct Node* temp = head;
       while (temp != NULL) {
           printf("%d -> ", temp->data);
           temp = temp->next;
       }
       printf("NULL\n");
   }
   ```
   This function traverses the list and prints each node's data.

### Output:
```
Linked List after inserting 1, 2, 3 at the beginning:
1 -> 2 -> 3 -> NULL
Linked List after inserting 4, 5 at the end:
1 -> 2 -> 3 -> 4 -> 5 -> NULL
Linked List after deleting node with value 3:
1 -> 2 -> 4 -> 5 -> NULL
```

This example demonstrates the basic operations on a singly linked list. You can modify or expand the linked list to handle more complex operations (e.g., searching, reversing the list, etc.).