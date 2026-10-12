/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>

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
	int guardias = 0;

	void dfs(Grafo const& G, int v, int c, vector<int>&conj) {
		visit[v] = true;
		color[v] = c;
		conj.push_back(v);
		for (int w : G.ady(v)) {

			// Todos sus adyacentes deben ser del color contrario
			if (color[w] == c) {
				bi = false;
				break;
			}

			if (!visit[w]) {
				ant[w] = v;
				dfs(G, w, c * -1, conj);
			}
		}
	}

	int conjuntoMenor(vector<int>conj) {
		int A = 0;
		for (int i = 0; i < conj.size(); i++)
			if (color[conj[i]] == 1)
				A++;

		return min(A, (int)conj.size() - A);
	}

public:
	CaminosDFS(Grafo const& g) : visit(g.V(), false),
		ant(g.V()), color(g.V(), 0), bi(true) {

		// Queremos hacerlo con todos los vertices del grafo
		for (int i = 0; i < g.V(); i++) {
			if (!visit[i]) {	//Se recorre nueva componente conexa
				vector<int>conj;
				dfs(g, i, 1, conj);
				guardias += conjuntoMenor(conj);
			}
		}
	}

	// ¿hay camino del origen a v? 
	bool hayCamino(int v) const {
		return visit[v];
	}

	bool bipartito() const {
		return bi;
	}

	int minGuardias() {
		return guardias;
	}

};


void resuelveCaso() {
	// leer los datos de la entrada
	int N, C;

	cin >> N >> C;

	Grafo ciudad(N);
	int n1, n2;

	for (int i = 0; i < C; i++) {
		cin >> n1 >> n2;
		ciudad.ponArista(n1 - 1, n2 - 1);
	}

	// resolver el caso posiblemente llamando a otras funciones
	CaminosDFS guardias(ciudad);

	// escribir la solución
	if (guardias.bipartito())
		cout << guardias.minGuardias() << '\n';
	else
		cout << "IMPOSIBLE\n";
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
