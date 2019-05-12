#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#define HASH_INIT_SIZE 101

typedef struct pair {
	int first;
	int second;
} Pair;

typedef struct heap {
	int currSize;
	int maxSize;
	Pair* arr;
} Heap;

enum Type { EMPTY, ACTIVE, DELETED };

typedef struct entry {
	Pair p;
	enum Type type;
} Entry;

typedef struct hash_map {
	int currSize;
	int maxSize;
	Entry* arr;
} HashMap;

HashMap* add(HashMap*, Pair);

Heap* initHeap(int maxSize) {
	Heap* h = (Heap*) malloc(sizeof(Heap));
	h->maxSize = maxSize;
	h->currSize = 0;
	h->arr = (Pair*) malloc(sizeof(Pair) * (maxSize + 1));
	return h;
}

void freeHeap(Heap* h) {
	free(h->arr);
	free(h);
}

void insert(Heap* h, Pair p) {
	if (h->currSize == h->maxSize) {
		puts("The heap is full, cannot insert.");
		return;
	}

	h->currSize++;
	int hole = h->currSize;
	for (; hole > 1 && h->arr[hole / 2].second < p.second; hole /= 2) {
		h->arr[hole] = h->arr[hole / 2];
	}
	h->arr[hole] = p;
}

void deleteMax(Heap* h) {
	if (h->currSize == 0) {
		puts("The heap is empty, cannot deleteMax.");
		return;
	}

	Pair p = h->arr[h->currSize];
	h->currSize--;

	int hole = 1, child;
	for (; hole * 2 <= h->currSize; hole = child) {
		child = hole * 2;
		if (child != h->currSize && h->arr[child].second < h->arr[child + 1].second) {
			child++;
		}
		
		if (h->arr[child].second > p.second) {
			h->arr[hole] = h->arr[child];
		} else break;
	}
	h->arr[hole] = p;
}

Pair getMax(Heap* h) {
	if (h->currSize == 0) {
		puts("Cannot getMax, the heap is empty.");
		Pair p = {-1, -1};
		return p;
	}

	return h->arr[1];
}

HashMap* initHashMap() {
	HashMap* hm = (HashMap*) malloc(sizeof(HashMap));
	hm->currSize = 0;
	hm->maxSize = HASH_INIT_SIZE;
	hm->arr = (Entry*) malloc(sizeof(Entry) * hm->maxSize);
	int i;
	for (i = 0; i < hm->maxSize; i++) {
		hm->arr[i].type = EMPTY;
	}
	return hm;
}

void freeHashMap(HashMap* hm) {
	free(hm->arr);
	free(hm);
}

int isPrime(int num) {
	int i;
	for (i = 2; i * i <= num; i++) {
		if (num % i == 0)
			return 0;
	}
	return 1;
}

int nextPrime(int num) {
	do {
		num++;
	} while (!isPrime(num));
	return num;
}

int hash(HashMap* hm, int val) {
	return val % hm->maxSize;
}

HashMap* checkLoadFactor(HashMap* hm) {
	if (hm->currSize * 2 >= hm->maxSize) {
	//	puts("Load factor exceeds half, rehashing to new HashMap.");
		HashMap* newMap = (HashMap*) malloc(sizeof(HashMap));
		newMap->currSize = 0;
		newMap->maxSize = nextPrime(hm->maxSize * 2);
	//	printf("New maxSize is %d.\n", newMap->maxSize);
		newMap->arr = (Entry*) malloc(sizeof(Entry) * newMap->maxSize);

		int i;
		for (i = 0; i < newMap->maxSize; i++)
			newMap->arr[i].type = EMPTY;

		for (i = 0; i < hm->maxSize; i++) {
			if (hm->arr[i].type == ACTIVE) {
				newMap = add(newMap, hm->arr[i].p);
			}
		}
		freeHashMap(hm);
		return newMap;
	}
	return hm;
}

HashMap* add(HashMap* hm, Pair p) {
	int rehash = 0;
	int key = hash(hm, p.first);
	while (hm->arr[key].type == ACTIVE) {
		rehash++;
		key = (hash(hm, p.first) + rehash * rehash) % hm->maxSize;
	}

	hm->arr[key].p = p;
	hm->arr[key].type = ACTIVE;
	
	hm->currSize++;

	return checkLoadFactor(hm);
}


// Return NULL if not found.
Pair* find(HashMap* hm, int key) {
	int hashVal = hash(hm, key);
	int rehash = 0;
	while (hm->arr[hashVal].type == DELETED || (hm->arr[hashVal].type == ACTIVE && hm->arr[hashVal].p.first != key)) {
//	printf("Finding at %d.\n", hashVal);
	rehash++;
	hashVal = (hash(hm, key) + rehash * rehash) % hm->maxSize;
	}
	if (hm->arr[hashVal].type == EMPTY) {
		return NULL;
	}

	return &(hm->arr[hashVal].p);
}

int main(void) {
	int i, test_cases;
	scanf("%d", &test_cases);
	for (i = 0; i < test_cases; i++) {
		int n, k, j;
		scanf("%d%d", &n, &k);
		HashMap* hm = initHashMap();
		for (j = 0; j < n; j++) {
			int num;
			scanf("%d", &num);
			Pair* p = find(hm, num);
			if (p) {
				p->second++;
			} else {
				Pair newPair = {num, 0};
				hm = add(hm, newPair);
			}
		}
		
		// Sort by heap.
		Heap* h = initHeap(hm->currSize);
		for (j = 0; j < hm->maxSize; j++) {
			if (hm->arr[j].type == ACTIVE) {
				insert(h, hm->arr[j].p);
			}
		}

		for (j = 0; j < k; j++) {
			printf((j == k - 1 ? "%d\n" : "%d "), getMax(h).first);
			deleteMax(h);
		}

		freeHeap(h);
		freeHashMap(hm);
	}

	return 0;
}
