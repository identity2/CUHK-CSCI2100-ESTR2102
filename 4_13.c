#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

typedef struct heap {
	int currSize;
	int len;
	int* arr;
} Heap;

Heap* initHeap(int len) {
	Heap* h = (Heap*) malloc(sizeof(Heap));
	h->arr = (int*) malloc(sizeof(int) * (len + 1));
	h->arr[0] = INT_MAX;
	h->len = len;
	h->currSize = 0;
	return h;
}

void freeHeap(Heap* h) {
	free(h->arr);
	free(h);
}

void insert(Heap* h, int val) {
	if (h->currSize == h->len) {
		puts("Cannot insert, the heap is full.");
		return;
	}

	h->currSize++;

	// Percolate Up.
	int hole = h->currSize;
	for (; h->arr[hole / 2] < val; hole /= 2) {
		h->arr[hole] = h->arr[hole / 2];
	}
	h->arr[hole] = val;
}

int getMax(Heap* h) {
	if (h->currSize == 0) {
		puts("Cannot getMax, the heap is empty.");
		return -1;
	}

	return h->arr[1];
}

void deleteMax(Heap* h) {
	if (h->currSize == 0) {
		puts("Cannot deleteMax, the heap is empty.");
		return;
	}

	int val = h->arr[h->currSize];
	h->currSize--;

	int hole = 1, child;
	for (; hole * 2 <= h->currSize; hole = child) {
		child = hole * 2;
		if (child != h->currSize && h->arr[child] < h->arr[child + 1]) {
			child++;
		}
		if (h->arr[child] > val) {
			h->arr[hole] = h->arr[child];
		}
		else break;
	}
	h->arr[hole] = val;
}

int main(void) {
	int max_num;
	scanf("%d", &max_num);
	Heap* h = initHeap(max_num);
	while (1) {
		getchar(); // New line.
		char operation = getchar();
		if (operation == 'I') {
			int input;
			scanf("%d", &input);
			if (h->currSize < h->len) {
				insert(h, input);
			} else if (input < getMax(h)) {
				deleteMax(h);
				insert(h, input);
			}
		} else if (operation == 'O') {
			printf("%d\n", getMax(h));
		} else {
			break;
		}
	}
	freeHeap(h);
	return 0;
}
