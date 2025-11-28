// A01737959 Luis Antonio Bolaina Dominguez
// A01233745 Victor Abel Camacho Rodriguez

#ifndef DISJOINT_SETS_H
#define DISJOINT_SETS_H

// Estructura de conjuntos disjuntos (Union-Find)
// con path compression y union by rank
struct DisjointSets {
    int *parent, *rank;
    int n;
    
    DisjointSets(int n) {
        this->n = n;
        parent = new int[n + 1];
        rank = new int[n + 1];
        for (int i = 0; i <= n; i++) {
            rank[i] = 0;
            parent[i] = i;
        }
    }

    // Encuentra el representante del conjunto
    // Complejidad: O(1)
    int find(int u) {
        if (u != parent[u]) {
            parent[u] = find(parent[u]);  // Path compression
        }
        return parent[u];
    }

    // Une dos conjuntos
    // Complejidad: O(1)
    void merge(int x, int y) {
        x = find(x);
        y = find(y);
        
        if (rank[x] > rank[y]) {
            parent[y] = x;
        } else {
            parent[x] = y;
        }
        
        if (rank[x] == rank[y]) {
            rank[y]++;
        }
    }
};

#endif // DISJOINT_SETS_H