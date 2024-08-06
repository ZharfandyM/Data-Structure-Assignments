#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int src, dest, weight;
} Edge;

typedef struct {
    int V, E;
    Edge edge[MAX];
} Graph;

typedef struct {
    int parent, rank;
} Subset;

Graph* createGraph(int V, int E) {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->V = V;
    graph->E = E;
    return graph;
}

int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void Union(Subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank)
        subsets[rootX].parent = rootY;
    else if (subsets[rootX].rank > subsets[rootY].rank)
        subsets[rootY].parent = rootX;
    else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

int compare(const void* a, const void* b) {
    Edge* edgeA = (Edge*) a;
    Edge* edgeB = (Edge*) b;
    return edgeA->weight > edgeB->weight;
}

void KruskalMST(Graph* graph) {
    int V = graph->V;
    Edge result[V];
    int e = 0;
    int i = 0;

    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), compare);

    Subset* subsets = (Subset*) malloc(V * sizeof(Subset));

    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    while (e < V - 1 && i < graph->E) {
        Edge next_edge = graph->edge[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    printf("Edges in the Minimum Spanning Tree:\n");
    for (i = 0; i < e; ++i)
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
    return;
}

int main() {
    int V = 5;  // Number of vertices in graph
    int E = 7;  // Number of edges in graph
    Graph* graph = createGraph(V, E);

    // Adding edges
    graph->edge[0].src = 0;  // Data center
    graph->edge[0].dest = 1; // Kantor1
    graph->edge[0].weight = 30;

    graph->edge[1].src = 0;
    graph->edge[1].dest = 2; // Kantor2
    graph->edge[1].weight = 20;

    graph->edge[2].src = 0;
    graph->edge[2].dest = 3; // Pemukiman1
    graph->edge[2].weight = 10;

    graph->edge[3].src = 1;
    graph->edge[3].dest = 3;
    graph->edge[3].weight = 5;

    graph->edge[4].src = 1;
    graph->edge[4].dest = 4; // Pemukiman2
    graph->edge[4].weight = 25;

    graph->edge[5].src = 2;
    graph->edge[5].dest = 3;
    graph->edge[5].weight = 13;

    graph->edge[6].src = 2;
    graph->edge[6].dest = 4;
    graph->edge[6].weight = 40;

    KruskalMST(graph);

    return 0;
}
