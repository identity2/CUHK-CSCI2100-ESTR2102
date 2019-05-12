#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int x, int y) {
    return x > y ? x : y;
}

int min(int x, int y) {
    return x < y ? x : y;
}

int main(void) {
    int N, L;
    scanf("%d%d", &N, &L);
    int* arr = malloc(sizeof(int) * N);
    int i;
    for (i = 0; i < N; i++)
        arr[i] = 0;
    
    for (i = 0; i < L; i++) {
        char str[4];
        scanf("%s", str);
        if (strcmp(str, "T") == 0) {
            int from, to;
            scanf("%d%d", &from, &to);
            from--;
            to--;
            for (; from <= to; from++) {
                arr[from] = !arr[from];
            }
        } else if (strcmp(str, "O") == 0) {
            int maxFront = 0;
            int maxBack = 0;
            int currCount = 1;
            int j;
            for (j = 1; j < N; j++) {
                if (arr[j] != arr[j-1]) {
                    if (arr[j-1]) {
                        maxFront = max(maxFront, currCount);
                    } else {
                        maxBack = max(maxBack, currCount);
                    }

                    currCount = 1;
                } else {
                    currCount++;
                }
            }
            if (arr[j-1]) maxFront = max(maxFront, currCount);
            else maxBack = max(maxBack, currCount);
            printf("%d %d\n", maxFront, maxBack);
        }
    }

    free(arr);
    return 0;
}