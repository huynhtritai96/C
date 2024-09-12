### Implementing a Stack in C: Different Methods and All Operations

A **stack** is a linear data structure that follows the **Last In, First Out (LIFO)** principle. It allows operations at one end only, the top of the stack. The primary operations are:

- **Push**: Insert an element onto the stack.
- **Pop**: Remove and return the top element from the stack.
- **Peek/Top**: Retrieve the top element without removing it.
- **isEmpty**: Check if the stack is empty.
- **isFull**: Check if the stack is full (relevant for fixed-size implementations).
- **Size**: Get the current number of elements in the stack.

There are multiple ways to implement a stack in C:

1. **Array-Based Implementation**:
   - **Static Array**: Uses a fixed-size array.
   - **Dynamic Array**: Uses a dynamically allocated array that can resize.

2. **Linked List Implementation**:
   - **Singly Linked List**: Each node points to the next node.
   - **Doubly Linked List**: Each node points to both the next and previous nodes.

Below, we'll explore each method with code examples and explain all the operations.

---

## **1. Stack Implementation Using a Static Array**

### **Overview**

- **Fixed Size**: The size of the stack is predefined.
- **Pros**: Simple and efficient for known maximum sizes.
- **Cons**: Limited capacity; cannot handle more elements than the array size.

### **Code Implementation**

```c
#include <stdio.h>
#include <stdlib.h>
#define MAX 100 // Maximum size of the stack

// Stack structure using a static array
struct Stack {
    int arr[MAX];
    int top;
};

// Function prototypes
void initStack(struct Stack* stack);
int isFull(struct Stack* stack);
int isEmpty(struct Stack* stack);
void push(struct Stack* stack, int value);
int pop(struct Stack* stack);
int peek(struct Stack* stack);
int size(struct Stack* stack);

// Initialize the stack
void initStack(struct Stack* stack) {
    stack->top = -1;
}

// Check if the stack is full
int isFull(struct Stack* stack) {
    return stack->top == MAX - 1;
}

// Check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Push an element onto the stack
void push(struct Stack* stack, int value) {
    if (isFull(stack)) {
        printf("Stack Overflow. Cannot push %d\n", value);
        return;
    }
    stack->arr[++(stack->top)] = value;
    printf("Pushed %d onto the stack.\n", value);
}

// Pop an element from the stack
int pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow. Cannot pop.\n");
        return -1; // Return -1 to indicate failure
    }
    int value = stack->arr[(stack->top)--];
    printf("Popped %d from the stack.\n", value);
    return value;
}

// Peek the top element of the stack
int peek(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty.\n");
        return -1; // Return -1 to indicate failure
    }
    return stack->arr[stack->top];
}

// Get the current size of the stack
int size(struct Stack* stack) {
    return stack->top + 1;
}

// Main function to demonstrate stack operations
int main() {
    struct Stack stack;
    initStack(&stack);

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);

    printf("Top element is %d\n", peek(&stack));
    printf("Stack size is %d\n", size(&stack));

    pop(&stack);
    pop(&stack);
    pop(&stack);
    pop(&stack); // Attempt to pop from an empty stack

    return 0;
}
```

### **Explanation**

- **Initialization**: The `initStack` function sets `top` to `-1`, indicating an empty stack.
- **Push Operation**:
  - Check if the stack is full using `isFull`.
  - Increment `top` and insert the value.
- **Pop Operation**:
  - Check if the stack is empty using `isEmpty`.
  - Retrieve the value at `top` and decrement `top`.
- **Peek Operation**:
  - Return the value at `top` without modifying `top`.
- **Size Operation**:
  - Return `top + 1` since `top` starts at `-1`.

---

## **2. Stack Implementation Using a Dynamic Array**

### **Overview**

- **Resizable**: The stack can grow as needed.
- **Pros**: Flexible size; can handle more elements than initially allocated.
- **Cons**: Slightly more complex due to dynamic memory management.

### **Code Implementation**

