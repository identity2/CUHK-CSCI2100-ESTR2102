#include <stdio.h>

int arr[1000];

int greater(int x, int y) {
    int outerX, outerY;
    if (x / 10 == 0) outerX = x;
    else outerX = x / 10;

    if (y / 10 == 0) outerY = y;
    else outerY = y / 10;

    if (outerX > outerY) return 1;
    else if (outerX < outerY) return 0;
    
    return (x % 10) > (y % 10);
}

void insertionSort(int left, int right) {
    int i;
    for (i = left + 1; i <= right; i++) {
        int temp = arr[i];
        int j;
        for (j = i; j > left && greater(arr[j-1], temp); j--)
            arr[j] = arr[j-1];
        arr[j] = temp;
    }
}

void print(int n) {
    int i;
    for (i = 0; i < n; i++)
        printf("%d", arr[i]);
    putchar('\n');
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    int c;
    for (c = 0; c < cases; c++) {
        int n, j;
        scanf("%d", &n);
        for (j = 0; j < n; j++)
            scanf("%d", &arr[j]);
        insertionSort(0, n-1);
        print(n);
    }
    return 0;
}