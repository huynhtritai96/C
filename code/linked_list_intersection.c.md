Reference: https://www.geeksforgeeks.org/write-a-function-to-get-the-intersection-point-of-two-linked-lists/

Table of content: https://leetcode.com/explore/interview/card/leetcodes-interview-crash-course-data-structures-and-algorithms/703/arraystrings/4501/

### Finding the Intersection Point of Two Linked Lists in C Using the Two Pointers Technique

The provided C program demonstrates how to find the intersection point of two singly linked lists using the **Two Pointers Technique**. Below is a detailed explanation of how the code works, including the creation of linked lists, the intersection logic, and the algorithm's efficiency.

---

#### **1. Understanding the Problem**

Given two singly linked lists, the goal is to find the node at which the two lists intersect. The intersection is defined by reference, not by value. This means that after the intersection point, the nodes are shared between the two lists.

**Example:**

- **List A**: `10 -> 15 -> 30`
- **List B**: `3 -> 6 -> 9 -> 15 -> 30`

In this example, the two lists intersect at node `15`, and nodes `15` and `30` are common to both lists.

---

#### **2. Code Breakdown**

##### **a. Node Structure**

```c
struct Node {
    int data;
    struct Node *next;
};
```

- Each node contains:
  - **`data`**: The value stored in the node.
  - **`next`**: A pointer to the next node in the list.

##### **b. Function to Find the Intersection Point**

```c
struct Node* getIntersectionNode(struct Node* head1, struct Node* head2) {
    struct Node* ptr1 = head1;
    struct Node* ptr2 = head2;

    if (ptr1 == NULL || ptr2 == NULL)
        return NULL;

    while (ptr1 != ptr2) {
        ptr1 = ptr1 ? ptr1->next : head2;
        ptr2 = ptr2 ? ptr2->next : head1;
    }

    return ptr1;
}
```

- **Purpose**: Finds the intersection node between two linked lists.
- **Logic**:
  - **Initialization**: Two pointers `ptr1` and `ptr2` start at the heads of the two lists.
  - **Traversal**:
    - Move each pointer to the next node in its list.
    - If a pointer reaches the end (`NULL`), redirect it to the head of the other list.
  - **Termination**: The loop continues until `ptr1` and `ptr2` meet at the intersection point or both reach `NULL` (no intersection).

- **Explanation of the Two Pointers Technique**:
  - By switching pointers to the head of the opposite list after reaching the end, both pointers traverse the combined lengths of both lists. If there's an intersection, they will meet at the intersection node after at most `lengthA + lengthB` steps.
  - This works because:
    - The pointers traverse the same total distance.
    - If there's an intersection, they synchronize at that node.

##### **c. Helper Functions**

- **`createNode(int new_data)`**:
  - Allocates memory for a new node.
  - Sets the `data` and initializes `next` to `NULL`.

- **`printList(struct Node* node)`**:
  - Iterates through a linked list and prints the `data` of each node.

##### **d. Main Function**

```c
int main() {
    // Creation of first list: 10 -> 15 -> 30
    struct Node *head1 = createNode(10);
    head1->next = createNode(15);
    head1->next->next = createNode(30);

    // Creation of second list: 3 -> 6 -> 9 -> 15 -> 30
    struct Node *head2 = createNode(3);
    head2->next = createNode(6);
    head2->next->next = createNode(9);
    head2->next->next->next = head1->next; // Linking to the intersection

    struct Node *intersectionPoint = getIntersectionNode(head1, head2);

    if (intersectionPoint == NULL)
        printf("No Intersection Point\n");
    else
        printf("Intersection Point: %d\n", intersectionPoint->data);

    return 0;
}
```

- **Building the Lists**:
  - **First List**:
    - Nodes with data `10`, `15`, `30`.
  - **Second List**:
    - Nodes with data `3`, `6`, `9`.
    - The `next` of node `9` is set to `head1->next`, which is the node with data `15`, creating an intersection.

- **Finding the Intersection**:
  - Calls `getIntersectionNode(head1, head2)` to find the intersection point.
  - Prints the result.

---

#### **3. How the Two Pointers Technique Works**

- **Goal**: To synchronize the traversal of two linked lists so that the pointers align at the intersection point.

- **Process**:
  - **First Iteration**:
    - `ptr1` traverses List A.
    - `ptr2` traverses List B.
  - **Switching Lists**:
    - When `ptr1` reaches the end of List A, it starts from the head of List B.
    - When `ptr2` reaches the end of List B, it starts from the head of List A.
  - **Convergence**:
    - By switching, both pointers cover the same total distance.
    - They eventually meet at the intersection node or at `NULL` if there is no intersection.

- **Visualization**:

  ```
  List A: a1 -> a2 -> a3
                          ↘
                           c1 -> c2 -> c3
                          ↗
  List B: b1 -> b2 -> b3
  ```

- **Traversals**:
  - `ptr1` path: a1 → a2 → a3 → c1 → c2 → c3 → b1 → b2 → b3 → c1
  - `ptr2` path: b1 → b2 → b3 → c1 → c2 → c3 → a1 → a2 → a3 → c1

---

#### **4. Time and Space Complexity**

- **Time Complexity**: O(m + n)
  - `m` is the length of List A.
  - `n` is the length of List B.
  - Each pointer traverses at most `m + n` nodes.

- **Space Complexity**: O(1)
  - Only a constant amount of extra space is used for pointers.

---

#### **5. Edge Cases Handled**

- **No Intersection**:
  - If the lists do not intersect, both pointers will eventually reach `NULL`, and the function returns `NULL`.

- **One or Both Lists are Empty**:
  - If either `head1` or `head2` is `NULL`, the function immediately returns `NULL`.

---

#### **6. Testing the Program**

- **Expected Output**:
  ```
  Intersection Point: 15
  ```

- **Explanation**:
  - The two lists intersect at the node with data `15`.

---

#### **7. Potential Modifications**

- **Doubly Linked Lists**:
  - The algorithm can be adapted for doubly linked lists with appropriate adjustments.

- **Circular Linked Lists**:
  - Additional checks may be necessary to handle circular references.

- **Alternative Methods**:
  - **Using Hashing**:
    - Store nodes of one list in a hash table and check for common nodes in the other list.
    - Time Complexity: O(m + n)
    - Space Complexity: O(m) or O(n)

- **Without Modifying Pointers**:
  - If modifying pointers is not allowed, counts of the lengths can be used to align the pointers.

---

#### **8. Conclusion**

The provided code efficiently finds the intersection point of two singly linked lists using the Two Pointers Technique. This method is optimal in terms of time and space complexity and elegantly handles various edge cases.

---

**Note**: Always ensure that the linked lists are properly constructed and that any shared nodes are intentionally created, as unintended sharing of nodes can lead to unexpected behavior.
