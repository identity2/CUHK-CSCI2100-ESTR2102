#include <stdio.h>

int main(void) {
	int fives, customers, i, result;
	fives = result = 0;
	
	scanf("%d", &customers);
	for (i = 0; i < customers; i++) {
		int curr;
		scanf("%d", &curr);
		if (curr == 5) {
			result++;
			fives++;
		} else if (fives > 0) {
			result++;
			fives--;
		}
	}

	printf("%d\n", result);
	return 0;
}
