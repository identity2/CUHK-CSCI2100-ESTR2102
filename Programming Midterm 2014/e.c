#include <stdlib.h>
#include <stdio.h>

typedef struct _node {
    struct _node* next;
    int val;
} Node;

Node* initNode(int val) {
    Node* n = malloc(sizeof(Node));
    n->next = NULL;
    n->val = val;
    return n;
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    int c;
    for (c = 0; c < cases; c++) {
        int n, m;
        scanf("%d%d", &n, &m);

        // Init.
        Node* head = initNode(1);
        Node* curr = head;
        int i;
        for (i = 2; i <= n; i++) {
            curr->next = initNode(i);
            curr = curr->next;
        }
        curr->next = head;
        Node* prev = curr;
        curr = head;

        // Execute.
        int start = 1;
        for (i = 0; i < n-1; i++) {
            int j;
            for (j = 1; j < m; j++) {
                prev = curr;
                curr = curr->next;
            }
            if (start) {
                printf("%d", curr->val);
                start = 0;
            } else {
                printf(" %d", curr->val);
            }

            // Remove.
            prev->next = curr->next;
            free(curr);
            curr = prev->next;
        }
        printf(start ? "%d\n" : " %d\n", curr->val);
    }
    return 0;
}