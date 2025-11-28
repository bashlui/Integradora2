// A01737959 Luis Antonio Bolaina Dominguez
// A01233745 Victor Abel Camacho Rodriguez

#ifndef CLOSEST_PAIR_H
#define CLOSEST_PAIR_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "Point.h"
#include "Colonia.h"

#define INF INT_MAX

using namespace std;

// Encuentra el par más cercano por fuerza bruta
// Complejidad: O(n^2)
float bruteForce(vector<Point> &P, int ini, int fin) {
    float min_aux = INF;
    for (int i = ini; i < fin; i++) {
        for (int j = i + 1; j <= fin; j++) {
            min_aux = min(min_aux, dist(P[i], P[j]));
        }
    }
    return min_aux;
}

// Encuentra el par más cercano en la franja
// Complejidad: O(n^2) peor caso, O(n) caso promedio
float stripClosest(vector<Point> &strip, float dMenor) {
    float min_Strip = INF;
    sort(strip.begin(), strip.end(), compareY);
    
    for (int i = 0; i < strip.size() - 1; i++) {
        for (int j = i + 1; j <= strip.size() - 1; j++) {
            min_Strip = min(min_Strip, dist(strip[i], strip[j]));
        }
    }
    return min_Strip;
}

// Algoritmo recursivo de divide y conquista
// Complejidad: O(n log^2 n)
float closest_Helper(vector<Point> &P, int ini, int fin) {
    if (fin - ini < 3) {
        return bruteForce(P, ini, fin);
    }
    
    int mid = (fin - ini) / 2;
    Point midPoint = P[mid];
    
    float dl = closest_Helper(P, ini, mid);
    float dr = closest_Helper(P, mid + 1, fin);
    float dMenor = min(dl, dr);
    
    vector<Point> strip;
    for (int i = ini; i <= fin; i++) {
        if (abs(P[i].x - midPoint.x) < dMenor) {
            strip.push_back(P[i]);
        }
    }
    
    float ds = stripClosest(strip, dMenor);
    return ds;
}

// Encuentra la colonia más cercana a un punto dado
// Complejidad: O(n)
void encontrarVecinosCercanos(vector<Colonia>& colonias, vector<pair<string, Point>>& nuevasColonias) {
    cout << endl;
    cout << "-------------------" << endl;
    cout << "4 - Conexión de nuevas colonias." << endl;
    cout << endl;
    
    for (int i = 0; i < nuevasColonias.size(); i++) {
        string nombreNueva = nuevasColonias[i].first;
        Point coordNueva = nuevasColonias[i].second;
        
        float distMinima = INF;
        string coloniaCercana = "";
        
        for (int j = 0; j < colonias.size(); j++) {
            float d = dist(coordNueva, colonias[j].coordenadas);
            if (d < distMinima) {
                distMinima = d;
                coloniaCercana = colonias[j].nombre;
            }
        }
        
        cout << nombreNueva << " debe conectarse con " << coloniaCercana << endl;
    }
    
    cout << endl;
    cout << "-------------------" << endl;
}

#endif // CLOSEST_PAIR_H