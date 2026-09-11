
/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <deque>

using namespace std;

#include "Grafo.h"

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class Bipartito {
private:

	vector<bool> visit;	//Vector de nodos visitados
	vector<int> ant;	//guarda el último vértice antes de llegar a v
	int s;				//vértice de origen
	bool ciclo = false;

	using Camino = std::deque<int>;

public:

	Bipartito(Grafo const& g, int s) : visit(g.V(), false),
		ant(g.V()), s(s) {

		//Tenemos que comprobar que no haya ningún camino cíclico
		if (conexo(g) && !ciclo) cout << "SI\n";
		else cout << "NO\n";

	}

	//Comprobamos si el grafo es conexo
	void dfs(Grafo const& g, int v) {	//Recorrido en profundidad
		visit[v] = true;

		//Recorremos los adyacentes del nodo
		for (int w : g.ady(v)) {	//Hacerlo así le da a w el valor de la componente en el vector y no su indice
			if (!visit[w]) {	//Si no hemos visitado el nodo
				ant[w] = v;
				dfs(g, w);	//Vemos los adyacentes a ese nuevo nodo
			}
			else if (ant[v] != w && w != s){	//Hemos encontrado un ciclo
				//Si volvemos a un nodo ya visitado y no es su padre directo
				//(Es decir no acabamos de venir de ahí) hay un ciclo
				ciclo = true;
			}
		}

	}

	bool conexo(Grafo const& g) {

		dfs(g, s);

		int i = 0;
		while (i < visit.size()) {

			if (visit[i] == false) return false;
			i++;
		}
		return true;	//Si llega al final del bucle es que se han visitado todos en una sola búsqueda
	}

	bool hayCamino(int v) const {
		return visit[v];	//Si se ha visitado es que hay un camino a el
	}

	Camino camino(int v) const {

		//devuelve el camino desde el origen a v
		if (!hayCamino(v))
			throw std::domain_error("No existe camino");
		Camino cam;

		//recuperamos el recorrido hecho
		for (int x = v; x != s; x = ant[x]) 
			cam.push_front(x);
		cam.push_front(s);
		return cam;
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

	Bipartito al(grafo, 0);	//Que empiece en el primer nodo (Tener cuidado con los grafos vacíos

	//Escribimos la solución
	//Si con esa llamada se han visitado todos los nodos es que es un árbol libre
	/*if (al.sol()) cout << "SI\n";
	else cout << "NO\n";*/

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
