#include <stdio.h>
#include <string.h>
#define STR_MAX 256

/* return -1 if bad input */
int convert_to_num(char ch) {
	if (ch < 'A' || ch > 'M')
		return -1;
	
	return ch - 'A' + 1;
}

int check_valid(int sum, char check) {
	int reminder = sum % 11;
	if (reminder == 0 && check == '0') return 1;
	else if (reminder == 1 && check == 'A') return 1;
	else if (check == '0' + (11 - reminder)) return 1;

	return 0;
}

int check_minus(char* line) {
	if (line[1] != '-' || line[5] != '-' || line[9] != '-')
		return 0;

	return 1;
}

int check_digit(char* line) {
	int check_indices[6] = {2, 3, 4, 6, 7, 8};
	int i;
	for (i = 0; i < 6; i++) {
		char ch = line[check_indices[i]];
		if (ch < '0' || ch > '9')
			return 0;
	}
	return 1;
}

int main(void) {
	int cases;
	scanf("%d", &cases);
	while (getchar() != '\n') continue;

	char line[STR_MAX];
	int i;
	for (i = 0; i < cases; i++) {
		gets(line);
		if (strlen(line) != 11) {
			puts("False");
			continue;
		}

		int first = convert_to_num(line[0]);
		if (first == -1) {
			puts("False");
			continue;
		}

		if (!check_minus(line) || !check_digit(line)) {
			puts("False");
			continue;
		}

		int multiplier = 7;
		int indices[6] = {2, 3, 4, 6, 7, 8};
		int n;
		int sum = 8 * first;
		for (n = 0; n < 6; n++) {
			sum += multiplier * (line[indices[n]] - '0');
			multiplier--;
		}

		if (check_valid(sum, line[10])) {
			puts("True");
			continue;
		}

		puts("False");
	}
	
	return 0;
}
