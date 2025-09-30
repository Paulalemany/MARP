
/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

using namespace std;

#include "IndexPQ.h"  // propios o los de las estructuras de datos de clase

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
	int N;
	cin >> N;

	if (!std::cin)  // fin de la entrada
		return false;

	string datos;
	int p;
	IndexPQ <string, int, greater<int>> podio;

	for (int i = 0; i < N; i++) {
		cin >> datos;

		if (datos == "?") {	//Consultar al ganador

			if (!podio.empty())
				cout << podio.top().elem << " " << podio.top().prioridad << '\n';
		}
		else {	//Dar puntos a x pais
			cin >> p;
			//Queremos sumar los puntos
			try { p += podio.priority(datos); }	//Queremos sumarle los puntos que ya tiene
			catch (domain_error & e){ }
			
			try { podio.update(datos, p); }	//Actualizamos la prioridad
			catch (invalid_argument & e){}
			
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
