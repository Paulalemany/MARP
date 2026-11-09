/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
 //#include <...>

using namespace std;

#include "PriorityQueue.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct trabajo {
	int c;
	int f;
};

bool operator<(const trabajo a, const trabajo b) {
	return a.c < b.c;
}

void resuelveCaso() {
	// leer los datos de la entrada
	int C, F, N;

	cin >> C >> F >> N;

	int c, f;
	PriorityQueue<trabajo> trabajos;
	for (int i = 0; i < N; i++) {

		cin >> c >> f;
		trabajos.push({ c,f });
	}


	int cubierto = C;
	int mejor = C;
	bool imposible = false;
	int t = 0;

	while (!imposible && cubierto < F) {
		
		mejor = cubierto;
		while (!trabajos.empty() && trabajos.top().c <= cubierto) {
			mejor = max(mejor, trabajos.top().f);
			trabajos.pop();
		}

		if (mejor == cubierto)
			imposible = true;

		t++;
		cubierto = mejor;

	}

	// escribir la solución
	if (imposible)
		cout << "Imposible\n";
	else
		cout << t << '\n';
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
