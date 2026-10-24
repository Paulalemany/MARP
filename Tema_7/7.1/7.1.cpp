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
	
	CaminosMinimos(DigrafoValorado<Valor> const& g, int origen, int destino) : 
		origen(origen), destino(destino), dist(g.V(), INF), ulti(g.V()), pq(g.V()) {
		dist[origen] = 0; 
		pq.push(origen, 0); 
		//Queremos que el bucle termine cuando el destino salga de la cola y ya no sea modificable
		while (!pq.empty() && pq.top().elem != destino) { 
			int v = pq.top().elem; pq.pop(); 
			for (auto a : g.ady(v)) 
				relajar(a);
		}
	}
	
	bool hayCamino(int v) const { return dist[v] != INF; }
	
	Valor distancia(int v) const { return dist[v]; }

	deque<AristaDirigida<Valor>> camino(int v) const {
		deque<AristaDirigida<Valor>> cam; // recuperamos el camino retrocediendo 
		AristaDirigida<Valor> a; 
		for (a = ulti[v]; a.desde() != origen; a = ulti[a.desde()])
			cam.push_front(a); 
		cam.push_front(a);
		return cam;
	}

	void escribirCamino(int v) {
		deque<AristaDirigida<Valor>> cam = camino(v);

		int o = -1;
		int d = -1;
		while (!cam.empty()) {
			o = cam.front().desde();
			if (o == d)
				cout << " -> " << cam.front().hasta() + 1;
			else
			cout << cam.front().desde() + 1 << " -> " << cam.front().hasta() + 1;
			d = cam.front().hasta();
			cam.pop_front();
		}

	}

private: 
	
	const Valor INF = std::numeric_limits<Valor>::max(); 
	int origen; 
	int destino;
	std::vector<Valor> dist; 
	std::vector<AristaDirigida<Valor>> ulti; 
	IndexPQ<Valor> pq; 
	
	void relajar(AristaDirigida<Valor> a) {
		int v = a.desde(), w = a.hasta(); 
		if (dist[w] > dist[v] + a.valor()) {
			dist[w] = dist[v] + a.valor(); 
			ulti[w] = a; 
			pq.update(w, dist[w]);
		} 
	}
};

void resuelveCaso() {
	// leer los datos de la entrada
	int N, C;
	cin >> N >> C;
	DigrafoValorado<int> ciudad(N);

	int A, B, T;
	for (int i = 0; i < C; i++) {

		cin >> A >> B >> T;
		ciudad.ponArista({ A - 1, B - 1, T });
		ciudad.ponArista({ B - 1, A - 1, T });	//Todas las calles pueden recorrerse en ambos sentidos
	}

	// resolver el caso posiblemente llamando a otras funciones
	int K;
	cin >> K;

	int o, d;
	for (int i = 0; i < K; i++) {
		cin >> o >> d;
		CaminosMinimos<int> min(ciudad, o - 1, d - 1);

		if (min.hayCamino(d - 1)) {
			cout << min.distancia(d - 1) << ": ";
			min.escribirCamino(d - 1);
			cout << '\n';
		}
		else {
			cout << "NO LLEGA\n";
		}
	}

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
