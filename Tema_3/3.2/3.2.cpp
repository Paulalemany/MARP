
/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

using namespace std;

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

struct pais {
	string nombre;
	int puntos;
};

bool operator<(pais const& a, pais const& b) {
	return b.puntos < a.puntos ||
		(b.puntos == a.puntos && a.nombre < b.nombre);
}

bool resuelveCaso() {
	// leer los datos de la entrada
	IndexPQ<string, pais> puntuaciones;
	int n;

	cin >> n;

	if (!std::cin)  // fin de la entrada
		return false;

	string evento;
	for (int i = 0; i < n; i++) {

		cin >> evento;

		if (evento == "?") {	//Comprobamos quien va ganando
			cout << puntuaciones.top().prioridad.nombre << " " << puntuaciones.top().prioridad.puntos << '\n';
		}
		else {
			int puntos;
			cin >> puntos;

			//Si el pais ya estaba en el listado sus puntos se tienen que sumar o restar
			if (puntuaciones.contiene(evento))
				puntos += puntuaciones.priority(evento).puntos;
				

			puntuaciones.update(evento, { evento, puntos });
		}
	}

	cout << "---\n";

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
