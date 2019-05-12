#include <stdio.h>
#include <stdlib.h>

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

void percolateDown(Heap* h, int hole) {
    int val = h->arr[hole];

    int child;
    for (; hole * 2 <= h->currSize; hole = child) {
        child = hole * 2;
        if (child != h->currSize && h->arr[child + 1] < h->arr[child])
            child += 1;
        if (h->arr[child] < val)
            h->arr[hole] = h->arr[child];
        else break;
    }
    h->arr[hole] = val;
}

int isEmpty(Heap* h) {
    return h->currSize == 0;
}

int findMin(Heap* h) {
    return h->arr[1];
}

void insert(Heap* h, int val) {
    h->currSize++;
    int hole = h->currSize;
    for (; hole > 1 && h->arr[hole / 2] > val; hole /= 2)
        h->arr[hole] = h->arr[hole / 2];
    h->arr[hole] = val;
}

void deleteMin(Heap* h) {
    h->arr[1] = h->arr[h->currSize];
    h->currSize--;
    percolateDown(h, 1);
}

int main(void) {
    while (1) {
        int cases;
        scanf("%d", &cases);
        if (cases == 0) break;
        Heap* h = initHeap(cases);
        int i;
        for (i = 0; i < cases; i++) {
            int num;
            scanf("%d", &num);
            insert(h, num);
        }

        int res = 0;
        while (h->currSize >= 2) {
            int num1 = findMin(h);
            deleteMin(h);
            int num2 = findMin(h);
            deleteMin(h);
            res += num1 + num2;
            insert(h, num1 + num2);
        }
        printf("%d\n", res);
        freeHeap(h);
    }
}