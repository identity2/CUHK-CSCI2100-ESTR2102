#include <stdlib.h>
#include <stdio.h>

typedef struct _node {
    long val;
    struct _node* next;
} Node;

typedef struct _stack {
    Node* head;
} Stack;

Stack* initStack() {
    Stack* stk = malloc(sizeof(Stack));
    stk->head = malloc(sizeof(Node));
    stk->head->next = NULL;
    return stk;
}

void freeStack(Stack* stk) {
    Node* n = stk->head;
    while (n) {
        Node* temp = n->next;
        free(n);
        n = temp;
    }
    free(stk);
}

int isEmpty(Stack* stk) {
    return stk->head->next == NULL;
}

long top(Stack* stk) {
    return stk->head->next->val;
}

void push(Stack* stk, long val) {
    Node* n = malloc(sizeof(Node));
    n->val = val;
    n->next = stk->head->next;
    stk->head->next = n;
}

void pop(Stack* stk) {
    Node* n = stk->head->next;
    stk->head->next = n->next;
    free(n);
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    Stack* stk = initStack();
    Stack* mStk = initStack();
    int c;
    for (c = 0; c < cases; c++) {
        int operation;
        scanf("%d", &operation);
        if (operation == 1) {
            long x;
            scanf("%ld", &x);
            push(stk, x);
            if (isEmpty(mStk) || top(mStk) >= x) {
                // printf("is empty: %d, top(stk): %ld, x%ld\n", isEmpty(stk), top(stk), x);
                // puts("Also push on mStk.");
                push(mStk, x);
            }
        } else if (operation == 2) {
            long x = top(stk);
            pop(stk);
            if (x == top(mStk)) {
                pop(mStk);
            }
        } else if (operation == 3) {
            printf("%ld\n", top(stk));
        } else if (operation == 4) {
            printf("%ld\n", top(mStk));
        }
    }

    freeStack(stk);
    freeStack(mStk);
    return 0;
}