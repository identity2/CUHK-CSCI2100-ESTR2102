#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef int T;
typedef struct {
    T* arr;
    int maxSize;
    int currSize;
} Vector;

typedef struct _tree_node {
    int val;
    int active;
    struct _tree_node* left;
    struct _tree_node* right;
} TreeNode;

typedef struct _q_node {
    TreeNode* val;
    struct _q_node* next;
} QueueNode;

typedef struct _queue {
    QueueNode* head;
    QueueNode* rear;
} Queue;

Vector* initVector(int maxSize) {
    Vector* vec = malloc(sizeof(Vector));
    vec->arr = malloc(sizeof(T) * maxSize);
    vec->maxSize = maxSize;
    vec->currSize = 0;
    return vec;
}

void freeVector(Vector* vec) {
    free(vec->arr);
    free(vec);
}

Vector* resizeVector(Vector* vec, int newSize) {
    Vector* temp = initVector(newSize);
    temp->currSize = vec->currSize;

    int i;
    for (i = 0; i < vec->currSize; i++)
        temp->arr[i] = vec->arr[i];
    
    freeVector(vec);
    return temp;
}

Vector* pushBack(Vector* vec, int num) {
    if (vec->currSize == vec->maxSize)
        vec = resizeVector(vec, vec->maxSize * 2);
    
    vec->arr[vec->currSize] = num;
    vec->currSize++;
    return vec;
}

void popBack(Vector* vec) {
    if (vec->currSize != 0) {
        vec->currSize--;
    }
}

TreeNode* initTreeNode(int val) {
    TreeNode* node = malloc(sizeof(TreeNode));
    node->active = (val != INT_MIN);
    node->left = node->right = NULL;
    node->val = val;
    return node;
}

Queue* initQueue() {
    Queue* q = malloc(sizeof(Queue));
    q->head = malloc(sizeof(QueueNode));
    q->rear = q->head;
    return q;
}

void freeQueue(Queue* q) {
    QueueNode* n = q->head;
    while (n) {
        QueueNode* temp = n->next;
        free(n);
        n = temp;
    }
    free(q);
}

TreeNode* front(Queue* q) {
    return q->head->next->val;
}

void push(Queue* q, TreeNode* val) {
    QueueNode* n = malloc(sizeof(QueueNode));
    n->val = val;
    n->next = NULL;
    q->rear->next = n;
    q->rear = n;
}

void pop(Queue* q) {
    QueueNode* n = q->head->next;
    if (!n) return;
    if (n == q->rear) q->rear = q->head;
    q->head->next = n->next;
    free(n);
}

TreeNode* construct(int* arr, int len) {
    Queue* q = initQueue();
    TreeNode* root = initTreeNode(arr[0]);
    push(q, root);
    int j, leftChild = 1;
    TreeNode* parent;
    for (j = 1; j < len; j++) {
        if (leftChild) {
            parent = front(q);
            pop(q);
        }
        TreeNode* currNode = initTreeNode(arr[j]);
        push(q, currNode);
        if (leftChild)
            parent->left = currNode;
        else
            parent->right = currNode;
        leftChild = !leftChild;
    }
    free(q);
    return root;
}

TreeNode* readLineToTree() {
    Vector* vec = initVector(20);
    char str[8];
    char ch;
    int index = 0;
    while ((ch = getchar()) != '\n') {
        if (ch == '#') {
            vec = pushBack(vec, INT_MIN);
            getchar();
        } else if (ch == ' ') {
            str[index] = '\0';
            vec = pushBack(vec, atoi(str));
            index = 0;
        } else {
            str[index++] = ch;
        }
    }

    str[index] = '\0';
    vec = pushBack(vec, atoi(str));

    TreeNode* node = construct(vec->arr, vec->currSize);
    freeVector(vec);
    return node;
}

void preorder(TreeNode* root) {
    if (!root || !root->active) return;

    printf("%d ", root->val);
    preorder(root->left);
    preorder(root->right);
}

int max(int x, int y) {
    return x > y ? x : y;
}

int maxSum(TreeNode* root) {
    if (!root || !root->active) return 0;

    return root->val + max(maxSum(root->left), maxSum(root->right));
}

int main(void) {
    int test_cases;
    scanf("%d", &test_cases); getchar();
    int c;
    for (c = 0; c < test_cases; c++) {
        TreeNode* root = readLineToTree();
        printf("%d\n", maxSum(root));
    }
    return 0;
}