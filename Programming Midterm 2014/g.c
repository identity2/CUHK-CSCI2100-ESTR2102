#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum Type {ACTIVE, DELETED, EMPTY};

typedef struct _entry {
    enum Type type;
    char key[444];
} Entry;

typedef struct _hash_set {
    int currSize;
    int maxSize;
    Entry* arr;
} HashSet;

int isPrime(int num) {
    int i;
    for (i = 2; i * i <= num; i++) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

int nextPrime(int num) {
    while (!isPrime(num)) {
        num++;
    }
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
    hs->arr = initEntryList(size);
    hs->currSize = 0;
    hs->maxSize = size;
    return hs;
}

void freeHashSet(HashSet* hs) {
    free(hs->arr);
    free(hs);
}

int hash(HashSet* hs, int key, int probes) {
    return ((key % hs->maxSize) + probes * probes) % hs->maxSize;
}

int find(HashSet* hs, char* str) {
    int probes = 0;
    int i = 0;
    int len = strlen(str);
    int key = 0;
    for (i = 0; i < len; i++)
        key += (int) str[i] * (i+1);

    int hashVal = hash(hs, key, probes);
    while (hs->arr[hashVal].type == DELETED || (hs->arr[hashVal].type == ACTIVE && strcmp(hs->arr[hashVal].key, str) != 0)) {
        probes++;
        hashVal = hash(hs, key, probes);
    }
    if (hs->arr[hashVal].type == EMPTY)
        return 0;
    return 1;
}

HashSet* insert(HashSet* hs, char* str) {
    int probes = 0;
    int i = 0;
    int len = strlen(str);
    int key = 0;
    for (i = 0; i < len; i++)
        key += (int) str[i] * (i+1);
    int hashVal = hash(hs, key, probes);
    while (hs->arr[hashVal].type == ACTIVE) {
        probes++;
        hashVal = hash(hs, key, probes);
    }

    hs->arr[hashVal].type = ACTIVE;
    strcpy(hs->arr[hashVal].key, str);

    hs->currSize++;

    return hs;
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    getchar();
    int c;
    char str[444];
    HashSet* hs = initHashSet(2500);
    for (c = 0; c < cases; c++) {
        gets(str);
        hs = insert(hs, str);
    }
    
    gets(str);
    cases = atoi(str);
    for (c = 0; c < cases; c++) {
        gets(str);
        puts(find(hs, str) ? "Yes" : "No");
    }
    return 0;
}