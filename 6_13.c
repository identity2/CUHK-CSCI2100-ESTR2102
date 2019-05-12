#include <stdio.h>
#include <stdlib.h>

int max(int x, int y) {
    return x > y ? x : y;
}

int min(int x, int y) {
    return x < y ? x : y;
}

double findMedian(int* M, int m, int* N, int n) {
    if (m == 0 && n == 0) return 0.0;
    int count = 0;
    int target = (m + n) / 2;
    int i = 0, j = 0, currNum;
    if (m == 0) currNum = N[target - 1];
    if (n == 0) currNum = M[target - 1];
    
    while (i < m && j < n) {
        if (M[i] < N[j]) {
            currNum = M[i];
            i++;
        } else {
            currNum = N[j];
            j++;
        }
        count++;
        if (count == target)
            break;
    }

    int nextNum;
    if (i == m) {
        currNum = target > count ? N[target - count + j - 1] : currNum;
        nextNum = N[target - count + j];
    } else if (j == n) {
        currNum = target > count ? M[target - count + i - 1] : currNum;
        nextNum = M[target - count + i];
    } else {
        nextNum = min(M[i], N[j]);
    }

    return (m + n) % 2 == 0 ? (currNum + nextNum) / 2.0 : nextNum;
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    int i;
    int* M = malloc(sizeof(int) * 10000);
    int* N = malloc(sizeof(int) * 10000);
    for (i = 0; i < cases; i++) {
        int m, n;
        scanf("%d%d", &m, &n);
        int j;
        for (j = 0; j < m; j++) scanf("%d", &M[j]);
        for (j = 0; j < n; j++) scanf("%d", &N[j]);

        printf("%.1f\n", findMedian(M, m, N, n));
    }

    free(M);
    free(N);

    return 0;
}