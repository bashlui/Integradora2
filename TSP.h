// A01737959 Luis Antonio Bolaina Dominguez
// A01233745 Victor Abel Camacho Rodriguez

#ifndef TSP_H
#define TSP_H

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include "Colonia.h"

#define INF INT_MAX
#define MAX 100

using namespace std;

// Nodo para el algoritmo Branch & Bound de TSP
struct TSPNode {
    int niv;           // Nivel (nodos visitados)
    int ca;            // Costo Acumulado
    int cp;            // Costo Posible (cota inferior)
    int actual;        // Nodo actual
    vector<bool> visitados;
    vector<int> camino;
    
    TSPNode(int niv, int ca, int cp, int actual) {
        this->niv = niv;
        this->ca = ca;
        this->cp = cp;
        this->actual = actual;
    }
    
    // Operador para priority_queue (menor cp = mayor prioridad)
    bool operator<(const TSPNode &otro) const {
        return this->cp > otro.cp;
    }
};

// Calcula la cota inferior para Branch & Bound
// Suma las aristas mínimas de cada nodo no visitado
// Complejidad: O(n^2)
int calculaBound(vector<bool> &visitados, int caAux, int matAdj[MAX][MAX], 
                 int n, vector<int> &nodos) {
    int bound = caAux;
    
    for (int i = 0; i < nodos.size(); i++) {
        int idx = nodos[i];
        if (!visitados[idx]) {
            int minEdge = INF;
            
            for (int j = 0; j < nodos.size(); j++) {
                int idx2 = nodos[j];
                if (idx != idx2 && matAdj[idx][idx2] < minEdge && 
                    matAdj[idx][idx2] != INF) {
                    minEdge = matAdj[idx][idx2];
                }
            }
            
            if (minEdge != INF) {
                bound += minEdge;
            }
        }
    }
    
    return bound;
}

// Algoritmo Branch & Bound para TSP
// Encuentra el camino más corto que visita todos los nodos y regresa al origen
// Complejidad: O(2^n) en el peor caso, con poda efectiva
pair<vector<int>, int> TSPBB(vector<int> &nodos, int matAdj[MAX][MAX], int n, int &cantBB) {
    priority_queue<TSPNode> pq;
    int costoOptimo = INF;
    vector<int> caminoOptimo;
    int inicio = nodos[0];
    
    // Crear nodo inicial
    vector<bool> visitadosInicio(n, false);
    visitadosInicio[inicio] = true;
    vector<int> caminoInicio;
    caminoInicio.push_back(inicio);
    
    int cpInicial = calculaBound(visitadosInicio, 0, matAdj, n, nodos);
    TSPNode arranque(0, 0, cpInicial, inicio);
    arranque.visitados = visitadosInicio;
    arranque.camino = caminoInicio;
    
    cantBB++;
    pq.push(arranque);
    
    while (!pq.empty()) {
        TSPNode otro = pq.top();
        pq.pop();
        
        // Poda: si el costo posible es peor que el óptimo, descartar
        if (otro.cp >= costoOptimo) {
            continue;
        }
        
        // Si visitamos todos los nodos
        if (otro.niv == nodos.size() - 1) {
            // Intentar cerrar el ciclo
            if (matAdj[otro.actual][inicio] != INF) {
                int costoTotal = otro.ca + matAdj[otro.actual][inicio];
                if (costoTotal < costoOptimo) {
                    costoOptimo = costoTotal;
                    caminoOptimo = otro.camino;
                }
            }
            continue;
        }
        
        // Expandir: probar ir a cada nodo no visitado
        for (int i = 0; i < nodos.size(); i++) {
            int siguiente = nodos[i];
            
            if (otro.visitados[siguiente]) {
                continue;
            }
            
            if (matAdj[otro.actual][siguiente] == INF) {
                continue;
            }
            
            cantBB++;
            
            // Crear nuevo nodo hijo
            int nuevoCA = otro.ca + matAdj[otro.actual][siguiente];
            vector<bool> nuevosVisitados = otro.visitados;
            nuevosVisitados[siguiente] = true;
            
            int nuevoCP = calculaBound(nuevosVisitados, nuevoCA, matAdj, n, nodos);
            
            // Solo agregar si puede mejorar
            if (nuevoCP < costoOptimo) {
                TSPNode hijo(otro.niv + 1, nuevoCA, nuevoCP, siguiente);
                hijo.visitados = nuevosVisitados;
                hijo.camino = otro.camino;
                hijo.camino.push_back(siguiente);
                pq.push(hijo);
            }
        }
    }
    
    return make_pair(caminoOptimo, costoOptimo);
}

#endif // TSP_H