
/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "Grafo.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class Bipartito {
private:

	vector<pair<bool,int>> visit;	//Vector de nodos visitados (Guarda el "color" del nodo (1/-1 el 0 es no visitado)
	vector<int> ant;	//guarda el último vértice antes de llegar a v
	int s;				//vértice de origen
	int col = -1;		//Color del vértice
	bool bipartito = true;

public:

	Bipartito(Grafo const& g, int s) : visit(g.V(), {false, 0}),
		ant(g.V()), s(s) {

		//100% tiene una componente conexa
		dfs(g, s, col);
		int con = 0;
		conexo(g, con);

		while (con < g.V() && bipartito) {
			dfs(g, con, col);
			conexo(g, con);
		}

		//Tenemos que comprobar que no haya ningún camino cíclico
		if (bipartito) cout << "SI\n";
		else cout << "NO\n";

	}

	//Comprobamos si el grafo es conexo
	void dfs(Grafo const& g, int v, int c) {	//Recorrido en profundidad
		visit[v].first = true;
		visit[v].second = c;
		
		c *= -1;	//Cambiamos el tono

		//Recorremos los adyacentes del nodo
		for (int w : g.ady(v)) {	//Hacerlo así le da a w el valor de la componente en el vector y no su indice
			if (!visit[w].first) {	//Si no hemos visitado el nodo
				ant[w] = v;
				dfs(g, w, c);	//Vemos los adyacentes a ese nuevo nodo
			}
			else {	//Si se ha visitado comprobar que tienen el color correcto
				bipartito = visit[w].second == c;
			}
			if (!bipartito) return;
		}

	}

	bool conexo(Grafo const& g, int& i) {
		while (i < visit.size()) {

			if (visit[i].first == false) return false;
			i++;
		}
		return true;	//Si llega al final del bucle es que se han visitado todos en una sola búsqueda
	}
};

bool resuelveCaso() {
	// leer los datos de la entrada
	int V, A;
	cin >> V >> A;

	if (!std::cin)  // fin de la entrada
		return false;

	Grafo grafo(V);
	int ini, fin;

	//Creamos el grafo
	for (int i = 0; i < A; i++) {
		cin >> ini >> fin;
		grafo.ponArista(ini, fin);
	}

	Bipartito al(grafo, 0);

	return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	if (!in.is_open())
		std::cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	std::cout << "Pulsa Intro para salir..." << std::flush;
	std::cin.get();
#endif
	return 0;
}
