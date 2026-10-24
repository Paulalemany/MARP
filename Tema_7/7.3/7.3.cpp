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
		origen(origen), destino(destino), dist(g.V(), INF), form(g.V(), 0), pq(g.V()) {
		dist[origen] = 0;
		form[origen] = 1;
		pq.push(origen, 0);
		//Queremos que el bucle termine cuando el destino salga de la cola y ya no sea modificable
		while (!pq.empty()) {
			int v = pq.top().elem; pq.pop();
			for (auto a : g.ady(v))
				relajar(a);
		}
	}

	int formas(int v) const { return form[v]; }

private:

	const Valor INF = std::numeric_limits<Valor>::max();
	int origen;
	int destino;
	std::vector<Valor> dist;
	vector<int> form;
	IndexPQ<Valor> pq;

	void relajar(AristaDirigida<Valor> a) {

		if (a.hasta() == destino)
			cout << "";

		int v = a.desde(), w = a.hasta();
		if (dist[w] > dist[v] + a.valor()) {
			form[w] = form[v];
			dist[w] = dist[v] + a.valor();
			pq.update(w, dist[w]);
		}
		else if (dist[w] == dist[v] + a.valor()) {
			form[w] += form[v];
		}
	}
};

void resuelveCaso() {
	// leer los datos de la entrada
	int N, C;
	cin >> N >> C;
	DigrafoValorado<int> ciudad(N);

	int A, B, L;
	for (int i = 0; i < C; i++) {

		cin >> A >> B >> L;
		ciudad.ponArista({ A - 1, B - 1, L });
		ciudad.ponArista({ B - 1, A - 1, L });
	}

	// resolver el caso posiblemente llamando a otras funciones
	CaminosMinimos<int> maneras(ciudad, 0, N - 1);
	
	cout << maneras.formas(N - 1) << '\n';
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
