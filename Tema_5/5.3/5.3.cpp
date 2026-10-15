/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <deque>
#include <unordered_set>

using namespace std;

#include "Digrafo.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class OrdenTopologico {
public: 
	// g es DAG 
	OrdenTopologico(Digrafo const& g) : visit(g.V(), false) {
		for (int v = 0; v < g.V(); ++v) 
			if (!visit[v]) 
				dfs(g, v); 
	} 
	
	// devuelve la ordenación topológica 
	std::deque<int> const& orden() const { 
		return _orden; 
	}

	bool const aciclico() {
		return aci;
	}

private: 
	std::vector<bool> visit; 
	std::deque<int> _orden;
	unordered_set<int> cola;
	bool aci = true;
	
	// ordenación topológica 
	void dfs(Digrafo const& g, int v) { 
		visit[v] = true; 
		cola.insert(v);
		for (int w : g.ady(v)) {
			
			if (!visit[w]) {
				dfs(g, w); 
			}

			//Necesitamos saber si el grafo tiene ciclos
			if (cola.count(w) > 0) {
				aci = false;
				break;
			}

		}
		_orden.push_front(v);
		cola.erase(v);
	} 
};

void resuelveCaso() {
	// leer los datos de la entrada

	int N, M;
	cin >> N >> M;

	int A, B;
	Digrafo tareas(N);
	for (int i = 0; i < M; i++) {
		cin >> A >> B;
		tareas.ponArista(A - 1, B - 1);
	}

	// resolver el caso posiblemente llamando a otras funciones
	OrdenTopologico orden(tareas);

	// escribir la solución

	if (orden.aciclico()) {

		deque<int> sol = orden.orden();

		for (int i = 0; i < sol.size(); i++) {
			cout << sol[i] + 1 << " ";
		}
	}
	else
		cout << "Imposible";


	cout << '\n';
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
