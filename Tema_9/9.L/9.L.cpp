/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <limits>

using namespace std;

#include "DigrafoValorado.h"
#include "IndexPQ.h"

/*@ <answer>

 Nos encontramos ante un ejercicio que puede resolverse con Digrafos Valorados y el algoritmo de Dijkstra.
 El grafo consta de Nodos que son los puntos importantes de la isla (Las dos desalinizadoras y los pueblos), a partir de ahora N,
 y aristas que son carreteras transitables en ambos sentidos, a partir de ahora M. Se nos asegura que el grafo es conexo, es decir
 que se puede llegar a todos los puntos importantes de la isla.

 Para resolverlo utilizamos Dijkstra con la intención de tener el camino minimo desde cada desalinizadora a cada punto importante.
 Como cada planta debe ir a la mitad de los pueblos, tras hacer dijkstra utilizamos la planta norte como referencia.
 Hacemos que la planta Norte vaya a los m pueblos a los que le cuesta menos llegar, siendo m la mitad de los pueblos siguiendo el siguiente calculo
 m = (N-2)/2. Con eso, hacemos que la planta Sur vaya a los pueblos a los que no ha podido ir la planta norte. 
 Como no podemos asegurar que dar prioridad al norte sea más beneficioso hacemos también lo mismo a la inversa y nos quedamos con el mejor resultado.

 El coste de esta solución es el siguiente:
	Primero crear el Digrafo valorado tiene un coste de O(N + M) ya que primero se crean los nodos y luego se ponen las aristas
	Luego cada Dijkstra tiene una complejidad en el orden O(M log V)
	Calcular el coste de cada desalinizadora tiene un coste en el orden de O(N)

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

template <typename Valor>
class Dijkstra {
public:
	Dijkstra(DigrafoValorado<Valor> const& g, int orig) : origen(orig),
		dist(g.V(), INF), ulti(g.V()), pq(g.V()) {
		dist[origen] = 0;
		pq.push(origen, 0);
		//int cont = (g.V() - 2) / 2;	//Para que solo lo haga con la mitad de los elementos
		while (!pq.empty() /* && cont >= 0*/) {
			int v = pq.top().elem; pq.pop();
			//cont--;
			for (auto a : g.ady(v))
				relajar(a);
		}
	}

	Valor distancia(int v) const { return dist[v]; }

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
};

void resuelveCaso() {
	// leer los datos de la entrada
	long long N, M;
	cin >> N >> M;

	DigrafoValorado<long long> mapa(N);

	long long a, b;
	long long c;
	for (int i = 0; i < M; i++) {
		cin >> a >> b >> c;
		mapa.ponArista({ a - 1, b - 1, c });
		mapa.ponArista({ b - 1, a - 1, c });
	}

	// resolver el caso posiblemente llamando a otras funciones
	Dijkstra<long long> Norte(mapa, 0);	//La estacion norte esta en el 0
	Dijkstra<long long> Sur(mapa, N - 1);

	IndexPQ<long long> ahorro(N);
	for (long long i = 1; i < N - 1; i++) {	//No queremos contar las plantas

		long long a = Norte.distancia(i) - Sur.distancia(i);
		ahorro.update(i, a);	//Ahorro de que el pueblo sea de la planta norte
	}

	long long costN = 0;
	long long costS = 0;
	long long mitad = (N - 2) / 2;

	while (!ahorro.empty()) {

		if (ahorro.size() > mitad)	//Van al norte
			costN += Norte.distancia(ahorro.top().elem);
		else	//Van al sur
			costS += Sur.distancia(ahorro.top().elem);

		ahorro.pop();
	}


	// escribir la solución
	cout << costN*2 + costS * 2 << '\n';
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
