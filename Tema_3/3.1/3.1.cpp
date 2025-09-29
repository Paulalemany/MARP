
/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
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

bool resuelveCaso() {
	// leer los datos de la entrada
	int E, N, mid;
	cin >> E >> N;

	if (E == 0 && N == 0)
		return false;

	PriorityQueue<int, less<int>> der;
	PriorityQueue<int, greater<int>> izq;
	
	der.push(E);	//En la derecha va a estar el mediano

	for (int i = 0; i < N * 2; i++) {
		cin >> E;

		if (E < der.top()) izq.push(E); 
		else der.push(E);

		//Nivelamos si hace falta
		if (izq.size() > der.size()) {	//Tenemos que pasar el top de la izquierda a la derecha
			der.push(izq.top());
			izq.pop();
		}
		else if (der.size() > izq.size() + 1) {	//Tenemos que pasar el que era el centro a la izquierda
			izq.push(der.top());
			der.pop();
		}

		//Si hemos terminado de rellenar un par escribimos solución
		if (i % 2 != 0) cout << der.top() << " ";

	}

	cout << '\n';

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
