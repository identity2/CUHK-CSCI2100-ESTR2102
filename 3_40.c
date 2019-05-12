#include <stdio.h>
#include <stdlib.h>

int res[1024];
int res_i = 0;

typedef struct TreeNode {
	int val;
	struct TreeNode* children[2];
} tree_node;

typedef struct ListNode {
	tree_node* val;
	struct ListNode* next;
} list_node;

typedef struct Queue {
	list_node* head;
	list_node* rear;
} queue;

tree_node* init_tn(int val) {
	tree_node* tn = (tree_node*) malloc(sizeof(tree_node));
	tn->children[0] = tn->children[1] = NULL;
	tn->val = val;
	return tn;
}

queue* init_queue() {
//	puts("Queue initialized.");
	queue* q = (queue*) malloc(sizeof(queue));
	q->head = (list_node*) malloc(sizeof(list_node));
	q->rear = q->head;
	return q;
}

void free_queue(queue* q) {
//	puts("Queue freed.");
	list_node* node = q->head;
	while (node) {
		list_node* temp = node->next;
		free(node);
		node = temp;
	}
	free(q);
}

void push(queue* q, tree_node* node) {
//	printf("Node %d is pushed to the queue.\n", node->val);
	list_node* ln = (list_node*) malloc(sizeof(list_node));
	ln->val = node;
	ln->next = NULL;

	q->rear->next = ln;
	q->rear = ln;
}

int is_empty(queue* q) {
	if (q->head == q->rear)
		return 1;
	return 0;
}

tree_node* front(queue* q) {
	if (is_empty(q)) {
		puts("The queue is empty, no front.");
		return NULL;
	}

	return q->head->next->val;
}

void pop(queue* q) {
	if (is_empty(q)) {
		puts("The queue is empty, cannot pop.");
		return;
	}
	
	if (q->head->next == q->rear)
		q->rear = q->head;

	list_node* temp = q->head->next;
//	printf("Node %d is popped.\n", temp->val->val);
	q->head->next = q->head->next->next;
	free(temp);
}

void inorder(tree_node* root) {
	if (root->children[0] && root->children[0]->val != 0)
		inorder(root->children[0]);

	res[res_i++] = root->val;
	// rintf("%d ", root->val);

	if (root->children[1] && root->children[1]->val != 0)
		inorder(root->children[1]);
}

void free_tree(tree_node* root) {
	if (root->children[0])
		free_tree(root->children[0]);

	if (root->children[1])
		free_tree(root->children[1]);

	free(root);
}

int main(void) {
	int i, cases;
	scanf("%d", &cases);

	for (i = 0; i < cases; i++) {
		int j, node_count, root_val;
		scanf("%d", &node_count);
		
		queue* q = init_queue();
		scanf("%d", &root_val);
		tree_node* root = init_tn(root_val);
		push(q, root);

		int child_index = 0;
		tree_node* parent;
		for (j = 1; j < node_count; j++) {
			if (child_index == 0) {
				parent = front(q);
				pop(q);
			}

			int curr_val;
			scanf("%d", &curr_val);
			tree_node* curr_node = init_tn(curr_val);
			push(q, curr_node);
			
			parent->children[child_index] = curr_node;
			child_index = !child_index;
		}

		res_i = 0;
		inorder(root);

		int k;
		for (k = 0; k < res_i - 1; k++) {
			printf("%d ", res[k]);
		}
		printf("%d", res[k]);
		
		free_tree(root);
		free_queue(q);
		putchar('\n');
	}
	
	return 0;
}
