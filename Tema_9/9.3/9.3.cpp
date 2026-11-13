/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <deque>
#include <algorithm>

using namespace std;

//#include "..."  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

void resuelveCaso() {
	// leer los datos de la entrada
	int N, V;

	cin >> N >> V;

	deque<int> pilas;
	int p;
	for (int i = 0; i < N; i++) {
		cin >> p;
		pilas.push_back(p);
	}

	//Ordenamos la cola de forma ascendente
	sort(pilas.begin(), pilas.end());

	// resolver el caso posiblemente llamando a otras funciones
	int cont = 0;
	while (!pilas.empty() && pilas.size() > 1) {	//Si solo queda un elemento tampoco nos sirve

		int sum = pilas.front() + pilas.back();

		if (sum >= V) {	//Suficiente para un coche
			cont++;
			pilas.pop_back();
			pilas.pop_front();
		}
		else {	//Quitamos la pila mas pequeña
			pilas.pop_front();
		}
	}

	// escribir la solución
	cout << cont << '\n';
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
