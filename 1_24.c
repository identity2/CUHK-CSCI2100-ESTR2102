#include <stdio.h>
#include <string.h>
#define STR_SIZE 256

void reverse(char* str) {
	int len = strlen(str);
	
	if (len < 2) return;
	int i = 0, j = len - 1;
	while (i < j) {
		char temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		
		i++;
		j--;
	}
}

int main(void) {
	int cases;
	scanf("%d", &cases);
	while (getchar() != '\n') continue;
	char str[STR_SIZE];
	int i;
	for (i = 0; i < cases; i++) {
		gets(str);
		reverse(str);
		puts(str);
	}

	return 0;
}
