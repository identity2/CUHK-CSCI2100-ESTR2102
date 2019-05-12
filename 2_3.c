#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node {
	int id[2];
	struct Node* dir[2];
} node;

node* init_node(int* id) {
	node* n = (node*) malloc(sizeof(node));
	n->id[0] = id[0];
	n->id[1] = id[1];
	n->dir[0] = n->dir[1] = NULL;
	return n;
}

/* Returns the node inserted, or the existing node. */
node* find_or_insert(node* head, int d, int* id, node* existing) {
	node* curr = head;
	
	while (curr->dir[d] && curr->dir[d]->id[d] < id[d])
		curr = curr->dir[d];

	if (curr->dir[d] && curr->dir[d]->id[d] == id[d])
		return curr->dir[d];   /* Node already exists. */
	
	
	node* n = existing ? existing : init_node(id);
	n->dir[d] = curr->dir[d];
	curr->dir[d] = n;

	return n;
}

void add(node* head, int sid, int cid) {
	int id[2] = {sid, cid};
	
	node* student = find_or_insert(head, 0, id, NULL);
	node* course = find_or_insert(head, 1, id, NULL);
	node* n = find_or_insert(student, 1, id, NULL);
	find_or_insert(course, 0, id, n);
}

void print(node* head, int d, int id) {
	int fake_id[2] = {0, 0};
	fake_id[d] = id;
	node* curr = find_or_insert(head, d, fake_id, NULL);
	
	int new_d = !d;
	if (!curr->dir[new_d]) {
		puts("NIL");
		return;
	}

	while (curr->dir[new_d]) {
		curr = curr->dir[new_d];
		printf("%d ", curr->id[new_d]);
	}
	putchar('\n');
}

void drop(node* head, int sid, int cid) {
	int id[2] = {sid, cid};
	node* curr = head;
	node* target = NULL;

	int i;
	for (i = 0; i < 2; i++) {
	
		while (curr->dir[i] && curr->dir[i]->id[i] < id[i])
			curr = curr->dir[i];

		if (!curr->dir[i] || curr->dir[i]->id[i] > id[i])
			return;   /* No such entry */

		curr = curr->dir[i];

		int j = !i;
		while (curr->dir[j] && curr->dir[j]->id[j] < id[j])
			curr = curr->dir[j];

		if (!curr->dir[j] || curr->dir[j]->id[j] > id[j])
			return; /* No such entry */
	
		if (!target)
			target = curr->dir[j];

		curr->dir[j] = curr->dir[j]->dir[j];
		
		free(target);
	}
}

int main(void) {
	node* head = (node*) malloc(sizeof(node));
	head->dir[0] = head->dir[1] = NULL;

	char command[10];
	while (1) {
		scanf("%s", command);
		if (strcmp(command, "ADD") == 0) {
			int sid, cid;
			scanf("%d%d", &sid, &cid);
			add(head, sid, cid);
		} else if (strcmp(command, "PRINTC") == 0) {
			int id;
			scanf("%d", &id);
			print(head, 1, id);
		} else if (strcmp(command, "PRINTS") == 0) {
			int id;
			scanf("%d", &id);
			print(head, 0, id);
		} else if (strcmp(command, "DROP") == 0) {
			int sid, cid;
			scanf("%d%d", &sid, &cid);
			drop(head, sid, cid);
		}
	}

	return 0;
}
