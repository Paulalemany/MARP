//
//  Grafo.h
//
//  Implementación de grafos no dirigidos
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2020  Alberto Verdejo
//

#include <iostream>
#include <vector>
#include <iostream>
#include <stdexcept>

#include "Grafo.h"

using namespace std;

int main() {
    Grafo g(6);
    g.ponArista(0, 1);
    g.ponArista(2, 3);
    g.ponArista(4, 3);
    g.ponArista(1, 5);


    if (g.hayArista(3,4))
        cout << "Hay arista entre el 3 y el 4.\n"; // debe mostrar este mensaje
    else
        cout << "No hay arista entre el 3 y el 4.\n";
    if (g.hayArista(0,5))
        cout << "Hay arista entre el 0 y el 5.\n";
    else
        cout << "No hay arista entre el 0 y el 5.\n"; // debe mostrar este mensaje


    return 0;

}
