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
	int s;						// vértice origen 
	bool aciclico;

	void dfs(Grafo const& G, int v) {
		visit[v] = true;
		for (int w : G.ady(v)) {
			if (!visit[w]) {
				ant[w] = v;
				dfs(G, w);
			}
			else if (visit[w] && ant[v] != w) {	//Si ya esta visitado comprobamos si es un ciclo
				//Tenemos mas de un camino para llegar a un mismo vertice,
				//es decir, tenemos un ciclo
				aciclico = false;
				break;
			}
		}
	}

public:
	CaminosDFS(Grafo const& g, int s) : visit(g.V(), false),
		ant(g.V()), s(s), aciclico(true) {
		dfs(g, s);
	}

	// ¿hay camino del origen a v? 
	bool hayCamino(int v) const {
		return visit[v];
	}

	//Vemos si todos los vertices tienen un camino
	bool conexo() {
		bool c = true;

		int i = 0;
		while (i < visit.size() && c) {
			c = visit[i];
			i++;
		}
		return c;
	}

	bool Aciclico() const {
		return aciclico;
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
	int s = 0;

	CaminosDFS sol(grafo, s);

	// escribir la solución
	if (sol.Aciclico() && sol.conexo())
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
