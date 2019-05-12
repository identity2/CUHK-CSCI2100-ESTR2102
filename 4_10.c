#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LEN 32

typedef struct _heap {
    int currSize;
    int maxSize;
    char (*arr)[LEN];
} Heap;

Heap* initHeap(int maxSize) {
    Heap* h = malloc(sizeof(Heap));
    h->currSize = 0;
    h->maxSize = maxSize;
    h->arr = malloc(sizeof(h->arr) * (1 + maxSize));
    return h;
}

void freeHeap(Heap* h) {
    free(h->arr);
    free(h);
}

void percolateDown(Heap* h, int hole) {
    char str[LEN];
    strcpy(str, h->arr[hole]);

    int child;
    for (; hole * 2 <= h->currSize; hole = child) {
        child = hole * 2;
        if (child != h->currSize && strcmp(h->arr[child + 1], h->arr[child]) < 0)
            child += 1;
        if (strcmp(h->arr[child], str) < 0)
            strcpy(h->arr[hole], h->arr[child]);
        else break;
    }

    strcpy(h->arr[hole], str);
}

char* getMin(Heap* h) {
    return h->arr[1];
}

void insert(Heap* h, char* str) {
    h->currSize++;

    int hole = h->currSize;
    for (; hole > 1 && strcmp(h->arr[hole / 2], str) > 0; hole /= 2)
        strcpy(h->arr[hole], h->arr[hole / 2]);
    strcpy(h->arr[hole], str);
}

void deleteMin(Heap* h) {
    if (h->currSize != 1)
        strcpy(h->arr[1], h->arr[h->currSize]);
    h->currSize--;
    percolateDown(h, 1);
}

int main(void) {
    Heap* h = initHeap(100);
    while (1) {
        char operation[10];
        scanf("%s", operation);
        if (strcmp(operation, "Insert") == 0) {
            char str[LEN];
            scanf("%s", str);
            insert(h, str);
        } else if (strcmp(operation, "Sort") == 0) {
            int start = 1;
            while (h->currSize) {
                printf(start ? "%s" : " %s", getMin(h));
                deleteMin(h);
                start = 0;
            }
            putchar('\n');
        } else {
            deleteMin(h);
        }
    }
    return 0;
}
