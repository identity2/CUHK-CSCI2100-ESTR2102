#include <stdio.h>
#include <stdlib.h>

int indegree[500];
int graph[500][500];

void clearGraph(int cap) {
    int i, j;
    for (i = 0; i < cap; i++)
        for (j = 0; j < cap; j++)
            graph[i][j] = 0;
    
    for (i = 0; i < cap; i++)
        indegree[i] = 0;
}

void constructGraph(int m) {
    int i;
    for (i = 0; i < m; i++) {
        int from, to;
        scanf("%d%d", &from, &to);
        from--;
        to--;
        graph[from][to] = 1;
        indegree[to]++;
    }
}

int getZeroIndegIndex(int n) {
    int i;
    for (i = 0; i < n; i++) {
        if (indegree[i] == 0)
            return i;
    }
    return -1;
}

void topsort(int n, int m) {
    int i;
    for (i = 0; i < n; i++) {
        int vert = getZeroIndegIndex(n);
        printf(i == 0 ? "%d" : " %d", vert + 1);
        indegree[vert] = -1; // visited.

        // Decrease indegrees of adjacent vertices.
        int j;
        for (j = 0; j < n; j++) {
            if (graph[vert][j] == 1)
                indegree[j]--;
        }
    }
    putchar('\n');
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    int c;
    clearGraph(500);
    for (c = 0; c < cases; c++) {
        int n, m;
        scanf("%d%d", &n, &m);
        
        constructGraph(m);
        topsort(n, m);

        clearGraph(n);
    }
    return 0;
}