```c
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_SIZE 2 // Initial size of the stack

// Stack structure using a dynamic array
struct Stack {
    int* arr;
    int top;
    int capacity;
};

// Function prototypes
void initStack(struct Stack* stack);
void resizeStack(struct Stack* stack);
int isEmpty(struct Stack* stack);
void push(struct Stack* stack, int value);
int pop(struct Stack* stack);
int peek(struct Stack* stack);
int size(struct Stack* stack);
void freeStack(struct Stack* stack);

// Initialize the stack
void initStack(struct Stack* stack) {
    stack->capacity = INITIAL_SIZE;
    stack->top = -1;
    stack->arr = (int*)malloc(stack->capacity * sizeof(int));
    if (!stack->arr) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
}

// Resize the stack when capacity is reached
void resizeStack(struct Stack* stack) {
    stack->capacity *= 2;
    stack->arr = (int*)realloc(stack->arr, stack->capacity * sizeof(int));
    if (!stack->arr) {
        printf("Memory allocation failed during resizing.\n");
        exit(1);
    }
    printf("Stack capacity resized to %d.\n", stack->capacity);
}

// Check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Push an element onto the stack
void push(struct Stack* stack, int value) {
    if (stack->top == stack->capacity - 1) {
        resizeStack(stack);
    }
    stack->arr[++(stack->top)] = value;
    printf("Pushed %d onto the stack.\n", value);
}

// Pop an element from the stack
int pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow. Cannot pop.\n");
        return -1;
    }
    int value = stack->arr[(stack->top)--];
    printf("Popped %d from the stack.\n", value);
    return value;
}

// Peek the top element of the stack
int peek(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty.\n");
        return -1;
    }
    return stack->arr[stack->top];
}

// Get the current size of the stack
int size(struct Stack* stack) {
    return stack->top + 1;
}

// Free the allocated memory
void freeStack(struct Stack* stack) {
    free(stack->arr);
}

// Main function to demonstrate stack operations
int main() {
    struct Stack stack;
    initStack(&stack);

    for (int i = 1; i <= 5; i++) {
        push(&stack, i * 10);
    }

    printf("Top element is %d\n", peek(&stack));
    printf("Stack size is %d\n", size(&stack));

    while (!isEmpty(&stack)) {
        pop(&stack);
    }

    freeStack(&stack);
    return 0;
}
```

### **Explanation**

- **Initialization**:
  - Allocate memory for the array using `malloc`.
  - Set initial capacity and `top`.
- **Resizing**:
  - When the stack is full, double its capacity using `realloc`.
- **Push Operation**:
  - Check if resizing is needed.
  - Increment `top` and insert the value.
- **Pop Operation**:
  - Similar to the static array implementation.
- **Freeing Memory**:
  - Use `freeStack` to release the allocated memory when done.

---

## **3. Stack Implementation Using a Singly Linked List**

### **Overview**

- **Dynamic Size**: Can grow or shrink as needed.
- **Pros**: No need to define initial capacity; efficient memory usage.
- **Cons**: Slightly slower due to dynamic memory allocation for each node.

### **Code Implementation**

```c
#include <stdio.h>
#include <stdlib.h>

// Node structure for linked list
struct Node {
    int data;
    struct Node* next;
};

// Function prototypes
void push(struct Node** top_ref, int value);
int pop(struct Node** top_ref);
int peek(struct Node* top);
int isEmpty(struct Node* top);
int size(struct Node* top);

// Push an element onto the stack
void push(struct Node** top_ref, int value) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (!new_node) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    new_node->data = value;
    new_node->next = *top_ref;
    *top_ref = new_node;
    printf("Pushed %d onto the stack.\n", value);
}

// Pop an element from the stack
int pop(struct Node** top_ref) {
    if (isEmpty(*top_ref)) {
        printf("Stack Underflow. Cannot pop.\n");
        return -1;
    }
    struct Node* temp = *top_ref;
    int value = temp->data;
    *top_ref = temp->next;
    free(temp);
    printf("Popped %d from the stack.\n", value);
    return value;
}

// Peek the top element of the stack
int peek(struct Node* top) {
    if (isEmpty(top)) {
        printf("Stack is empty.\n");
        return -1;
    }
    return top->data;
}

// Check if the stack is empty
int isEmpty(struct Node* top) {
    return top == NULL;
}

// Get the current size of the stack
int size(struct Node* top) {
    int count = 0;
    struct Node* current = top;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

// Main function to demonstrate stack operations
int main() {
    struct Node* stack = NULL;

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);

    printf("Top element is %d\n", peek(stack));
    printf("Stack size is %d\n", size(stack));

    pop(&stack);
    pop(&stack);
    pop(&stack);
    pop(&stack); // Attempt to pop from an empty stack

    return 0;
}
```

