/*@ <authors>
 *
 * Paula, Alemany Rpdríguez (MARP01).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
 //#include <...>

using namespace std;

#include "GrafoValorado.h"
#include "ConjuntosDisjuntos.h"
#include "PriorityQueue.h"

/*@ <answer>

  Nos encontramos ante un problema que puede resolverse mediante un grafo no dirigido y valorado
 en el que los nodos son las localidades y las posibles aristas son las carreteras posibles entre localidades.
 Contamos con un valor que utilizamos como cota superior a la hora de crear el grafo, este es el coste de un 
 aeropuerto, como buscamos maximizar el numero de aeropuertos, si el coste de la carretera no es estrictamente menor
 que el coste del aeropuerto esta carretera ni siquiera se va a poner en el grafo, esto con el objetivo de que el 
 numero de aeropuertos sea el numero de componentes conexas del grafo.

 Despues de la creación del grafo para ver el mejor coste de las uniones entre localidades utilizamos el algoritmo de Kruskal
 para elegir el recubrimiento con menor coste total.

 Con estos dos datos ya podemos construir la solución:
	- Tendremos un aeropuerto por componente conexa del grafo (Ya que las carreteras mas costosas no las hemos añadido al grafo)
	- El coste de construir las carreteras es el coste dado por el algoritmo de kruskal y el coste de los aeropuertos es el coste
	de un aeropuerto por el numero de componentes conexas del grafo (gracias a los conjuntos este calculo es bastante sencillo)

 El coste de esta solucion sería el coste del algoritmo de Kruskal, es decir, tiene un tiempo en espacio de O(m log m) donde m es el 
 subconjunto de aristas que hay en el bosque de recubrimiento y un tiempo en espacio adicional de O(m).

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

template <typename Valor>

class ARM_Kruskal {
private:
	std::vector<Arista<Valor>> _ARM;
	Valor coste;
	int aeropuertos;

public:

	Valor costeARM() const {
		return coste;
	}

	int numAeropuertos() const {
		return aeropuertos;
	}

	ARM_Kruskal(GrafoValorado<Valor> const& g) : coste(0) {

		PriorityQueue<Arista<Valor>> pq(g.aristas());
		ConjuntosDisjuntos cjtos(g.V());
		while (!pq.empty()) {
			auto a = pq.top(); pq.pop();
			int v = a.uno(), w = a.otro(v);
			if (!cjtos.unidos(v, w)) {
				cjtos.unir(v, w);
				_ARM.push_back(a); coste += a.valor();
				if (_ARM.size() == g.V() - 1) break;
			}
		}

		aeropuertos = cjtos.num_cjtos();
	}
};

void resuelveCaso() {
	// leer los datos de la entrada
	int N, M, A;
	cin >> N >> M >> A;

	GrafoValorado<int> ciudad(N);
	int x, y, c;

	for (int i = 0; i < M; i++) {
		cin >> x >> y >> c;

		//Solo nos interesa poner la carretera posiblemente si cuesta menos que un aeropuerto
		if (c < A)
			ciudad.ponArista({ x - 1, y - 1, c });
	}

	// resolver el caso posiblemente llamando a otras funciones
	ARM_Kruskal<int> sol(ciudad);

	// escribir la solución
	cout << sol.costeARM() + sol.numAeropuertos() * A << " " << sol.numAeropuertos() << '\n';
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
