/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <deque>

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

class Amigos {
private:
	vector<bool> visit;				//Vector de nodos visitados
	vector<int> ant;				//guarda el último vértice antes de llegar a v
	int s;							//vértice de origen
	int conexa = 0;					//Nos guardamos cuantos elementos tiene la mayor componente conexa
	using Camino = std::deque<int>;	//Usamos caminos y nos guardamos el más largo

public:
	Amigos(Grafo const& g, int s) : visit(g.V(), {false}),
		ant(g.V()), s(s) {

		//Elegir la mayor componente conexa
		int con = 0, ini = s;
		while (ini < visit.size()) {	//Mientras no se hayan visitados todos los nodos

			dfs(g, ini, con);
			ini += con;	//Actualizamos por donde vamos
			if (con > conexa) conexa = con;	//Guardamos en conexa el numero de nodos de la componente más larga
			con = 0;
		}

		cout << conexa << '\n';
	}

	//Comprobamos si el grafo es conexo
	void dfs(Grafo const& g, int v, int& con) {	//Recorrido en profundidad
		visit[v] = true;
		con++; 

		//Recorremos los adyacentes del nodo
		for (int w : g.ady(v)) {	//Hacerlo así le da a w el valor de la componente en el vector y no su indice
			if (!visit[w]) {	//Si no hemos visitado el nodo
				ant[w] = v;
				dfs(g, w, con);	//Vemos los adyacentes a ese nuevo nodo
			}
		}

	}
};

void resuelveCaso() {

	// leer los datos de la entrada
	int N, M;

	cin >> N >> M;

	Grafo g(N);
	int d1, d2;
	for (int i = 0; i < M; i++) {

		cin >> d1 >> d2;
		g.ponArista(d1 - 1, d2 - 1);	//En los datos los grafos empiezan en 1 en vez de en 0
	}

	Amigos(g, 0);

	// escribir la solución
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
