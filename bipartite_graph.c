#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_VERTICES 100 // Maximum number of vertices

// Function to implement BFS
bool BFS(int G[MAX_VERTICES][MAX_VERTICES], int V, int s, int color[]) {
    int prev[MAX_VERTICES]; // Previous vertex in the BFS traversal
    int d[MAX_VERTICES]; // Distance from the source vertex
    int queue[MAX_VERTICES]; // Queue for BFS traversal
    int front = 0, rear = 0; // Front and rear pointers for the queue

    // Initialize prev and d arrays
    for (int u = 0; u < V; u++) {
        prev[u] = -1; // -1 represents NIL
        d[u] = INT_MAX; // INT_MAX represents infinity
    }

    color[s] = 0; // Set the color of the source vertex as 0 (first group)
    d[s] = 0;
    prev[s] = -1;
    queue[rear++] = s; // Enqueue the source vertex

    while (front != rear) {
        int u = queue[front++]; // Dequeue a vertex from the queue

        for (int v = 0; v < V; v++) {
            if (G[u][v]) {
                if (color[v] == -1) {
                    color[v] = 1 - color[u]; // Assign the opposite color to v
                    d[v] = d[u] + 1;
                    prev[v] = u;
                    queue[rear++] = v; // Enqueue v
                } else if (color[v] == color[u]) {
                    return false; // Not a bipartite graph
                }
            }
        }
    }

    return true; // It's a bipartite graph
}

int main() {
    int V = 5; // Number of vertices
    int G[MAX_VERTICES][MAX_VERTICES] = {
        {0, 1, 1, 0, 0}, // Adjacency matrix
        {1, 0, 0, 1, 1},
        {1, 0, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0}
    };

    int color[MAX_VERTICES]; // Color array to store the group of each vertex

    // Initialize color array
    for (int i = 0; i < V; i++) {
        color[i] = -1; // -1 represents unvisited
    }

    int source = 0; // Source vertex

    if (BFS(G, V, source, color)) {
        printf("It's a bipartite graph!\n");

        // Print the groups of vertices
        printf("Groups of vertices:\n");
        for (int i = 0; i < V; i++) {
            printf("Vertex %d: Group %d\n", i, color[i]);
        }
    } else {
        printf("It's not a bipartite graph!\n");
    }

    return 0;
}

