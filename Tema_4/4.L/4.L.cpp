/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <climits>

using namespace std;

#include "Grafo.h"

/*@ <answer>

 Nos encontramos ante un ejercicio que se resuelve mediante grafos en el que los
 vértices son las intersecciones entre calles y las aristas las calles en si, formando 
 un grafo NO dirigido y NO valorado.

 Para resolver este ejercicio se utilizan diferentes recorridos en anchura:
	- Recorrido para ver la distancia entre el Trabajo y todos los demas sitios.
	- Recorrido para ver la distancia que hay entre la casa de Alex y todos los demas sitios.
	- Recorrido para ver la distancia que hay entre la casa de Lucas y todos los demas sitios.

 Tras esto vemos donde es mejor quedar entre todos los nodos posibles y nos quedamos con aquella
 opción que nos de menor coste total.

 Recorrer todas las opciones posibles tiene un coste en O(N) y los recorridos en anchura tienen
 un coste en O(N + A) por lo que el coste final de la solución sería de O(N + A) siendo N el 
 numero de intersecciones y A el numero de calles.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class CaminoMasCorto {
public: 
	
	CaminoMasCorto(Grafo const& g, int s) 
		: visit(g.V(), false), ant(g.V()), dist(g.V()), s(s) {
		bfs(g); 
	}
	
	// ¿hay camino del origen a v? 
	bool hayCamino(int v) const { 
		return visit[v]; 
	}

	// número de aristas entre s y v 
	int distancia(int v) const { 

		return dist[v]; 
	} 

private: 
	
	std::vector<bool> visit; // visit[v] = ¿hay camino de s a v? 
	std::vector<int> ant; // ant[v]  = último vértice antes de llegar a v 
	std::vector<int> dist; // dist[v] = aristas en el camino s-v más corto 
	int s;

	void bfs(Grafo const& g) { 
		std::queue<int> q; 
		dist[s] = 0; visit[s] = true; 
		q.push(s); 
		
		while (!q.empty()) { 
			int v = q.front(); 
			q.pop(); 
			for (int w : g.ady(v)) {
				if (!visit[w]) { 
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
	int N, C, A, L, T;
	cin >> N >> C >> A >> L >> T;

	Grafo ciudad(N);

	int d1, d2;
	for (int i = 0; i < C; i++) {

		cin >> d1 >> d2;
		ciudad.ponArista(d1 - 1, d2 - 1);
	}

	// resolver el caso posiblemente llamando a otras funciones
	// vemos la distancia del trabajo a todas partes
	//O(N + C)
	CaminoMasCorto trabajo(ciudad, T - 1);
	CaminoMasCorto Alex(ciudad, A - 1);
	CaminoMasCorto Lucas(ciudad, L - 1);

	//Probamos todos los nodos como punto de encuentro
	int costeMinimo = INT_MAX;
	for (int v = 0; v < N; v++) {
		int coste = Alex.distancia(v) + Lucas.distancia(v) + trabajo.distancia(v);
		costeMinimo = min(costeMinimo, coste);
	}

	cout << costeMinimo << '\n';
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
