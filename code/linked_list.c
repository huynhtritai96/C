#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node* next;
};

void insertEnd(struct Node** head, int value) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->value = value;
    node->next = NULL;
    
    if(*head == NULL) {
        *head = node;
        return;
    }
    
    // Find the final node
    struct Node* curr = *head;
    while(curr->next != NULL) {
        curr = curr->next;
    }
    
    // Assign at the end 
    curr->next = node;
}

void removeNode(struct Node** head, int value) {
    if(*head == NULL) {
        return;
    }
    
    // Case 1: delete the first Node
    struct Node* curr = *head;
    if(curr->value == value){
        *head = curr->next;
        free(curr);
        return;
    }
    
    // Case 2: Find the node by value
    struct Node* prev = NULL;
    while(curr != NULL && curr->value != value){
        prev = curr;
        curr = curr->next;
    }
    
    // value cannot be found
    if(curr == NULL) {
        return; 
    }
    
    prev->next = curr->next;
    free(curr);
}

// explain: we have 3 node, current node point to previous, save the next node for loop
void reverseList(struct Node** head) {
    struct Node* curr = *head;
    struct Node* next = NULL;
    struct Node* prev = NULL;
    while(curr != NULL) {
        next = curr->next;
        curr->next = prev;
        
        // next
        prev = curr;
        curr = next;
    }
    //NOTE: cur = NULL
    *head = prev;
}

void printList(struct Node* head) {
    struct Node* curr = head;
    while(curr != NULL) {
        printf("%d -> ", curr->value);
        curr = curr->next;
    }
    printf("NULL\n");
}

void printReversedList(struct Node* head) {
    struct Node* curr = head;
    if(curr == NULL) return;
    printReversedList(curr->next);
    printf("%d -> ", curr->value);
}



int main()
{
    struct Node* head = NULL;
    insertEnd(&head, 5);
    insertEnd(&head, 10);
    insertEnd(&head, 15);
    insertEnd(&head, 51);
    insertEnd(&head, 33);
    insertEnd(&head, 7);
    
    printList(head);
    printf("\n");
    printReversedList(head);
    printf("\n");
    
    removeNode(&head, 5);
    removeNode(&head, 15);
    removeNode(&head, 7);
    printList(head);
    
    reverseList(&head);
    printList(head);
    
    return 0;
}
