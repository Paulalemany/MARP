
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;
#include "DigrafoValorado.h"
#include "ConjuntosDisjuntos.h"
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
class Dijkstra {
private:
	const Valor INF = std::numeric_limits<Valor>::max();
	int origen;
	std::vector<Valor> dist;
	std::vector<AristaDirigida<Valor>> ulti;
	IndexPQ<Valor> pq;

	void relajar(AristaDirigida<Valor> a) {
		int v = a.desde(), w = a.hasta();
		if (dist[w] > dist[v] + a.valor()) {
			dist[w] = dist[v] + a.valor(); ulti[w] = a;
			pq.update(w, dist[w]);
		}
	}

public:

	Dijkstra(DigrafoValorado<Valor> const& g, int orig) : origen(orig),
		dist(g.V(), INF), ulti(g.V()), pq(g.V()) {
		dist[origen] = 0;
		pq.push(origen, 0);
		while (!pq.empty()) {
			int v = pq.top().elem; pq.pop();
			for (auto a : g.ady(v))
				relajar(a);
		}
	}

	Valor distancia(int v) const { return dist[v]; }
	vector<Valor> distancias(){ return dist; }

};

bool resuelveCaso() {
	// leer los datos de la entrada
	int N, M;
	cin >> N >> M;

	if (!std::cin)  // fin de la entrada
		return false;

	DigrafoValorado <long long> carreteras(N);

	int n1, n2;
	long long c;
	for (int i = 0; i < M; i++) {
		cin >> n1 >> n2 >> c;
		carreteras.ponArista({ n1 - 1, n2 - 1, c });
		carreteras.ponArista({ n2 - 1, n1 - 1, c });
	}

	//Buscamos entre los adyacentes de la planta 1 los que tengan menos coste
	//Camiones que salen de cada planta
	int camiones = (N - 2) / 2;	//Numero de pueblos que visita cada planta

	//Calculamos las distancias de los pueblos a las plantas
	Dijkstra<long long> Norte(carreteras, 0);
	vector<long long> DN = Norte.distancias();

	Dijkstra<long long> Sur(carreteras, N - 1);
	vector<long long> DS = Sur.distancias();

	priority_queue<pair<long long, long long>> diferencias;	//Lo hacemos con un nodo para saber que pueblos son
	vector<long long> norte;

	//Ordenamos las diferencias
	for (int i = 0; i < DS.size(); i++) {
		diferencias.push({ DN[i] - DS[i], i });
	}

	//Las que tengan una diferencia menor las guardamos para que vaya la planta norte
	long long camino = 0;

	//Las plantas están en los extremos de la cola de prioridad
	//Quitamos el primero 
	diferencias.pop();

	for (int i = 0; i < camiones; i++) {
		
		camino += Sur.distancia(diferencias.top().second) * 2;
		diferencias.pop();
	}

	//El resto de pueblos los visita el norte

	//Nunca se llega al último
	for (int i = 0; i < camiones; i++) {
		camino += Norte.distancia(diferencias.top().second) * 2;
		diferencias.pop();
	}

	cout << camino << '\n';

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
