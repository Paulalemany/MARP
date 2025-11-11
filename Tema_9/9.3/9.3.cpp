/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <deque>
#include <queue>

using namespace std;

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

	int p;
	priority_queue<int> ordenar;
	deque<int> pilas;
	for (int i = 0; i < N; i++) {
		cin >> p;
		ordenar.push(p);
	}

	//Pasamos las pilas ordenadas a la deque
	while (!ordenar.empty()) {
		pilas.push_front(ordenar.top());
		ordenar.pop();
	}

	int coches = 0;
	int num = pilas.size();
	//Lo hacemos asi porque si solo queda una pila y esta no es del valor del mínimo terminamos
	while (!pilas.empty()) {
		if (pilas.back() == V) {
			coches++;
			pilas.pop_back();
			num--;
		}
		else if (num > 1 && pilas.front() + pilas.back() >= V) {
			coches++;
			pilas.pop_back();
			pilas.pop_front();
			num -= 2;
		}
		else {
			pilas.pop_front();
			num--;
		}
	}
	cout << coches << '\n';
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
