// A01737959 Luis Antonio Bolaina Dominguez
// A01233745 Victor Abel Camacho Rodriguez

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <climits>
#include "Colonia.h"
#include "DisjointSets.h"

#define INF INT_MAX
#define MAX 100

using namespace std;

struct Graph {
    int V, E, cost;
    vector<Colonia> colonias;
    unordered_map<string, int> nombreToId;
    int matAdj[MAX][MAX];
    int next[MAX][MAX];
    
    vector<pair<int, pair<int, int>>> edges;
    vector<pair<int, int>> selectedEdges;

    Graph(int V, int E, vector<Colonia>& colonias, unordered_map<string, int>& nombreToId) {
        this->V = V;
        this->E = E;
        this->colonias = colonias;
        this->nombreToId = nombreToId;
        this->cost = 0;

        // Inicializar matrices
        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                if (i == j) {
                    matAdj[i][j] = 0;
                } else {
                    matAdj[i][j] = INF;
                }
                next[i][j] = -1;
            }
        }
    }

    // Agrega una arista al grafo
    // Complejidad: O(1)
    void addEdge(int u, int v, int w) {
        edges.push_back({w, {u, v}});

        if (w < matAdj[u][v]) {
            matAdj[u][v] = w;
            matAdj[v][u] = w;
        }
    }

    // Algoritmo de Kruskal modificado para MST
    // Considera conexiones pre-existentes
    // Complejidad: O(E log E)
    void kruskalMST(vector<pair<int, int>>& preExistentes) {
        cost = 0;
        selectedEdges.clear();
        sort(edges.begin(), edges.end());

        DisjointSets ds(V);
        vector<pair<int, pair<int, int>>> aristas_seleccionadas; // {costo, {u, v}}

        // Fase 1: Pre-procesar conexiones existentes
        for (int i = 0; i < preExistentes.size(); i++) {
            int u = preExistentes[i].first;
            int v = preExistentes[i].second;
            if (ds.find(u) != ds.find(v)) {
                ds.merge(u, v);
                selectedEdges.push_back(make_pair(u, v));
            }
        }

        // Fase 2: Kruskal normal
        for (int i = 0; i < edges.size(); i++) {
            int weight = edges[i].first;
            int u = edges[i].second.first;
            int v = edges[i].second.second;

            if (ds.find(u) != ds.find(v)) {
                cost += weight;
                selectedEdges.push_back(make_pair(u, v));
                aristas_seleccionadas.push_back({weight, {u, v}});
                ds.merge(u, v);

                if (selectedEdges.size() == V - 1) {
                    break;
                }
            }
        }

        // Imprimir resultados
        cout << "-------------------" << endl;
        cout << "1 – Cableado óptimo de nueva conexión." << endl;
        cout << endl;
        for (int i = 0; i < aristas_seleccionadas.size(); i++) {
            int peso = aristas_seleccionadas[i].first;
            int u = aristas_seleccionadas[i].second.first;
            int v = aristas_seleccionadas[i].second.second;
            cout << colonias[u].nombre << " - " << colonias[v].nombre << " " << peso << endl;
        }
        cout << endl;
        cout << "Costo Total: " << cost << endl;
    }

    // Inicializa la matriz next para Floyd-Warshall
    // Complejidad: O(V^2)
    void initFloyd() {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (matAdj[i][j] != INF && i != j) {
                    next[i][j] = j;
                } else {
                    next[i][j] = -1;
                }
            }
        }
    }

    // Algoritmo de Floyd-Warshall
    // Calcula caminos más cortos entre todos los pares de nodos
    // Complejidad: O(V^3)
    void floyd() {
        initFloyd();
        
        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    if (matAdj[i][k] != INF && matAdj[k][j] != INF 
                        && matAdj[i][j] > matAdj[i][k] + matAdj[k][j]) {
                        matAdj[i][j] = matAdj[i][k] + matAdj[k][j];
                        next[i][j] = next[i][k];
                    }
                }
            }
        }
    }

    // Reconstruye el camino más corto entre u y v
    // usando la matriz next de Floyd-Warshall
    // Complejidad: O(V)
    vector<int> nuevoCamino(int u, int v) {
        vector<int> path;
        if (next[u][v] == -1) {
            return path; // No hay camino
        }
        
        path.push_back(u);
        while (u != v) {
            u = next[u][v];
            path.push_back(u);
        }
        return path;
    }
};

#endif // GRAPH_H