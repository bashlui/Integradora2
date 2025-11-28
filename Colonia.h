// A01737959 Luis Antonio Bolaina Dominguez
// A01233745 Victor Abel Camacho Rodriguez

#ifndef COLONIA_H
#define COLONIA_H

#include <string>
#include "Point.h"

using namespace std;

struct Colonia {
    string nombre;
    Point coordenadas;
    bool esCentral;
    int coloniaId;
    
    Colonia() {
        nombre = "";
        coordenadas = Point(0, 0);
        esCentral = false;
        coloniaId = -1;
    }

    Colonia(string nombre, Point coordenadas, bool esCentral, int coloniaId) {
        this->nombre = nombre;
        this->coordenadas = coordenadas;
        this->esCentral = esCentral;
        this->coloniaId = coloniaId;
    }
};

#endif // COLONIA_H