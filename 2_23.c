#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BUFFER 64

typedef enum Operator {
	ADD, SUBTRACT, MULTIPLY, DIVIDE, FACTORIAL, NONE
} operator;

typedef struct Node {
	int val;
	struct Node* next;
} node;

typedef struct Stack {
	struct Node* head;
} stack;

node* init_node(int val) {
	node* n = (node*) malloc(sizeof(node));
	n->val = val;
	n->next = NULL;
	return n;
}

stack* init_stack() {
	stack* stk = (stack*) malloc(sizeof(stack));
	stk->head = init_node(-1);
	return stk;
}

void free_stack(stack* stk) {
	node* n = stk->head;
	while (n) {
		node* temp = n->next;
		free(n);
		n = temp;
	}
	free(stk);
}

void push(stack* stk, int val) {
	node* n = init_node(val);
	n->next = stk->head->next;
	stk->head->next = n;
}

int is_empty(stack* stk) {
	return !stk->head->next;
}

void pop(stack* stk) {
	if (is_empty(stk))
		return;

	node* n = stk->head->next;
	stk->head->next = stk->head->next->next;
	free(n);
}

int top(stack* stk) {
	if (is_empty(stk))
		return -1;

	return stk->head->next->val;
}

void print(stack* stk) {
	node* n = stk->head->next;
	while (n) {
		printf("%d ", n->val);
		n = n->next;
	}
	putchar('\n');
}

/* Returns 1 if a line break is reached. */
int read_until_blank(char* str) {
	char ch;
	int i = 0;
	while ((ch = getchar()) != ' ') {
		if (ch == '\n' || ch == EOF) {
			str[i] = '\0';
			return 1;
		}
		
		str[i++] = ch;
	}
	str[i] = '\0';
	return 0;
}

operator get_operator(char* str) {
	if (strcmp(str, "+") == 0)
		return ADD;
	if (strcmp(str, "-") == 0)
		return SUBTRACT;
	if (strcmp(str, "/") == 0)
		return DIVIDE;
	if (strcmp(str, "*") == 0)
		return MULTIPLY;
	if (strcmp(str, "/") == 0)
		return DIVIDE;
	if (strcmp(str, "!") == 0)
		return FACTORIAL;

	return NONE;
}

/* Returns -1 if passed in a negative number. */
int factorial(int num) {
	if (num < 0) return -1;

	int result = 1, i;
	for (i = 2; i <= num; i++) {
		result *= i;
	}
	
	return result;
}

int main(void) {
	int i, test_cases;
	scanf("%d", &test_cases);
	getchar();
	for (i = 0; i < test_cases; i++) {
		char str[BUFFER];	
		stack* stk = init_stack();
		int error = 0;
		int end_of_line = 0;
		do {
			end_of_line = read_until_blank(str);
			operator op = get_operator(str);
			int result;

			if (op == NONE) {
				// puts("We got a number.");
				result = atoi(str);
			} else if (op == FACTORIAL) {
				int num = top(stk);
				// printf("Calculating factorial of %d.\n", num);
				pop(stk);
				result = factorial(num);
				if (result == -1) {
					puts("factorial of an negative number");
					error = 1;
					break;
				}
			} else {
				int num1, num2;
				num2 = top(stk);
				pop(stk);
				num1 = top(stk);
				pop(stk);
				
				if (op == ADD) {
					// printf("Calculating %d + %d.\n", num1, num2);
					result = num1 + num2;
				} else if (op == SUBTRACT) {
					// printf("Calculating %d - %d.\n", num1, num2);
					result = num1 - num2;
				} else if (op == MULTIPLY) {
					// printf("Calculating %d * %d.\n", num1 , num2);
					result = num1 * num2;
				} else if (op == DIVIDE) {
					// printf("Calculating %d / %d.\n", num1, num2);
					if (num2 == 0) {
						puts("division by zero");
						error = 1;
						break;
					}

					result = num1 / num2;
				}
			}
			
			// printf("  > Push the result %d on stack.\n", result);
			push(stk, result);
		} while (!end_of_line);

		if (!error)
			printf("%d\n", top(stk));
		
		free_stack(stk);
	}
	return 0;
}
