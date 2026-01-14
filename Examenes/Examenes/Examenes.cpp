
/*@ <authors>
 *
 * Paula, Alemany Rodriguez (MARP01)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <limits>
#include <deque>

#include "ConjuntosDisjuntos.h"
#include "DigrafoValorado.h"
#include "IndexPQ.h"

using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 // 
 // Para resolver este problema utilizamos Dijkstra un poco modificado
 // No queremos coger el camino que menos nos haga aguantar la respiración sino el
 // camino que su componente más alta nos haga aguantar menos la respiración.
 // para ello modificamos la función relajar para que la distancia que guarda sea 
 // la componente mayor del camino que es justo la solución que nos piden.
 // La complejidad de Dijkstra es de O(A * log V) siendo A el numero de aristas
 // y V el numero de vertices, mientras que hay camino y distancia son constantes,
 // por lo tanto la solución tiene una complejidad de O(A log V)
 //@ <answer>

template <typename Valor> 
class Dijkstra {
	public: 

		//Complejidad O(A log V) Siendo A numero de aristas y V el numero de vertices
		Dijkstra(DigrafoValorado<Valor> const& g, int orig) : 
			origen(orig), dist(g.V(), INF), pq(g.V()) {

			dist[origen] = 0; 
			pq.push(origen, 0); 

			while (!pq.empty()) { 
				int v = pq.top().elem; 
				pq.pop(); 
				for (auto a : g.ady(v)) relajar(a); 
			} 
		}

		//O(1)
		bool hayCamino(int v) const { return dist[v] != INF; } 
		Valor distancia(int v) const { return dist[v]; } 

	private: 
		const Valor INF = std::numeric_limits<Valor>::max(); 
		int origen; 
		std::vector<Valor> dist;  
		IndexPQ<Valor> pq;

		void relajar(AristaDirigida<Valor> a) 
		{
			int v = a.desde(), w = a.hasta();

			Valor nuevo = max(dist[v], a.valor());
			if (dist[w] > nuevo) { 
				dist[w] = nuevo; 
				pq.update(w, dist[w]); 
			} 
		}
};

bool resuelveCaso() {
	// leer los datos de la entrada
	int N, M;

	//Leemos el numero de camaras y galerias
	cin >> N >> M;

	if (!std::cin)  // fin de la entrada
		return false;

	//Creamos el grafo
	DigrafoValorado<int> mapa(N);

	int ini, f, t;
	for (int i = 0; i < M; i++) {
		cin >> ini >> f >> t;
		//Ponemos 2 para que sea bidireccional
		AristaDirigida<int> a(ini - 1, f - 1, t);
		AristaDirigida<int> b(f - 1, ini - 1, t);
		mapa.ponArista(a);
		mapa.ponArista(b);
	}

	//Guardamos donde esta J y el tesoro
	int J, T;
	cin >> J >> T;

	// resolver el caso posiblemente llamando a otras funciones

	Dijkstra<int> camino(mapa, J - 1);

	if (!camino.hayCamino(T - 1))
		cout << "IMPOSIBLE\n"; 
	else 
		cout << camino.distancia(T - 1) << "\n"; 
	

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
