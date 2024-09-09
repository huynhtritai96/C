A **Doubly Linked List (DLL)** is a more complex type of linked list where each node contains references to both the next node and the previous node. This allows for traversing the list in both directions, which is a significant advantage over singly linked lists. Here's how we can implement a basic doubly linked list in C.

### Doubly Linked List Structure
Each node in a doubly linked list contains:
1. **Data**: The value stored in the node.
2. **Pointer to the previous node**.
3. **Pointer to the next node**.

### Doubly Linked List Implementation in C

```c
#include <stdio.h>
#include <stdlib.h>

// Define the structure for a doubly linked list node
struct Node {
    int data;              // Data stored in the node
    struct Node* prev;     // Pointer to the previous node
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
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the front of the list
void insertAtFront(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = *head;
    if (*head != NULL) {
        (*head)->prev = newNode;
    }
    *head = newNode;
}

// Function to insert a node at the end of the list
void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    struct Node* temp = *head;
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

// Function to delete a node from the doubly linked list
void deleteNode(struct Node** head, int data) {
    struct Node* temp = *head;

    while (temp != NULL && temp->data != data) {
        temp = temp->next;
    }
    
    if (temp == NULL) {
        printf("Node with value %d not found.\n", data);
        return;
    }

    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    } else {
        *head = temp->next;  // Head is being deleted
    }

    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }

    free(temp);
}

// Function to display the doubly linked list from the head to the end
void displayList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Function to display the list from the end to the head (reverse traversal)
void displayReverseList(struct Node* head) {
    if (head == NULL) return;

    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->prev;
    }
    printf("NULL\n");
}

// Main function to test the doubly linked list
int main() {
    struct Node* head = NULL;

    insertAtFront(&head, 3);
    insertAtFront(&head, 2);
    insertAtFront(&head, 1);

    printf("Doubly Linked List after inserting 1, 2, 3 at the front:\n");
    displayList(head);

    insertAtEnd(&head, 4);
    insertAtEnd(&head, 5);

    printf("Doubly Linked List after inserting 4, 5 at the end:\n");
    displayList(head);

    deleteNode(&head, 3);
    printf("Doubly Linked List after deleting node with value 3:\n");
    displayList(head);

    printf("Reverse traversal of the Doubly Linked List:\n");
    displayReverseList(head);

    return 0;
}
```

### Explanation of the Code

1. **Node Structure**:
   ```c
   struct Node {
       int data;
       struct Node* prev;
       struct Node* next;
   };
   ```
   - `data`: Stores the integer value in the node.
   - `prev`: Points to the previous node.
   - `next`: Points to the next node.

2. **Creating a Node**:
   ```c
   struct Node* createNode(int data) {
       struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
       newNode->data = data;
       newNode->prev = NULL;
       newNode->next = NULL;
       return newNode;
   }
   ```
   This function creates and returns a new node with the specified data. Both the `prev` and `next` pointers are initialized to `NULL`.

3. **Insert at the Front**:
   ```c
   void insertAtFront(struct Node** head, int data) {
       struct Node* newNode = createNode(data);
       newNode->next = *head;
       if (*head != NULL) {
           (*head)->prev = newNode;
       }
       *head = newNode;
   }
   ```
   - Creates a new node.
   - If the list is not empty, it updates the `prev` pointer of the current head to point to the new node.
   - Makes the new node the head of the list.

4. **Insert at the End**:
   ```c
   void insertAtEnd(struct Node** head, int data) {
       struct Node* newNode = createNode(data);
       struct Node* temp = *head;
       if (*head == NULL) {
           *head = newNode;
           return;
       }
       while (temp->next != NULL) {
           temp = temp->next;
       }
       temp->next = newNode;
       newNode->prev = temp;
   }
   ```
   - Traverses the list to the last node.
   - Inserts the new node at the end and updates the `prev` pointer of the new node to point to the last node.

5. **Delete a Node**:
   ```c
   void deleteNode(struct Node** head, int data) {
       struct Node* temp = *head;
       while (temp != NULL && temp->data != data) {
           temp = temp->next;
       }
       if (temp == NULL) {
           printf("Node with value %d not found.\n", data);
           return;
       }
       if (temp->prev != NULL) {
           temp->prev->next = temp->next;
       } else {
           *head = temp->next;
       }
       if (temp->next != NULL) {
           temp->next->prev = temp->prev;
       }
       free(temp);
   }
   ```
   - Searches for the node with the specified value.
   - Updates the pointers of the adjacent nodes to remove the target node from the list and frees its memory.

6. **Display the List**:
   ```c
   void displayList(struct Node* head) {
       struct Node* temp = head;
       while (temp != NULL) {
           printf("%d <-> ", temp->data);
           temp = temp->next;
       }
       printf("NULL\n");
   }
   ```
   This function traverses the list from the head and prints each node's data.

7. **Display the List in Reverse**:
   ```c
   void displayReverseList(struct Node* head) {
       if (head == NULL) return;
       struct Node* temp = head;
       while (temp->next != NULL) {
           temp = temp->next;
       }
       while (temp != NULL) {
           printf("%d <-> ", temp->data);
           temp = temp->prev;
       }
       printf("NULL\n");
   }
   ```
   This function first traverses the list to the last node and then prints the list in reverse order by following the `prev` pointers.

### Output:

```
Doubly Linked List after inserting 1, 2, 3 at the front:
1 <-> 2 <-> 3 <-> NULL
Doubly Linked List after inserting 4, 5 at the end:
1 <-> 2 <-> 3 <-> 4 <-> 5 <-> NULL
Doubly Linked List after deleting node with value 3:
1 <-> 2 <-> 4 <-> 5 <-> NULL
Reverse traversal of the Doubly Linked List:
5 <-> 4 <-> 2 <-> 1 <-> NULL
```

This code implements a doubly linked list with functions for inserting nodes at both ends, deleting nodes, displaying the list in both forward and reverse order. You can extend this to add more features like searching, counting the number of nodes, etc.