#include <stdio.h>

int main(void) {
	int cases;
	scanf("%d", &cases);

	unsigned int a, b;
	int i;
	for (i = 0; i < cases; i++) {
		scanf("%u%u", &a, &b);
		if (a == 0) {
			printf("%u\n", b);
			continue;
		}

		int msb = 15;
		int mask = 1 << msb;
		while (mask > 0 && (mask & b) == 0) {
			msb--;
			mask = mask >> 1;
		}

		if (mask == 0) {
			printf("%d\n", a);
			continue;
		}
		
		printf("%u\n", (a << (msb + 1)) | b);
	}

	return 0;
}
