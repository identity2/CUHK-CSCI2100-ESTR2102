#include <stdio.h>
#include <stdlib.h>

int count = 0;

typedef struct Node {
	int val;
	int height;
	struct Node* children[2];
} node;

node* init_node(int val) {
	node* n = (node*) malloc(sizeof(node));
	n->children[0] = n->children[1] = NULL;
	n->val = val;
	n->height = 1;
	return n;
}

int height(node* n) {
	if (!n) return 0;
	return n->height;
}

int balancing(node* n) {
	return height(n->children[0]) - height(n->children[1]);
}

int max(int x, int y) {
	return x > y ? x : y;
}

void update_height(node* n) {
	n->height = max(height(n->children[0]), height(n->children[1])) + 1;
}

node* rotate(node* n, int pivot) {
	count++;
	node* k1 = n->children[pivot];
	n->children[pivot] = k1->children[!pivot];
	k1->children[!pivot] = n;
	
	update_height(n);
	update_height(k1);
	
	return k1;
}

node* double_rotate(node* n, int pivot) {
	n->children[pivot] = rotate(n->children[pivot], !pivot);
	n = rotate(n, pivot);
	return n;
}

node* perform_rotation(node* n, int pivot, int single_rot) {
//	printf("Imbalance at %d, perform %d rotation, single: %d.\n", n->val, pivot, single_rot);
	if (single_rot)
		return rotate(n, pivot);
	
	return double_rotate(n, pivot);
}

node* insert(node* n, int val) {
	if (!n) return init_node(val);
	
	if (val < n->val)
		n->children[0] = insert(n->children[0], val);
	else
		n->children[1] = insert(n->children[1], val);
	
	update_height(n);

	int balance = balancing(n);
	if (balance == 2)
		n = perform_rotation(n, 0, val < n->children[0]->val);
	else if (balance == -2)
		n = perform_rotation(n, 1, val > n->children[1]->val);

	return n;
}

void preorder(node* n) {
	printf("%d ", n->val);
	if (n->children[0]) preorder(n->children[0]);
	if (n->children[1]) preorder(n->children[1]);
}

void free_tree(node* n) {
	if (!n) return;

	if (n->children[0])
		free_tree(n->children[0]);

	if (n->children[1])
		free_tree(n->children[1]);

	free(n);
}

int main(void) {
	int i, cases;
	scanf("%d", &cases);
	for (i = 0; i < cases; i++) {
		int node_count, j;
		node* root = NULL;
		scanf("%d", &node_count);
		count = 0;
		for (j = 0; j < node_count; j++) {
			int num;
			scanf("%d", &num);
			root = insert(root, num);
		}
//		preorder(root);
//		putchar('\n');
		printf("%d\n", count);
		free_tree(root);
	}
	return 0;
}
