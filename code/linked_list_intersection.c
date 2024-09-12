/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
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

struct Node* findIntersection(struct Node* head1, struct Node* head2) {
    struct Node* cur1 = head1;
    struct Node* cur2 = head2;
    if(cur1 == NULL | cur2 == NULL) {
        return NULL;
    }
    
    while(cur1 != cur2) {
        cur1 = (cur1 == NULL) ? head2 : cur1->next;
        cur2 = (cur2 == NULL) ? head1 : cur2->next;
    }
    return cur1;
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
    
    struct Node* head2 = NULL;
    insertEnd(&head2, 1);
    insertEnd(&head2, 2);
    insertEnd(&head2, 3);
    // head2->next->next->next = head->next->next;
    printList(head2);
    
    struct Node* inter = findIntersection(head, head2);
    printf("\n%p ", inter);
    
    

    return 0;
}

