#include <stdlib.h>
#include <stdio.h>

enum Type {ACTIVE, DELETED, EMPTY};

typedef struct _entry {
    enum Type type;
    int key;
} Entry;

typedef struct _hash_set {
    int currSize;
    int maxSize;
    Entry* arr;
} HashSet;

int isPrime(int num) {
    int i;
    for (i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int nextPrime(int num) {
    while (!isPrime(num)) num++;
    return num;
}

Entry* initEntryList(int size) {
    Entry* entry = malloc(sizeof(Entry) * size);
    int i;
    for (i = 0; i < size; i++)
        entry[i].type = EMPTY;
    return entry;
}

HashSet* initHashSet(int size) {
    HashSet* hs = malloc(sizeof(HashSet));
    size = nextPrime(size);
    // printf("Init hash set with size: %d\n", size);
    hs->arr = initEntryList(size);
    hs->currSize = 0;
    hs->maxSize = size;
    return hs;
}

int hash(HashSet* hs, int key, int probes) {
    return ((abs(key) % hs->maxSize) + probes * probes) % hs->maxSize;
}

int find(HashSet* hs, int key) {
    int probes = 0;
    int hashVal = hash(hs, key, probes);
    while (hs->arr[hashVal].type == DELETED || (hs->arr[hashVal].type == ACTIVE && hs->arr[hashVal].key != key)) {
        probes++;
        hashVal = hash(hs, key, probes);
    }
    if (hs->arr[hashVal].type == EMPTY) {
        return 0;
    }
    return 1;
}

void freeHashSet(HashSet* hs) {
    free(hs->arr);
    free(hs);
}

HashSet* insert(HashSet* hs, int key) {
    int probes = 0;
    int hashVal = hash(hs, key, probes);
    while (hs->arr[hashVal].type == ACTIVE) {
        probes++;
        hashVal = hash(hs, key, probes);
    }

    hs->arr[hashVal].type = ACTIVE;
    hs->arr[hashVal].key = key;

    hs->currSize++;

    if (hs->currSize * 2 >= hs->maxSize) {
        HashSet* old = hs;
        hs = initHashSet(old->maxSize * 2);
        int i;
        for (i = 0; i < old->maxSize; i++) {
            if (old->arr[i].type == ACTIVE) {
                insert(hs, old->arr[i].key);
            }
        }
        freeHashSet(old);
    }
    return hs;
}

int main(void) {
    int shapeCount, doorCount;
    scanf("%d%d", &shapeCount, &doorCount);
    int* shapes = malloc(sizeof(int) * shapeCount);
    int* doors = malloc(sizeof(int) * doorCount);
    HashSet* hs = initHashSet(shapeCount * 2);
    int i;
    for (i = 0; i < shapeCount; i++) {
        scanf("%d", &shapes[i]);
        hs = insert(hs, shapes[i]);
    }
    for (i = 0; i < doorCount; i++)
        scanf("%d", &doors[i]);
    
    int j;
    for (i = 0; i < doorCount; i++) {
        int success = 0;
        for (j = 0; j < shapeCount; j++) {
            if (find(hs, doors[i] - shapes[j])) {
                puts("Yes");
                success = 1;
                break;
            }
        }
        if (!success) puts("No");
    }

    return 0;
}