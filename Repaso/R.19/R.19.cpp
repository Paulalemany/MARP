
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "Matriz.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

//i -> Actividad
//j -> Tiempo 
//M[i][j] -> Es posible llegar al tiempo j con las actividades de 0 a i
void posible(vector<bool>& Ant, vector<bool>& Act, vector<int> const& actividades, int N, int S) {

	//Casos base
	//Antes M[0][0] true
	Ant[0] = true;

	for (int i = 1; i < N; i++) {

		Act[0] = true;

		for (int j = 1; j < S; j++) {

			//Es posible llegar al tiempo si es posible sin esta actividad o con esta actividad
			bool usarla = false;
			if (j - actividades[i - 1] >= 0)
				usarla = Ant[j - actividades[i - 1]];

			Act[j] = Ant[j] || usarla;
		}

		//Cambiamos de filas
		Ant = Act;
	}
}

int reconstruccionSol(vector<bool> const& Act, int S) {

	//Recorremos de 0 a S/2 buscando la mejor opción
	int mejor = S;	//Caso peor

	for (int j = 0; j <= S; j++) {
		if (Act[j]) {
			//Si existe la suma vemos que resultado es el mayor
			int duracion = max(j, S - j);

			//Nos quedamos con el mejor resultado posible
			mejor = min(mejor, duracion);
		}
	}

	return mejor;
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int N;

	cin >> N;

	if (!std::cin)  // fin de la entrada
		return false;

	int dato;
	int SumaTotal = 0;
	vector<int> actividades;

	for (int i = 0; i < N; i++) {
		cin >> dato;
		SumaTotal += dato;
		actividades.push_back(dato);
	}

	vector<bool> actual(SumaTotal + 1, false);
	vector<bool> anterior(SumaTotal + 1, false);

	// resolver el caso posiblemente llamando a otras funciones
	posible(anterior, actual, actividades, N, SumaTotal);

	// escribir la solución
	cout << reconstruccionSol(actual, SumaTotal) << '\n';

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
