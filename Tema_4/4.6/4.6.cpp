/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <unordered_map>

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

	//Necesito guardarme cuanto nodos tiene la componente conexa a la que pertenecen
	//Para ello podemos hacer que compartan el mismo origen

public: 
	
	MaximaCompConexa(Grafo const& g) : visit(g.V(), false), origen(g.V()), s(0) {
		for (int v = 0; v < g.V(); ++v) {
			if (!visit[v]) { // se recorre una nueva componente conexa 
				s = v;
				int tam = dfs(g, v); 
				red[s] = tam;
			} 
		} 
	}

	void EscribirSolucion(int N) {

		for (int i = 0; i < N; i++) {
			cout << red[origen[i]] << " ";
		}

		cout << '\n';
	}

private: 
	vector<bool> visit; // visit[v] = se ha visitado el vértice v? 
	vector<int> origen;	//Para saber a que componente conexa pertenece
	int s;				//Vertice origen
	unordered_map<int, int> red;    //Numero de nodos que tiene cada componente conexa

	int dfs(Grafo const& g, int v) {
		visit[v] = true;
		origen[v] = s;
		int tam = 1; 
		for (int w : g.ady(v)) { 
			if (!visit[w]) {
				tam += dfs(g, w); 
			}
		} 
		return tam; 
	} 
};

void resuelveCaso() {
	// leer los datos de la entrada
	int N, M;

	cin >> N >> M;

	Grafo amigos(N);


	for (int i = 0; i < M; i++) {
		int n;

		cin >> n;
		vector<int> aristas;
		for (int j = 0; j < n; j++) {
			int id;
			cin >> id;

			aristas.push_back(id);
		}

		//Pasamos de los grupos y ponemos todas las conexiones 
		//Porque no tenemos manera de saber cuantos son grupos
		for (int j = 0; j < n-1; j++) {
			amigos.ponArista(aristas[j]-1, aristas[j+1] - 1);
		}
	}

	// resolver el caso posiblemente llamando a otras funciones
	MaximaCompConexa sol(amigos);

	// escribir la solución
	sol.EscribirSolucion(N);
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
