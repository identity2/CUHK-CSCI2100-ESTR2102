#include <stdlib.h>
#include <stdio.h>

typedef struct _heap {
    int currSize;
    int maxSize;
    int* arr;
} Heap;

Heap* initHeap(int maxSize) {
    Heap* h = malloc(sizeof(Heap));
    h->currSize = 0;
    h->maxSize = maxSize;
    h->arr = malloc(sizeof(int) * (1 + maxSize));
    return h;
}

void freeHeap(Heap* h) {
    free(h->arr);
    free(h);
}

void insert(Heap* h, int val) {
    h->currSize++;
    int hole = h->currSize;
    for (; hole > 1 && h->arr[hole / 2] > val; hole /= 2)
        h->arr[hole] = h->arr[hole / 2];
    h->arr[hole] = val;
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    int c;
    for (c = 0; c < cases; c++) {
        Heap* h = initHeap(20);
        int num;
        scanf("%d", &num);
        while (num != -1) {
            insert(h, num);
            scanf("%d", &num);
        }
        int i;
        int start = 1;
        for (i = 1; i <= h->currSize; i++) {
            if (start) {
                printf("%d", h->arr[i]);
                start = 0;
            } else {
                printf(" %d", h->arr[i]);
            }
        }
        putchar('\n');
        freeHeap(h);
    }
}