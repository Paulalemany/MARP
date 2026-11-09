/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

#include "PriorityQueue.h"

/*@ <answer>

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct edificio {
	int W;
	int E;
};

bool operator<(const edificio a, const edificio b) {
	return a.W < b.W;
}

int numTunel(PriorityQueue<edificio> edif) {

	int tunel = 0;

	int minE = std::numeric_limits<int>::max();
	while (!edif.empty()) {
		if (edif.top().W >= minE){
			tunel++;	//Ya estan contados todos los edificios que comparten tunel
			minE = edif.top().E;
			edif.pop();
		}
		else {

			minE = min(edif.top().E, minE);
			edif.pop();
		}

	}

	//El tunel que comparten los ultimos edificios
	tunel++;

	return tunel;
}

void resuelveCaso() {
	// leer los datos de la entrada
	int N;

	cin >> N;

	int w, e;
	PriorityQueue<edificio> edif;
	for (int i = 0; i < N; i++) {

		cin >> w >> e;
		edif.push({ w,e });
	}

	cout << numTunel(edif) << '\n';
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
