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

void deleteMin(Heap* h) {
    h->arr[1] = h->arr[h->currSize];
    h->currSize--;
    percolateDown(h, 1);
}

int main(void) {
    int piles;
    scanf("%d", &piles);
    int** grid = malloc(sizeof(int*) * piles);
    int p;
    int maxSize = 0;
    for (p = 0; p < piles; p++) {
        int n;
        scanf("%d", &n);
        int* arr = malloc(sizeof(int) * (n + 1));
        arr[0] = n;
        maxSize += n;
        int i;
        for (i = 1; i <= n; i++) {
            scanf("%d", &arr[i]);
        }
        grid[p] = arr;
    }

    Heap* h = initHeap(maxSize);

    int i, j;
    for (i = 0; i < piles; i++) {
        for (j = 1; j <= grid[i][0]; j++) {
            insert(h, grid[i][j]);
        }
    }

    while (h->currSize != 0) {
        printf("%d\n", findMin(h));
        deleteMin(h);
    }

    return 0;
}