/*@ <authors>
 *
 * Paula, Alemany Rodriguez (MARP01).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <deque>
#include <limits>

using namespace std;

#include "DigrafoValorado.h"
#include "IndexPQ.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>



template <typename Valor> 
class CaminosMinimos {
public: 
	
	CaminosMinimos(DigrafoValorado<Valor> const& g, int origen, int destino, vector<int> tiempos) : 
		origen(origen), destino(destino), dist(g.V(), INF), pq(g.V()) {
		dist[origen] = tiempos[origen];
		pq.push(origen, 0); 
		//Queremos que el bucle termine cuando el destino salga de la cola y ya no sea modificable
		while (!pq.empty() && pq.top().elem != destino) { 
			int v = pq.top().elem; pq.pop(); 
			for (auto a : g.ady(v)) 
				relajar(a, tiempos);
		}
	}
	
	bool hayCamino(int v) const { return dist[v] != INF; }
	
	Valor distancia(int v) const { return dist[v]; }

private: 
	
	const Valor INF = std::numeric_limits<Valor>::max(); 
	int origen; 
	int destino;
	std::vector<Valor> dist; 
	IndexPQ<Valor> pq; 
	
	void relajar(AristaDirigida<Valor> a, vector<int> tiempos) {
		int v = a.desde(), w = a.hasta(); 
		if (dist[w] > dist[v] + a.valor() + tiempos[w]) {
			dist[w] = dist[v] + a.valor() + tiempos[w];  
			pq.update(w, dist[w]);
		} 
	}
};

void resuelveCaso() {
	// leer los datos de la entrada
	int N;
	cin >> N;
	DigrafoValorado<int> red(N);
	vector<int>tiemposCarga;

	int t;
	for (int i = 0; i < N; i++) {
		cin >> t;
		tiemposCarga.push_back(t);
	}

	int M;
	cin >> M;
	int A, B, T;
	for (int i = 0; i < M; i++) {

		cin >> A >> B >> T;
		red.ponArista({ A - 1, B - 1, T });
	}

	// resolver el caso posiblemente llamando a otras funciones
	CaminosMinimos<int> tiempo(red, 0, N - 1, tiemposCarga);

	if (!tiempo.hayCamino(N - 1))
		cout << "IMPOSIBLE\n";
	else {
		cout << tiempo.distancia(N - 1) << '\n';
	}
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
