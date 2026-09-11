
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <deque>

using namespace std;

#include "Digrafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class OrdenacionTopologica {
private:

	vector<bool> visit;		//vector de vértices visitados
	vector<bool> pila;		//vector de vértices por comprobar adyacentes
	vector<int> ant;		//vector que marca el vértice anterior
	bool ciclico;			//booleano para indicar si un digrafo tiene un ciclo
	deque<int> postOrdern;	//Guardamos el recorrido en postOrden

	void dfs(Digrafo& g, int v) {
		visit[v] = true;
		pila[v] = true;
		for (int w : g.ady(v)) {
			if (ciclico) return;	//Si hay un ciclo es imposible ordenarse topológicamente
			if (!visit[w]) {		//Continuamos el recorrido en profundidad
				ant[w] = v;
				dfs(g, w);
			}
			else if (pila[w])	//Hay un ciclo
				ciclico = true;
		}
		pila[v] = false;
		postOrdern.push_front(v);
	}

public:

	OrdenacionTopologica(Digrafo& g) : visit(g.V(), false), pila(g.V(), false),
		ant(g.V()), ciclico(false) {

		for (int i = 0; i < g.V(); i++) {
			if(!visit[i]) 
				dfs(g, i);
		}
		

		if (ciclico) cout << "Imposible";
		else {
			for (int i : postOrdern) {
				cout << i + 1 << " ";
				postOrdern.pop_front();
			}
		}
	}

};

bool resuelveCaso() {
	// leer los datos de la entrada
	int T, D;

	cin >> T >> D;

	if (!std::cin)  // fin de la entrada
		return false;

	Digrafo tareas(T);
	int d1, d2;

	for (int i = 0; i < D; i++) {
		cin >> d1 >> d2;
		tareas.ponArista(d1 - 1, d2 - 1);
	}

	OrdenacionTopologica orden(tareas);

	cout << '\n';

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
