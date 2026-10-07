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

class CaminoMasCorto {
public: 
	CaminoMasCorto(Grafo const& g, int s, int ttl) 
		: visit(g.V(), false), ant(g.V()), dist(g.V()), s(s)
	{ 
		bfs(g, ttl); 
	} 

	// número de aristas entre s y v 
	int distancia(int v) const { 
		return dist[v]; 
	} 

	int noAlcanzables() {

		//Escribimos todos los nodos no visitados
		int cont = 0;
		for (int i = 0; i < visit.size(); i++) {
			if (!visit[i])
				cont++;
		}
		return cont;
	}

private: 

	std::vector<bool> visit; // visit[v] = ¿hay camino de s a v? 
	std::vector<int> ant; // ant[v]  = último vértice antes de llegar a v 
	std::vector<int> dist; // dist[v] = aristas en el camino s-v más corto 
	int s;

	void bfs(Grafo const& g, int ttl) { 
		std::queue<int> q; 
		dist[s] = 0; 
		visit[s] = true; 
		q.push(s); 
		while (!q.empty()) {
			int v = q.front(); 
			q.pop(); 
			for (int w : g.ady(v)) { 
				if (!visit[w] && ttl >= dist[v] + 1) {
					ant[w] = v; 
					dist[w] = dist[v] + 1; 
					visit[w] = true; 
					q.push(w); 
				} 
			} 
		} 
	}
};

void resuelveCaso() {

	// leer los datos de la entrada
	int N, C;
	cin >> N >> C;

	Grafo g(N);

	int n1, n2;
	for (int i = 0; i < C; i++) {

		cin >> n1 >> n2;
		g.ponArista(n1 - 1, n2 - 1);
	}

	// resolver el caso posiblemente llamando a otras funciones
	int k;
	cin >> k;
	for (int i = 0; i < k; i++) {
		int s, ttl;

		cin >> s >> ttl;
		CaminoMasCorto c(g, s - 1, ttl);
		cout << c.noAlcanzables() << '\n';
	}

	// escribir la solución
	cout << "---\n";
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