### **Explanation**

- **Push Operation**:
  - Allocate a new node.
  - Set its `data` and point `next` to the current top.
  - Update the `top` reference to the new node.
- **Pop Operation**:
  - Check if the stack is empty.
  - Store the current top node.
  - Update `top` to the next node.
  - Free the old top node.
- **Peek Operation**:
  - Return the `data` of the top node.
- **Size Operation**:
  - Traverse the linked list and count the nodes.

---

## **4. Stack Implementation Using a Doubly Linked List**

### **Overview**

- **Dynamic Size**: Similar to the singly linked list.
- **Pros**: Can traverse in both directions (not typically needed for a stack).
- **Cons**: More memory per node due to extra pointer; unnecessary complexity for a stack.

### **Note**

- A doubly linked list is not commonly used for implementing a stack because the stack operates on one end (the top), and bidirectional traversal is not required.
- Therefore, using a singly linked list is more efficient for stack implementation.

---

## **Operations Summary**

Here are all the standard operations performed on a stack:

- **Initialization**: Set up the stack data structure.
- **Push**: Add an element to the top of the stack.
- **Pop**: Remove and return the top element.
- **Peek/Top**: Return the top element without removing it.
- **isEmpty**: Check if the stack has no elements.
- **isFull**: (For fixed-size stacks) Check if the stack cannot accept more elements.
- **Size**: Get the number of elements in the stack.
- **Free**: Release any dynamically allocated memory (important in dynamic implementations).

---

## **Comparison of Implementations**

| Feature          | Static Array       | Dynamic Array      | Linked List        |
|------------------|--------------------|--------------------|--------------------|
| **Size Limit**   | Fixed at compile-time | Grows dynamically  | Dynamic, no predefined limit |
| **Memory Usage** | Allocated upfront  | Allocated as needed | Allocated per node |
| **Time Complexity (Push/Pop)** | O(1) | Amortized O(1) due to resizing | O(1) |
| **Implementation Complexity** | Simple | Moderate (due to resizing) | Moderate (due to pointers) |
| **Memory Efficiency** | May waste space | Efficient | Efficient |
| **Operations Supported** | All basic operations | All basic operations | All basic operations |

---

## **Advanced Stack Operations**

In addition to the basic operations, stacks can support advanced operations:

- **Duplicate Top Element**: Duplicate the top element of the stack.
- **Swap Top Two Elements**: Swap the top two elements.
- **Rotate Stack**: Move elements within the stack.

Implementing these operations depends on the stack structure:

### **Duplicate Top Element (Linked List Implementation)**

```c
void duplicateTop(struct Node** top_ref) {
    if (isEmpty(*top_ref)) {
        printf("Stack is empty. Cannot duplicate.\n");
        return;
    }
    int top_value = (*top_ref)->data;
    push(top_ref, top_value);
    printf("Duplicated top element %d.\n", top_value);
}
```

### **Swap Top Two Elements (Linked List Implementation)**

```c
void swapTop(struct Node** top_ref) {
    if (size(*top_ref) < 2) {
        printf("Not enough elements to swap.\n");
        return;
    }
    struct Node* first = *top_ref;
    struct Node* second = first->next;
    first->next = second->next;
    second->next = first;
    *top_ref = second;
    printf("Swapped top two elements.\n");
}
```

---

