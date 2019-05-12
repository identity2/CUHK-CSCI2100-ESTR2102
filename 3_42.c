#include <stdio.h>
#include <stdlib.h>

int painters = 0;

typedef struct tree_node {
    int val;
    int painted;
    struct tree_node* parent;
    struct tree_node* left;
    struct tree_node* right;
} TreeNode;

typedef struct list_node {
    TreeNode* val;
    struct list_node* next;
} ListNode;

typedef struct queue {
    ListNode* head;
    ListNode* rear;
} Queue;

TreeNode* newTreeNode(int val) {
    TreeNode* node = (TreeNode*) malloc(sizeof(TreeNode));
    node->val = val;
    node->painted = 0;
    node->left = node->right = node->parent = NULL;
    return node;
}

void freeTree(TreeNode* root) {
    if (!root) return;
    if (root->left) freeTree(root->left);
    if (root->right) freeTree(root->right);
    free(root);
}

Queue* newQueue() {
    Queue* q = (Queue*) malloc(sizeof(Queue));
    q->head = (ListNode*) malloc(sizeof(ListNode));
    q->rear = q->head;
    return q;
}

void freeQueue(Queue* q) {
    ListNode* node = q->head;
    while(node) {
        ListNode* temp = node->next;
        free(node);
        node = temp;
    }
    free(q);
}

void push(Queue* q, TreeNode* val) {
    ListNode* node = (ListNode*) malloc(sizeof(ListNode));
    node->val = val;
    node->next = NULL;

    q->rear->next = node;
    q->rear = node;
}

int isEmpty(Queue* q) {
    if (q->head == q->rear)
        return 1;
    return 0;
}

TreeNode* front(Queue* q) {
    if (isEmpty(q)) {
        puts("The queue is empty, no front.");
        return NULL;
    }
    return q->head->next->val;
}

void pop(Queue* q) {
    if (isEmpty(q)) {
        puts("The queue is empty, cannot pop.");
        return;
    }

    if (q->head->next == q->rear)
        q->rear = q->head;

    ListNode* temp = q->head->next;
    q->head->next = temp->next;
    free(temp);
}

TreeNode* constructTree(int* arr, int len) {
    Queue* q = newQueue();
    TreeNode* root = newTreeNode(arr[0]);
    push(q, root);

    int j, leftChild = 1;
    TreeNode* parent;
    for (j = 1; j < len; j++) {
        if (leftChild) {
            parent = front(q);
            pop(q);
        }

        TreeNode* currNode = newTreeNode(arr[j]);
        push(q, currNode);

        currNode->parent = parent;
        if (leftChild)
            parent->left = currNode;
        else
            parent->right = currNode;

        leftChild = !leftChild;
    }
    freeQueue(q);
    return root;
}

int isNull(TreeNode* node) {
    return !node || node->val == 0;
}

void inOrderPrint(TreeNode* root) {
    if (isNull(root)) return;

    inOrderPrint(root->left);
    printf("%d ", root->val);
    inOrderPrint(root->right);
}

void placePainter(TreeNode* root) {
    // printf("Painting node %d.\n", root->val);
    painters++;

    root->painted = 1;

    if (!isNull(root->parent))
        root->parent->painted = 1;

    if (!isNull(root->left))
        root->left->painted = 1;

    if (!isNull(root->right))
        root->right->painted = 1;
}

void placePaintersDFS(TreeNode* root) {
    // printf("DFS on node %d.\n", root->val);

    int hasLeft = !isNull(root->left);
    int hasRight = !isNull(root->right);

    if (hasLeft)
        placePaintersDFS(root->left);

    if (hasRight)
        placePaintersDFS(root->right);

    if (hasLeft && !root->left->painted)
        placePainter(root);
    else if (hasRight && !root->right->painted)
        placePainter(root);
}

int main(void) {
    int i, cases;
    scanf("%d", &cases);

    for (i = 0; i < cases; i++) {
        int j, nodeCount;
        scanf("%d", &nodeCount);
        
        int* arr = (int*) malloc(sizeof(int) * nodeCount);
        for (j = 0; j < nodeCount; j++)
            scanf("%d", &arr[j]);

        TreeNode* root = constructTree(arr, nodeCount);
        free(arr);
        painters = 0;
        placePaintersDFS(root);
        if (!root->painted) painters++; // Tree with a single node.
        freeTree(root);
        printf("%d\n", painters);
    }

    return 0;
}
