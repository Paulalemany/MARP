
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

#include "PriorityQueue.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


struct caja {
	int id = 0;		//Identificador de la caja
	int espera = 0;	//Tiempo de espera para que la caja esté libre
};

bool operator<(const caja& a, const caja& b) {
	return a.espera < b.espera ||
		((a.espera == b.espera) && (a.id < b.id));
}


bool resuelveCaso() {

	// leer los datos de la entrada
	int N, C;
	cin >> N >> C;

	if (N == 0 && C == 0)
		return false;

	//Creamos las cajas
	PriorityQueue<caja> cajas;
	caja caja;
	for (int i = 0; i < N; i++) {
		caja.id = i + 1;
		cajas.push(caja);
	}

	//Guardamos los clientes y sus tiempos
	int t;
	for (int i = 0; i < C; i++) {
		cin >> t;
		caja = cajas.top();
		cajas.pop();
		caja.espera += t;
		cajas.push(caja);
	}

	cout << cajas.top().id << '\n';

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
