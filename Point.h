// A01737959 Luis Antonio Bolaina Dominguez
// A01233745 Victor Abel Camacho Rodriguez

#ifndef POINT_H
#define POINT_H

#include <cmath>

struct Point {
    float x, y;
    
    Point() {
        x = y = 0;
    }
    
    Point(float x, float y) {
        this->x = x;
        this->y = y;
    }
};

// Calcula la distancia euclidiana entre dos puntos
// Complejidad: O(1)
float dist(Point &p1, Point &p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// Comparadores para ordenamiento
bool compareY(const Point &p1, const Point &p2) {
    return (p1.y < p2.y);
}

bool compareX(const Point &p1, const Point &p2) {
    return (p1.x < p2.x);
}

#endif // POINT_H