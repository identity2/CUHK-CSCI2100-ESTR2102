#include <stdlib.h>
#include <stdio.h>

int start;

typedef struct _node {
    struct _node* left;
    struct _node* right;
    int val;
} Node;

Node* initNode(int val) {
    Node* n = malloc(sizeof(Node));
    n->val = val;
    n->left = n->right = NULL;
    return n;
}

void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

Node* construct(int* pre, int preSize, int* in, int inSize) {
    if (inSize == 0) return NULL;
    Node* root = initNode(*pre);
    int i = 0;
    while (in[i] != *pre) i++;
    root->left = construct(pre + 1, i, in, i);
    root->right = construct(pre + 1 + i, preSize - i - 1, in + i + 1, inSize - i - 1);
    return root;
}

void printLeaf(Node* root) {
    if (!root) return;

    if (!root->left && !root->right) {
        if (start) {
            printf("%d", root->val);
            start = 0;
        } else {
            printf(" %d", root->val);
        }
    }

    printLeaf(root->left);
    printLeaf(root->right);
}

int main(void) {
    int preorder[1000];
    int inorder[1000];

    int cases;
    scanf("%d", &cases);
    int c;
    for (c = 0; c < cases; c++) {
        int n;
        scanf("%d", &n);
        int i;
        for (i = 0; i < n; i++) {
            scanf("%d", &preorder[i]);
        }

        for (i = 0; i < n; i++) {
            scanf("%d", &inorder[i]);
        }

        Node* root = construct(preorder, n, inorder, n);
        start = 1;
        printLeaf(root);
        putchar('\n');
        free(root);
    }
    return 0;
}