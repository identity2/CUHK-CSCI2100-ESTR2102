#include <stdio.h>
#include <stdlib.h>

int board[8][8];

typedef struct _node {
    int i;
    int j;
    int move;
    struct _node* next;
} Node;

typedef struct _queue {
    Node* head;
    Node* rear;
} Queue;

Queue* initQueue() {
    Queue* q = malloc(sizeof(Queue));
    q->head = malloc(sizeof(Node));
    q->rear = q->head;
    return q;
}

void freeQueue(Queue* q) {
    Node* n = q->head;
    while (n) {
        Node* temp = n->next;
        free(n);
        n = temp;
    }
    free(q);
}

Node* front(Queue* q) {
    return q->head->next;
}

void push(Queue* q, int i, int j, int move) {
    Node* n = malloc(sizeof(Node));
    n->i = i;
    n->j = j;
    n->move = move;
    n->next = NULL;
    q->rear->next = n;
    q->rear = n;
}

void pop(Queue* q) {
    Node* n = q->head->next;
    if (n == q->rear) q->rear = q->head;
    q->head->next = n->next;
    free(n);
}

int isEmpty(Queue* q) {
    return q->head->next == NULL;
}

void printBoard() {
    int i,j;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            printf("%d ", board[i][j]);
        }
        putchar('\n');
    }
    putchar('\n');
}

int minMove(int fi, int fj, int ti, int tj) {
    Queue* q = initQueue();
    push(q, fi, fj, 0);
    while (!isEmpty(q)) {
        Node* n = front(q);
        int i = n->i;
        int j = n->j;
        int move = n->move;
        pop(q);

        board[i][j] = move;
        // printBoard();

        if (i == ti && j == tj) {
            freeQueue(q);
            return move;
        }

        if (i + 2 < 8 && j + 1 < 8 && !board[i+2][j+1]) {
            push(q, i+2, j+1, move + 1);
        }
        if (i + 2 < 8 && j - 1 >= 0 && !board[i+2][j-1]) {
            push(q, i+2, j-1, move + 1);
        }
        if (i + 1 < 8 && j + 2 < 8 && !board[i+1][j+2]) {
            push(q, i+1, j+2, move + 1);
        }
        if (i - 1 >= 0 && j + 2 < 8 && !board[i-1][j+2]) {
            push(q, i-1, j+2, move + 1);
        }
        if (i - 2 >= 0 && j + 1 < 8 && !board[i-2][j+1]) {
            push(q, i-2, j+1, move + 1);
        }
        if (i - 2 >= 0 && j - 1 >= 0 && !board[i-2][j-1]) {
            push(q, i-2, j-1, move + 1);
        }
        if (i + 1 < 8 && j - 2 >= 0 && !board[i+1][j-2]) {
            push(q, i+1, j-2, move + 1);
        }
        if (i - 1 >= 0 && j - 2 >= 0 && !board[i-1][j-2]) {
            push(q, i-1, j-2, move + 1);
        }
    }

    freeQueue(q);
    return -1;
}

int main(void) {
    while (1) {
        char str1[3], str2[3];
        scanf("%s", str1);
        scanf("%s", str2);
        int fi = str1[1] - '1';
        int fj = str1[0] - 'a';
        int ti = str2[1] - '1';
        int tj = str2[0] - 'a';
        int i,j;

        for (i = 0; i < 8; i++)
            for (j = 0; j < 8; j++)
                board[i][j] = 0;
        
        printf("%d\n", minMove(fi, fj, ti, tj));
    }
    return 0;
}