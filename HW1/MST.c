#include <stdio.h> // printf, scanf
#include <stdlib.h> // malloc, free, qsort

struct Edge {
    /* u, v: vertices of the edge
     * w: weight of the edge
     */
    int u, v, w;
};

struct Graph {
    /* V: number of vertices
     * E: number of edges
     * edge: array of edges of the graph (pointer to the first element of the array)
     */
    int V, E;
    struct Edge* edge;
};

struct Graph* createGraph(int V, int E) {
    /* Allocates memory for a graph with V vertices and E edges
     * and returns a pointer to the graph
     */
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph)); // Allocates memory for the graph
    graph->V = V; // Sets the number of vertices
    graph->E = E; // Sets the number of edges
    graph->edge = (struct Edge*) malloc(graph->E * sizeof(struct Edge));
    return graph; // Returns a pointer to the graph
}

int find(int parent[], int i) {
    /* disjoint set find operation
     * Finds the set of the element i
     * and performs path compression
     * using disjoint set data structure
     */
    if (parent[i] == i) // If i is the root
        return i; // Returns i
    return find(parent, parent[i]); // Else returns the root of the set of i with recursive call
}

void Union(int parent[], int rank[], int x, int y) {
    /* disjoint set union operation
     * Unites the sets of x and y
     * using disjoint set data structure
     */
    int xroot = find(parent, x); // Finds the set of x
    int yroot = find(parent, y); // Finds the set of y

    if (rank[xroot] < rank[yroot]) // If the rank of xroot is less than the rank of yroot
        parent[xroot] = yroot; // Then yroot becomes the parent of xroot
    else if (rank[xroot] > rank[yroot]) // If the rank of xroot is greater than the rank of yroot
        parent[yroot] = xroot; // Then xroot becomes the parent of yroot
    else { // If the ranks are the same
        parent[yroot] = xroot; // Then yroot becomes the parent of xroot
        rank[xroot]++; // And the rank of xroot increases by 1
    }
}

int compare(const void* a, const void* b) {
    /* Comparison function for qsort
     * Compares the weights of two edges
     */
    struct Edge* a1 = (struct Edge*)a; // Casts a to a pointer to an Edge
    struct Edge* b1 = (struct Edge*)b; // Casts b to a pointer to an Edge
    return a1->w > b1->w; // Returns 1 if the weight of a is greater than the weight of b, 0 otherwise
}

int kruskalMST(struct Graph* graph) {
    /* Kruskal's algorithm for finding the minimum spanning tree of a graph
     * Returns the weight of the minimum spanning tree
     * using disjoint set data structure and qsort
     */
    int V = graph->V; // Number of vertices
    struct Edge result[V]; // Array of edges of the minimum spanning tree
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), compare); // Sorts the edges of the graph by weight using qsort(quicksort)

    int* parent = (int*) malloc(V * sizeof(int)); // Array of parents of the vertices
    int* rank = (int*) malloc(V * sizeof(int)); // Array of ranks of the vertices
    for (int v = 0; v < V; ++v) { // Initializes the arrays
        parent[v] = v; // The parent of each vertex is itself
        rank[v] = 0; // The rank of each vertex is 0
    }

    int e = 0; // Number of edges of the minimum spanning tree
    int i = 0; // Index of the edge being considered
    while (e < V - 1 && i < graph->E) { // While the minimum spanning tree has less than V - 1 edges and there are edges left
        struct Edge next_edge = graph->edge[i++]; // The next edge to be considered
        int x = find(parent, next_edge.u); // The set of the first vertex of the edge
        int y = find(parent, next_edge.v); // The set of the second vertex of the edge

        if (x != y) { // If the vertices are not in the same set
            result[e++] = next_edge; // The edge is added to the minimum spanning tree
            Union(parent, rank, x, y); // The sets of the vertices are united
        }
    }

    int minCost = 0; // Weight of the minimum spanning tree
    for (i = 0; i < e; ++i) // Calculates the weight of the minimum spanning tree
        minCost += result[i].w; // Adds the weight of the edge to the weight of the minimum spanning tree
    return minCost; // Returns the weight of the minimum spanning tree
}

int main() {
    /* Reads the input and calls the kruskalMST function
     * Prints the weight of the minimum spanning tree
     */
    int V, E; // Number of vertices and edges
    scanf("%d %d", &V, &E); // Reads the number of vertices and edges

    struct Graph* graph = createGraph(V, E); // Creates a graph with V vertices and E edges

    for (int i = 0; i < E; ++i) { // Reads the edges
        scanf("%d %d %d", &graph->edge[i].u, &graph->edge[i].v, &graph->edge[i].w); // Reads the vertices and weight of the edge
        graph->edge[i].u--; // Vertices are 0-indexed (0 <= u, v < V)
        graph->edge[i].v--; // Vertices are 0-indexed (the reason for the decrement)
    }

    printf("%d\n", kruskalMST(graph)); // Calls the kruskalMST function and prints the weight of the minimum spanning tree

    return 0; // Returns 0 to the operating system
}