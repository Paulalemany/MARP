/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

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

class CaminosDFS {
private:
	std::vector<bool> visit;	// visit[v] = ¿hay camino de s a v? 
	std::vector<int> ant;		// ant[v] = último vértice antes de llegar a v 
	std::vector<int> color;	
	bool bi;

	void dfs(Grafo const& G, int v, int c) {
		visit[v] = true;
		color[v] = c;
		for (int w : G.ady(v)) {

			// Todos sus adyacentes deben ser del color contrario
			if (color[w] == c) {
				bi = false;
				break;
			}

			if (!visit[w]) {
				ant[w] = v;
				dfs(G, w, c * -1);
			}
		}
	}

public:
	CaminosDFS(Grafo const& g) : visit(g.V(), false),
		ant(g.V()), color(g.V(), 0), bi(true) {

		// Queremos hacerlo con todos los vertices del grafo
		for (int i = 0; i < g.V(); i++) {
			if (!visit[i])
				dfs(g, i, 1);
		}
	}

	// ¿hay camino del origen a v? 
	bool hayCamino(int v) const {
		return visit[v];
	}

	bool bipartito() const {
		return bi;
	}
};

void resuelveCaso() {
	// leer los datos de la entrada

	int V, A;
	cin >> V >> A;

	Grafo grafo(V);

	int v1, v2;
	for (int i = 0; i < A; i++) {

		cin >> v1 >> v2;
		grafo.ponArista(v1, v2);
	}

	// resolver el caso posiblemente llamando a otras funciones

	CaminosDFS sol(grafo);

	// escribir la solución
	
	if (sol.bipartito())
		cout << "SI\n";
	else
		cout << "NO\n";

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

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	// para dejar todo como estaba al principio y parar antes de salir
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	std::cout << "Pulsa Intro para salir..." << std::flush;
	std::cin.get();
#endif

	return 0;
}
