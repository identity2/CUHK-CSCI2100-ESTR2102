#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1024

typedef struct Node {
    int val;
    struct Node* next;
} node;

typedef struct Queue {
    node* head;
    node* rear;
} queue;

queue* init_queue() {
    queue* q = (queue*) malloc(sizeof(queue));
    q->head = q->rear = (node*) malloc(sizeof(node));
    q->head->next = NULL;
    return q;
}

void free_queue(queue* q) {
    node* n = q->head;
    while (n) {
        node* temp = n->next;
        free(n);
        n = temp;
    }
    free(q);
}

int is_empty(queue* q) {
    return q->head == q->rear;
}

int front(queue* q) {
    if (is_empty(q)) {
        puts("No front element in an empty queue.");
        return -1;
    }

    return q->head->next->val;
}

void push(queue* q, int val) {
    node* n = (node*) malloc(sizeof(node));
    n->val = val;
    n->next = NULL;
    q->rear->next = n;
    q->rear = n;
}

void pop(queue* q) {
    if (is_empty(q)) {
        puts("Can't pop in an empty queue.");
        return;
    }

    node* n = q->head->next;
    if (n == q->rear) {
        q->rear = q->head;
    }

    q->head->next = q->head->next->next;
    free(n);
}

void print(queue* q) {
    node* n = q->head->next;
    while (n) {
        printf("%d ", n->val);
        n = n->next;
    }
    putchar('\n');
}

int check_bipartite(int graph[][MAX_SIZE], int n, int start, int color_arr[]) {
    color_arr[start] = 1;

    queue* q = init_queue();
    push(q, start);

    // Breadth first search.
    while (!is_empty(q)) {
        int u = front(q);
        pop(q);

        // Color adjacent vertices.
        for (int v = 0; v < n; v++) {
            if (graph[u][v] && color_arr[v] == -1) {
                color_arr[v] = !color_arr[u];
                push(q, v);
            } else if (graph[u][v] && color_arr[v] == color_arr[u]) {
                // Cannot color the graph into bipartite.
                free_queue(q);
                return 0;
            }
        }
    }

    free_queue(q);
    return 1;
}

int is_bipartite(int graph[][MAX_SIZE], int n) {
    int color_arr[MAX_SIZE];
    for (int i = 0; i < n; i++)
        color_arr[i] = -1; // Not colored.

    for (int i = 0; i < n; i++) {
        if (color_arr[i] == -1) {
            if (!check_bipartite(graph, n, i, color_arr))
                return 0;
        }
    }

    return 1;
}

// For every i, j in {1, 2, ..., N},
// If there exists a k such that k < i < j and seq[i] < seq[j] < seq[k],
// seq[i] and seq[j] can't be pushed onto the same stack. So add an edge between them.
void generate_graph(int graph[][MAX_SIZE], int* seq, int n) {
    int i, j;
    int max_nums[MAX_SIZE];

    // printf("Max Nums: ");
    for (i = 0; i < n; i++) {
        max_nums[i] = seq[i];
        
        if (i > 0 && max_nums[i-1] > max_nums[i]) {
            max_nums[i] = max_nums[i-1];
        }
        // printf("%d", max_nums[i]);
    }
    // putchar('\n');

    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (i > 0 && seq[i] < seq[j] && max_nums[i-1] > seq[j]) {
                graph[i][j] = graph[j][i] = 1;
            }
        }
    }
}

void clear_graph(int graph[][MAX_SIZE], int n) {
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            graph[i][j] = 0;
}

void print_graph(int graph[][MAX_SIZE], int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", graph[i][j]);
        }
        putchar('\n');
    }
}

int main(void) {
    int cases, i;
    int seq[MAX_SIZE];
    int graph[MAX_SIZE][MAX_SIZE];
    clear_graph(graph, MAX_SIZE);

    scanf("%d", &cases);
    for (i = 0; i < cases; i++) {
        int n, j;
        scanf("%d", &n);
        for (j = 0; j < n; j++) {
            scanf("%d", &seq[j]);
            seq[j] -= 1; // Always start the index with 0.
        }

        generate_graph(graph, seq, n);
        // print_graph(graph, n);
        int result = is_bipartite(graph, n);
        if (result)
            puts("Yes");
        else
            puts("No");

        clear_graph(graph, n);
    }
    return 0;
}