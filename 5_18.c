#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 97

enum Type {ACTIVE, EMPTY};

typedef struct _entry {
    enum Type type;
    char key;
    char val;
} Entry;

Entry arr[97];

int hash(char key, int probes) {
    return (((int) key % 97) + probes * probes) % 97;
}

char find(char key) {
    int probes = 0;
    int hashVal = hash(key, probes);
    while (arr[hashVal].type == ACTIVE && arr[hashVal].key != key)
        hashVal = hash(key, ++probes);
    if (arr[hashVal].type == EMPTY)
        return '\0';
    return arr[hashVal].val;
}

void insert(char key, char val) {
    int probes = 0;
    int hashVal = hash(key, probes);
    while (arr[hashVal].type == ACTIVE) {
        probes++;
        hashVal = hash(key, probes);
    }

    arr[hashVal].type = ACTIVE;
    arr[hashVal].key = key;
    arr[hashVal].val = val;
}

int main(void) {
    int i;
    for (i = 0; i < 97; i++) {
        arr[i].type = EMPTY;
    }

    char* colA = "AEIMQUY26";
    char* colB = "BFJNRVZ37";
    char* colC = "CGKOSW048";
    char* colD = "DHLPTX159";

    int len = strlen(colA);

    for (i = 0; i < len; i++) {
        insert(colA[i], 'A');
        insert(colB[i], 'B');
        insert(colC[i], 'C');
        insert(colD[i], 'D');
    }

    int n;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        int m;
        scanf("%d", &m);
        int j;
        int count = 0;
        char str[24];
        for (j = 0; j < m; j++) {
            scanf("%s", str);
            int len = strlen(str);
            int k;
            char col = find(str[0]);
            int success = 1;
            for (k = 1; k < len; k++) {
                char ch = find(str[k]);
                if (ch == '\0' || ch != col) {
                    success = 0;
                    break;
                }
            }
            if (success) count++;
        }
        printf("%d\n", count);
    }
    return 0;
}