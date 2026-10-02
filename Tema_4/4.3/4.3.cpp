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

class MaximaCompConexa {
private: 
	vector<bool> visit;		// visit[v] = se ha visitado el vértice v? 
	int maxim;				// tamaño de la componente mayor 

	int dfs(Grafo const& g, int v) { 
		visit[v] = true; 
		int tam = 1; 
		for (int w : g.ady(v)) { 
			if (!visit[w]) 
				tam += dfs(g, w); 
		} 
		return tam; 
	} 

public: 

	MaximaCompConexa(Grafo const& g) : 
		visit(g.V(), false), maxim(0) {
		for (int v = 0; v < g.V(); ++v) {
			if (!visit[v]) { 
				// se recorre una nueva componente conexa 
				int tam = dfs(g, v); 
				maxim = max(maxim, tam); 
			} 
		} 
	} 
	
	// tamaño máximo de una componente conexa 
	int maximo() const { 
		return maxim; 
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
		grafo.ponArista(v1 - 1, v2 - 1);
	}

	MaximaCompConexa mcc(grafo); 
	cout << mcc.maximo() << '\n';

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
