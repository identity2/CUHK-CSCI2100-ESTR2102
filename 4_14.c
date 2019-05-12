#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int val;
	int index;
	int base;
} Node;

typedef struct heap {
	int currSize;
	int maxSize;
	Node* arr;
} Heap;

Heap* initHeap(int maxSize) {
	Heap* h = (Heap*) malloc(sizeof(Heap));
	h->currSize = 0;
	h->maxSize = maxSize;
	h->arr = (Node*) malloc(sizeof(Node) * (maxSize + 1));
	return h;
}

void freeHeap(Heap* h) {
	free(h->arr);
	free(h);
}

void push(Heap* h, Node n) {
	if (h->currSize == h->maxSize) {
		puts("The heap is full, cannot push.");
		return;
	}

	h->currSize++;

	int hole = h->currSize;
	for (; hole > 1 && h->arr[hole / 2].val > n.val; hole /= 2) {
		h->arr[hole] = h->arr[hole / 2];
	}
	h->arr[hole] = n;
}

Node getMin(Heap* h) {
	if (h->currSize == 0) {
		puts("The heap is empty, cannot getMin.");
		Node n = {-1, -1, -1};
		return n;
	}

	return h->arr[1];
}

void deleteMin(Heap* h) {
	if (h->currSize == 0) {
		puts("The heap is empty, annot deleteMin.");
		return;
	}

	Node n = h->arr[h->currSize];
	h->currSize--;

	int hole = 1, child;
	for (; hole * 2 <= h->currSize; hole = child) {
		child = hole * 2;
		if (child != h->currSize && h->arr[child].val > h->arr[child+1].val) {
			child++;
		}
		if (n.val > h->arr[child].val) {
			h->arr[hole] = h->arr[child];
		} else break;
	}
	h->arr[hole] = n;
}

int main(void) {
	int test_cases;
	scanf("%d", &test_cases);
	int i;
	for (i = 0; i < test_cases; i++) {
		int k, n;
		scanf("%d%d", &k, &n);
		
		Heap* h = initHeap(n);
		int j;
		for (j = 0; j < n; j++) {
			int num;
			scanf("%d", &num);
			Node node = {num, 1, num};
			push(h, node);
		}
		
		int* ugly = (int*) malloc(sizeof(int) * k);
		ugly[0] = 1;
		for (j = 1; j < k; j++) {
			Node node = getMin(h);
			ugly[j] = node.val;
			while (ugly[j] == node.val) {
				node.val = node.base * ugly[node.index];
				node.index++;
				deleteMin(h);
				push(h, node);
				
				node = getMin(h);
			}
		}

		printf("%d\n", ugly[k-1]);
		free(ugly);
		freeHeap(h);
	}
	return 0;
}
