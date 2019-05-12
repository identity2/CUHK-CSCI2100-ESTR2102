#include <stdlib.h>
#include <stdio.h>

typedef struct _heap {
    int currSize;
    int maxSize;
    long* arr;
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

void percolateDown(Heap* h, int hole) {
    long val = h->arr[hole];

    int child;
    for (; hole * 2 <= h->currSize; hole = child) {
        child = hole * 2;
        if (child != h->currSize && h->arr[child + 1] > h->arr[child])
            child += 1;
        if (h->arr[child] > val)
            h->arr[hole] = h->arr[child];
        else break;
    }

    h->arr[hole] = val;
}

long findMax(Heap* h) {
    return h->arr[1];
}

void insert(Heap* h, long val) {
    h->currSize++;
    int hole = h->currSize;
    for (; hole > 1 && h->arr[hole / 2] < val; hole /= 2)
        h->arr[hole] = h->arr[hole / 2];
    h->arr[hole] = val;
}

void deleteMax(Heap* h) {
    h->arr[1] = h->arr[h->currSize];
    h->currSize--;
    percolateDown(h, 1);
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    int c;
    Heap* h = initHeap(1000000);
    for (c = 0; c < cases; c++) {
        int operation;
        scanf("%d", &operation);
        if (operation == 1) {
            long val;
            scanf("%ld", &val);
            insert(h, val);
        } else if (operation == 2) {
            deleteMax(h);
        } else if (operation == 3) {
            printf("%ld\n", findMax(h));
        } else if (operation == 4) {
            long newVal;
            scanf("%ld", &newVal);
            
            long val = findMax(h);
            deleteMax(h);
            insert(h, newVal);
        }
    }
    freeHeap(h);
    return 0;
}