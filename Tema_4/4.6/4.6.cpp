
/*@ <authors>
 *
 * Paulda, Alemany Rodríguez (MARP01).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

#include "Grafo.h"

using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class Amiguisimo {
private:
	vector<bool> visit;	//Vector de nodos visitados
	vector<int> ant;	//guarda el último vértice antes de llegar a v
	vector<int> ami;	//Vector que guarda el tamaño de la componente conexa del número
	int s;				//Vertice de origen

public:
	Amiguisimo(Grafo& g, int s) : visit(g.V(), false), ant(g.V()),
		ami(g.V()), s(s) {

		int nodos = 0;
		int ini = 0;
		while (nodos < g.V()) {

			int amig = 0;
			dfs(g, primerSinVisita(ini), amig);
			ini = primerSinVisita(ini);
			nodos += amig;
		}

		noticias(g);

	}

	//Vemos cada componente conexa
	void dfs(Grafo const& g, int v, int& a) {	//Recorrido en profundidad
		visit[v] = true;
		a++;

		//Recorremos los adyacentes del nodo
		for (int w : g.ady(v)) {	//Hacerlo así le da a w el valor de la componente en el vector y no su indice
			if (!visit[w]) {	//Si no hemos visitado el nodo
				ant[w] = v;
				dfs(g, w, a);	//Vemos los adyacentes a ese nuevo nodo
			}
		}
		ami[v] = a;
	}

	void noticias(Grafo& g) {

		for (int i = 0; i < g.V(); i++) {
			cout << ami[i] << " ";
		}

		cout << "\n";
	}

	int primerSinVisita(int ini) {
		int i = ini;
		while (i < visit.size() && visit[i]) i++;
		return i;
	}
};

bool resuelveCaso() {
	
	int N, M;

	cin >> N >> M;

	if (!std::cin)  // fin de la entrada
		return false;

	Grafo g(N);

	//Lectura de los datos
	for (int i = 0; i < M; i++) {
		int inter;
		cin >> inter;
		vector<int> datos;
		for (int j = 0; j < inter; j++) {	//Recorremos los integrantes del grupo
			int d;
			cin >> d;
			datos.push_back(d);
		}

		if (datos.size() > 0) {

			//Creamos las conexiones
			for (int j = 0; j < datos.size() - 1; j++) {
				for (int x = j + 1; x < datos.size(); x++) {
					g.ponArista(datos[j] - 1, datos[x] - 1);
				}
			}
		}
		
	}

	Amiguisimo am(g, 0);
	

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
