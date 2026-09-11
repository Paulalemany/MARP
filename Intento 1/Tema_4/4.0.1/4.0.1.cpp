//
//  Grafo.h
//
//  Implementación de grafos no dirigidos
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2015-2020  Alberto Verdejo
//

#ifndef GRAFO_H_
#define GRAFO_H_

#include <iostream>
#include <vector>
#include <iostream>
#include <stdexcept>

using Adys = std::vector<int>;  // lista de adyacentes a un vértice

class Grafo {
private:
    int _V;  // número de vértices
    int _A;  // número de aristas
    std::vector<std::vector<bool>> _ady;  // matriz de adyacencia
public:

    /**
     * Crea un grafo con V vértices.
     */
    Grafo(int V) : _V(V), _A(0), _ady(_V, std::vector<bool>(_V, false)) {}

    /**
     * Devuelve el número de vértices del grafo.
     */
    int V() const { return _V; }

    /**
     * Devuelve el número de aristas del grafo.
     */
    int A() const { return _A; }

    /**
     * Añade la arista v-w al grafo.
     * @throws domain_error si algún vértice no existe
     */
    void ponArista(int v, int w) {
        if (v < 0 || v >= _V || w < 0 || w >= _V)
            throw std::domain_error("Vertice inexistente");
        ++_A;
        _ady[v][w] = _ady[w][v] = true;
    }

    bool hayArista(int v, int w) const {
        if (v < 0 || v >= _V || w < 0 || w >= _V)
            throw std::domain_error("Vertice inexistente");
        return _ady[v][w];
    }

    /**
     * Devuelve la lista de adyacencia de v.
     * @throws domain_error si v no existe
     */
    Adys ady(int v) const {
        if (v < 0 || v >= _V)
            throw std::domain_error("Vertice inexistente");
        Adys res;
        for (int i = 0; i < _V; ++i) {
            if (_ady[v][i])
                res.push_back(i);
        }
        return res;
    }

};

#endif /* GRAFO_H_ */

using namespace std;

int main() {
    Grafo g(7);
    g.ponArista(0, 1);
    g.ponArista(2, 3);
    g.ponArista(4, 3);
    g.ponArista(1, 5);
    g.ponArista(1, 6);

    if (g.hayArista(3, 4))
        cout << "Hay arista entre el 3 y el 4.\n"; // debe mostrar este mensaje
    else
        cout << "No hay arista entre el 3 y el 4.\n";
    if (g.hayArista(0, 5))
        cout << "Hay arista entre el 0 y el 5.\n";
    else
        cout << "No hay arista entre el 0 y el 5.\n"; // debe mostrar este mensaje

    cout << "Los adyacentes al 1 son:";
    for (int v : g.ady(1)) // debe mostrar  0 5 6
        cout << ' ' << v;
    cout << '\n';

    return 0;
}
