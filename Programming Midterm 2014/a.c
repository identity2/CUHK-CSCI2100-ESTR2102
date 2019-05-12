#include <string.h>
#include <stdio.h>
#include <ctype.h>

int main(void) {
    char str[312];
    int test_cases;
    scanf("%d", &test_cases); getchar();
    int c;
    for (c = 0; c < test_cases; c++) {
        gets(str);
        int i = 0, j = strlen(str) - 1;
        int success = 1;
        while (i < j) {
            if (tolower(str[i]) != tolower(str[j])) {
                puts("No");
                success = 0;
                break;
            }
            ++i;
            --j;
        }
        if (success) puts("Yes");
    }
    return 0;
}