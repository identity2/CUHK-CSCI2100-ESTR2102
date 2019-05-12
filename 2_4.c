#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node {
	struct Node* prev;
	struct Node* next;
	int val;
} node;

typedef struct Number {
	node* head;   /* The head node indicates whether is number is positive or negative. */
	node* tail;
} number;

node* init_node(int val) {
	node* n = (node*) malloc(sizeof(node));
	n->prev = n->next = NULL;
	n->val = val;
	return n;
}

void push_back(number* num, int val) {
	node* n = init_node(val);
	n->next = num->tail;
	n->prev = num->tail->prev;
	num->tail->prev->next = n;
	num->tail->prev = n;
}

void push_front(number* num, int val) {
	node* n = init_node(val);
	n->next = num->head->next;
	n->prev = num->head;
	num->head->next->prev = n;
	num->head->next = n;
}

number* init_number() {
	number* num = (number*) malloc(sizeof(number));
	num->head = init_node(1);
	num->tail = init_node(0);
	
	num->head->next = num->tail;
	num->tail->prev = num->head;
	
	return num;
}

void free_number(number* num) {
	node* curr = num->head;
	while (curr) {
		node* temp = curr;
		curr = curr->next;
		free(temp);
	}
	
	free(num);
}

number* str_to_number(char* str) {
	size_t len = strlen(str);
	number* num = init_number();
	
	int i;
	for (i = 0; i < len; i++) {
		if (str[i] == '-') {
			num->head->val = -1;
			continue;
		}

		push_back(num, str[i] - '0');
	}

	return num;
}

void print(number* num) {
	if (num->head->val == -1)
		putchar('-');

	node* curr = num->head->next;
	
	while (curr != num->tail) {
		printf("%d", curr->val);
		curr = curr->next;
	}

	putchar('\n');
}

void apply_carries(number* num) {
	// printf("apply_carrie: ");
	// print(num);
	int carry = 0;
	node* curr = num->tail->prev;
	while (curr != num->head) {
		int val = curr->val + carry;
		carry = val / 10;
		curr->val = val % 10;
		curr = curr->prev;
	}

	if (carry) {
		push_front(num, carry);
	}

	// printf("result: ");
	// print(num);
}

number* single_digit_multiply(number* num, int digit) {
	// printf("single_digit_multiply: %d x ", digit);
	// print(num);

	number* res = init_number();
	node* curr = num->tail->prev;
	while (curr != num->head) {
		push_front(res, digit * curr->val);
		curr = curr->prev;
	}
	apply_carries(res);
	
	// printf("result: ");
	// print(res);
	return res;
}

number* add(number* n1, number* n2, int n2_shift) {
	// puts("Addition for:");
	// print(n1);
	// print(n2);
	// printf("Shift: %d\n", n2_shift);

	number* res = init_number();
	int curr_digit = 0;
	node* n1_curr = n1->tail->prev;
	node* n2_curr = n2->tail->prev;
	
	/* Do the shiftings. */
	while (curr_digit < n2_shift) {
		if (n1_curr == n1->head) {
			push_front(res, 0);
		} else {
			push_front(res, n1_curr->val);
			n1_curr = n1_curr->prev;
		}
		curr_digit++;
	}

	/* Addition. */
	while (n1_curr != n1->head || n2_curr != n2->head) {
		int val = 0;
		if (n1_curr != n1->head) {
			val += n1_curr->val;
			// printf("n1_curr->val: %d\n", n1_curr->val);
			n1_curr = n1_curr->prev;
		}

		if (n2_curr != n2->head) {
			// printf("n2_curr->val: %d\n", n2_curr->val);
			val += n2_curr->val;
			n2_curr = n2_curr->prev;
		}
		push_front(res, val);
		// printf("Push front: ");
		// print(res);
		// printf("with val: %d\n ->", val);
		// print(res);
	}

	// printf("Result before carrying: ");
	// print(res);
	apply_carries(res);
	
	return res;
}

void multiply_and_print(number* n1, number* n2) {
	// printf("Multiply: \n");
	// print(n1);
	// print(n2);
	
	int positiviy = n1->head->val * n2->head->val;
	number* res = init_number();
	push_back(res, 0);

	int digit_shift = 0;
	node* n2_curr = n2->tail->prev;
	while (n2_curr != n2->head) {
		number* temp = single_digit_multiply(n1, n2_curr->val);
		number* addition = add(res, temp, digit_shift);
		
		free_number(temp);
		temp = res;
		free_number(temp);
		res = addition;

		n2_curr = n2_curr->prev;
		digit_shift++;
	}
	
	res->head->val = positiviy;

	print(res);
	free_number(res);
}

int get_len(number* num) {
	int len = 0;
	node* curr = num->head;
	while (curr != num->tail) {
		len++;
		curr = curr->next;
	}

	return len;
}

int is_greater(node* head1, node* from1, node* head2, node* from2) {
	int len1 = 0;
	int len2 = 0;

	while (from1 != head1) {
		len1++;
		from1 = from1->prev;
	}

	while (from2 != head2) {
		len2++;
		from2 = from2->prev;
	}

	if (len1 == len2)
		return head1->next->val > head2->next->val;

	return len1 > len2;
}

/* The first number will change to the result. */
void substract(node* head1, node* tail1, node* head2, node* tail2) {
	node* curr1 = tail1->prev;
	node* curr2 = tail2->prev;

	while (curr1 != head1) {
		int val = curr1->val;
		if (curr2 != head2) {
			val -= curr2->val;
			curr2 = curr2->prev;
		}
		curr1 = curr1->prev;
	}

	/* Add up the negative numbers. */
	curr1 = tail1->prev;
	while (curr1 != head1) {
		/* TODO */
	}
}

void divide_and_print(number* n1, number* n2) {
	int positivity = n1->head->val * n2->head->val;
	int len1 = get_len(n1);
	int shift = get_len(n2) - 1;

	/* Division by zero */
	if (shift == 1 && n2->head->next->val == 0) {
		puts("Error: division by zero.");
		return;
	}
	
	/* n1 is smaller */
	if (is_greater(n2->head, n2->tail->prev, n1->head, n1->tail->prev)) {
		int temp = n1->head->val;
		n1->head->val = positivity;
		printf("0 ");
		print(n1);
		n1->head->val = temp;
		return;
	}

	/* shift to the first long division position. */
	node* n1_curr = n1->head->next;
	int i;
	for (i = 0; i < shift; i++)
		n1_curr = n1_curr->next;

	

}

int main(void) {
	char str[128];
	int cases;
	scanf("%d", &cases);
	getchar(); /* remove the line break. */

	number *n1, *n2;
	char operator;
	int i;
	for (i = 0; i < cases; i++) {
		/* Get the operator. */
		operator = getchar();
		getchar();

		/* Get the numbers. */
		gets(str);
		n1 = str_to_number(str);
		gets(str);
		n2 = str_to_number(str);
		
		/* Calculate and print. */
		if (operator == '*')
			multiply_and_print(n1, n2);
		else if (operator == '/')
			divide_and_print(n1, n2);

		/* Free the numbers. */
		free_number(n1);
		free_number(n2);

		/* Remove the white blank line. */
		if (i < cases - 1) {
			gets(str);
			putchar('\n');
		}
	}

	return 0;
}
