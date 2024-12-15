#include<stdio.h>

// Function to perform Dijkstra's Algorithm
void dij(int n, int cost[10][10], int source, int dest, int d[], int p[]) {
    int s[10], min, u, v;
    for (int i = 0; i < n; i++) { 
        d[i] = cost[source][i]; // Initialize distances from source
        s[i] = 0;              // Mark all nodes as unvisited
        p[i] = source;         // Initialize parent array
    }
    s[source] = 1;             // Mark source as visited

    for (int i = 1; i < n; i++) {
        min = 999;
        u = -1;

        // Find the unvisited node with the smallest distance
        for (int j = 0; j < n; j++) {
            if (!s[j] && d[j] < min) {
                min = d[j];
                u = j;
            }
        }

        if (u == -1) return; // No more reachable nodes
        s[u] = 1;           // Mark the node as visited

        if (u == dest) return; // Stop if we reach the destination

        // Update distances of neighbors
        for (v = 0; v < n; v++) {
            if (!s[v] && d[u] + cost[u][v] < d[v]) {
                d[v] = d[u] + cost[u][v];
                p[v] = u;
            }
        }
    }
}

// Function to print the shortest path and its cost
void print_path(int source, int destination, int d[], int p[]) {
    if (d[destination] == 999) {
        printf("%d is not reachable from %d\n", destination, source);
        return;
    }

    int i = destination;
    printf("Path: ");
    while (i != source) {
        printf("%d <- ", i);
        i = p[i];
    }
    printf("%d = %d\n", source, d[destination]);
}

// Main function
int main() {
    int cost[10][10], n, d[10], p[10], source;

    printf("Enter the number of nodes in the network: ");
    scanf("%d", &n);

    printf("Enter the cost between nodes (use 999 for no connection):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
        }
    }

    printf("Enter the source node: ");
    scanf("%d", &source);

    // Find shortest path from the source to all other nodes
    for (int dest = 0; dest < n; dest++) {
        if (source != dest) {
            dij(n, cost, source, dest, d, p);
            print_path(source, dest, d, p);
        }
    }

    return 0;
}
