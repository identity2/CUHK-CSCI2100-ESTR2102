#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    int cases;
    scanf("%d", &cases);
    int i;
    for (i = 0; i < cases; i++) {
        char s[128], t[128], map1[26], map2[26];
        scanf("%s", s);
        scanf("%s", t);
        int len = strlen(s);
        if (len != strlen(t)) {
            puts("NO");
            continue;
        }

        int j;
        for (j = 0; j < 26; j++) {
            map1[j] = map2[j] = '\0';
        }

        int success = 1;
        for (j = 0; j < len; j++) {
            char ch1 = s[j];
            char ch2 = t[j];
            int i1 = ch1 - 'a';
            int i2 = ch2 - 'a';
            if (map1[i1] == '\0' && map2[i2] == '\0') {
                map1[i1] = ch2;
                map2[i2] = ch1;
            } else if ((map1[i1] != '\0' && map2[i2] == '\0') || (map1[i1] == '\0' && map2[i2] != '\0')) {
                success = 0;
                break;
            } else if (map1[i1] == ch2 && map2[i2] == ch1) {
                    continue;
            } else {
                success = 0;
                break;
            }
        }
        if (success) puts("YES");
        else puts("NO");
    }
    return 0;
}