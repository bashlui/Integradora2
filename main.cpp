// A01737959 Luis Antonio Bolaina Dominguez
// A01233745 Victor Abel Camacho Rodriguez

#include <iostream>
#include <vector>
#include <unordered_map>
#include "Point.h"
#include "Colonia.h"
#include "Graph.h"
#include "TSP.h"
#include "ClosestPair.h"

using namespace std;

int main() {
    int n, m, k, q, x, y, costo;
    string colonia, colonia1, colonia2;
    bool central;
    cin >> n >> m >> k >> q;

    vector<Colonia> colonias(n);
    unordered_map<string, int> nombreToId;
    vector<int> centrales, noCentrales;

    vector<pair<string, string>> cableadoNuevo;
    vector<pair<string, Point>> nuevasColonias;

    if ((2 <= n && n <= 30) && (1 <= m && m <= 400) && (0 <= k && k <= m) && (1 <= q && q <= 10)) {
        // 1. Leer colonias
        for (int i = 0; i < n; i++) {
            cin >> colonia >> x >> y >> central;
            Point coord(x, y);
            colonias[i] = Colonia(colonia, coord, central, i);
            nombreToId[colonia] = i;
            
            if (central == 1) {
                centrales.push_back(i);
            } else {
                noCentrales.push_back(i);
            }
        }

        // 2. Crear grafo y leer conexiones
        Graph grafo(n, m, colonias, nombreToId);
        for (int i = 0; i < m; i++) {
            cin >> colonia1 >> colonia2 >> costo;
            int u = nombreToId[colonia1];
            int v = nombreToId[colonia2];
            grafo.addEdge(u, v, costo);
        }

        // 3. Leer cableado nuevo
        vector<pair<int, int>> cableadoNuevoIds;
        for (int i = 0; i < k; i++) {
            cin >> colonia1 >> colonia2;
            int u = nombreToId[colonia1];
            int v = nombreToId[colonia2];
            cableadoNuevoIds.push_back({u, v});
        }

        // 4. Leer nuevas colonias
        for (int i = 0; i < q; i++) {
            cin >> colonia >> x >> y;
            Point coord(x, y);
            nuevasColonias.push_back({colonia, coord});
        }
        
        grafo.kruskalMST(cableadoNuevoIds);
        
        grafo.floyd();
        
        // PUNTO 2: TSP (DESPUÉS de Floyd)
        int cantBB = 0;
        pair<vector<int>, int> resultadoTSP = TSPBB(noCentrales, grafo.matAdj, n, cantBB);
        vector<int> rutaTSP = resultadoTSP.first;
        int costoTSP = resultadoTSP.second;

        cout << endl;
        cout << "-------------------" << endl;
        cout << "2 - La ruta óptima." << endl;
        cout << endl;

        // Construir la ruta completa con todos los nodos intermedios
        if (rutaTSP.size() > 0) {
            vector<int> rutaCompleta;
            
            for (int i = 0; i < rutaTSP.size(); i++) {
                int origen = rutaTSP[i];
                int destino = (i == rutaTSP.size() - 1) ? rutaTSP[0] : rutaTSP[i + 1];
                
                // Reconstruir el camino entre origen y destino
                vector<int> caminoSegmento = grafo.nuevoCamino(origen, destino);
                
                // Agregar el camino (sin duplicar el último nodo)
                for (int j = 0; j < caminoSegmento.size(); j++) {
                    // Solo agregar si no es el último nodo O si es el último segmento
                    if (j < caminoSegmento.size() - 1 || i == rutaTSP.size() - 1) {
                        rutaCompleta.push_back(caminoSegmento[j]);
                    }
                }
            }
            
            // Imprimir la ruta completa
            for (int i = 0; i < rutaCompleta.size(); i++) {
                cout << colonias[rutaCompleta[i]].nombre;
                if (i < rutaCompleta.size() - 1) {
                    cout << " - ";
                }
            }
            cout << endl << endl;
        } else {
            cout << "No se encontró ruta." << endl << endl;
        }

        cout << "La Ruta Óptima tiene un costo total de: " << costoTSP << endl;
        
        // PUNTO 3: Mostrar caminos entre centrales
        cout << endl;
        cout << "-------------------" << endl;
        cout << "3 - Caminos más cortos entre centrales." << endl;
        cout << endl;
        for (int i = 0; i < centrales.size(); i++) {
            for (int j = i + 1; j < centrales.size(); j++) {
                int u = centrales[i];
                int v = centrales[j];
                vector<int> camino = grafo.nuevoCamino(u, v);
                
                for (int k = 0; k < camino.size(); k++) {
                    cout << colonias[camino[k]].nombre;
                    if (k < camino.size() - 1) {
                        cout << " - ";
                    }
                }
                cout << " (" << grafo.matAdj[u][v] << ")" << endl;
            }
        }
        
        // PUNTO 4: Encontrar colonias más cercanas
        encontrarVecinosCercanos(colonias, nuevasColonias);
    }
    
    return 0;
}