## **Implementing Stack in Other Languages**

While this explanation focuses on C, stacks can be implemented in other programming languages such as C++, Java, Python, and more. The core concepts remain the same, but the syntax and available data structures may differ.

---

## **Conclusion**

There are several ways to implement a stack, each with its advantages and trade-offs:

- **Static Array**: Simple but fixed size.
- **Dynamic Array**: Resizable but requires dynamic memory management.
- **Linked List**: Dynamic size and efficient memory usage but involves pointer manipulation.

When choosing an implementation:

- **Use a static array** when the maximum size is known and unlikely to change.
- **Use a dynamic array** when you need flexibility and prefer array indexing.
- **Use a linked list** when you expect frequent insertions and deletions, and memory efficiency is important.

Understanding these implementations and operations allows you to choose the best approach for your specific needs.

---

## **Complete Linked List Stack Implementation with All Operations**

Below is the complete code for a stack implemented using a singly linked list, including advanced operations:

```c
#include <stdio.h>
#include <stdlib.h>

// Node structure for linked list
struct Node {
    int data;
    struct Node* next;
};

// Function prototypes
void push(struct Node** top_ref, int value);
int pop(struct Node** top_ref);
int peek(struct Node* top);
int isEmpty(struct Node* top);
int size(struct Node* top);
void duplicateTop(struct Node** top_ref);
void swapTop(struct Node** top_ref);
void freeStack(struct Node** top_ref);

// Push an element onto the stack
void push(struct Node** top_ref, int value) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (!new_node) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    new_node->data = value;
    new_node->next = *top_ref;
    *top_ref = new_node;
    printf("Pushed %d onto the stack.\n", value);
}

// Pop an element from the stack
int pop(struct Node** top_ref) {
    if (isEmpty(*top_ref)) {
        printf("Stack Underflow. Cannot pop.\n");
        return -1;
    }
    struct Node* temp = *top_ref;
    int value = temp->data;
    *top_ref = temp->next;
    free(temp);
    printf("Popped %d from the stack.\n", value);
    return value;
}

// Peek the top element of the stack
int peek(struct Node* top) {
    if (isEmpty(top)) {
        printf("Stack is empty.\n");
        return -1;
    }
    return top->data;
}

// Check if the stack is empty
int isEmpty(struct Node* top) {
    return top == NULL;
}

// Get the current size of the stack
int size(struct Node* top) {
    int count = 0;
    struct Node* current = top;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

// Duplicate the top element of the stack
void duplicateTop(struct Node** top_ref) {
    if (isEmpty(*top_ref)) {
        printf("Stack is empty. Cannot duplicate.\n");
        return;
    }
    int top_value = (*top_ref)->data;
    push(top_ref, top_value);
    printf("Duplicated top element %d.\n", top_value);
}

// Swap the top two elements of the stack
void swapTop(struct Node** top_ref) {
    if (size(*top_ref) < 2) {
        printf("Not enough elements to swap.\n");
        return;
    }
    struct Node* first = *top_ref;
    struct Node* second = first->next;
    first->next = second->next;
    second->next = first;
    *top_ref = second;
    printf("Swapped top two elements.\n");
}

// Free the stack
void freeStack(struct Node** top_ref) {
    struct Node* current = *top_ref;
    struct Node* next_node;
    while (current) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
    *top_ref = NULL;
    printf("Stack memory freed.\n");
}

// Main function to demonstrate stack operations
int main() {
    struct Node* stack = NULL;

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);

    printf("Top element is %d\n", peek(stack));
    printf("Stack size is %d\n", size(stack));

    duplicateTop(&stack);
    printf("Top element after duplication is %d\n", peek(stack));
    printf("Stack size is %d\n", size(stack));

    swapTop(&stack);
    printf("Top element after swap is %d\n", peek(stack));

    while (!isEmpty(stack)) {
        pop(&stack);
    }

    freeStack(&stack);

    return 0;
}
```

---

**Note**: Always ensure proper memory management by freeing allocated memory when it's no longer needed to prevent memory leaks.
