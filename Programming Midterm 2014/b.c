#include <stdlib.h>
#include <stdio.h>

long array[1024];

void insertionSort(long* arr, int left, int right) {
    int i,j;
    for (i = left + 1; i <= right; i++) {
        long temp = arr[i];
        for (j = i; j > left && arr[j-1] > temp; j--) {
            arr[j] = arr[j-1];
        }
        arr[j] = temp;
    }
}

void swap(long* x, long* y) {
    long temp = *x;
    *x = *y;
    *y = temp;
}

long median3(long* arr, int left, int right) {
    int mid = (left + right) / 2;
    if (arr[left] > arr[mid]) swap(&arr[left], &arr[mid]);
    if (arr[left] > arr[right]) swap(&arr[left], &arr[right]);
    if (arr[mid] > arr[right]) swap(&arr[mid], &arr[right]);
    swap(&arr[mid], &arr[right-1]);
    return arr[right-1];
}

void quickSort(long* arr, int left, int right) {
    if (right - left < 10) {
        insertionSort(arr, left, right);
    } else {
        long pivot = median3(arr, left, right);
        int i = left, j = right - 1;
        while (1) {
            while (arr[++i] < pivot) {}
            while (arr[--j] > pivot) {}

            if (i < j) swap(&arr[i], &arr[j]);
            else break;
        }
        swap(&arr[right-1], &arr[i]);
        quickSort(arr, left, i - 1);
        quickSort(arr, i + 1, right);
    }
}

long getNum(long* arr, int len) {
    int count = 1;
    int i;
    for (i = 1; i < len; i++) {
        if (arr[i] == arr[i-1])
            count++;
        else
            count = 1;
        
        if (count == len / 2)
            return arr[i];
    }
    return -1;
}

int main(void) {
    int testCases;
    scanf("%d", &testCases);
    int c;
    for (c = 0; c < testCases; c++) {
        int n;
        scanf("%d", &n);
        int i;
        for (i = 0; i < n; i++) {
            scanf("%ld", &array[i]);
        }
        quickSort(array, 0, n - 1);
        printf("%ld\n", getNum(array, n));
    }
    return 0;
}