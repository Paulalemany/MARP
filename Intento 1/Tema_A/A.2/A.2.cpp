
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

#include "EnterosInf.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

const long long INF = 1e18;

struct cuerda {
	int largo = 0;
	int coste = 0;
};

bool resuelveCaso() {

	// leer los datos de la entrada
	int V, S;
	cin >> V >> S;

	if (!std::cin)  // fin de la entrada
		return false;

	//Guardamos las secciones de la diana y sus valores
	vector<int> diana;
	int v;

	for (int i = 0; i < S; i++) {
		cin >> v;
		diana.push_back(v);
	}

	/// Guardamos las soluciones
	vector<EntInf> minDardos(V + 1, Infinito);	//Vector donde guardamos los dardos minimos necesarios
	vector<int> sol;	//Vector donde guardamos las soluciones al problema

	//Rellenamos la primera fila/columna
	minDardos[0] = 0;

	//Las secciones pueden repetirse sin ningún problema así que es igual que el problema de las monedas
	// calcular la matriz sobre el propio vector 
	for (int i = 1; i <= S; ++i) {
		for (int j = diana[i-1]; j <= V; ++j) {
			minDardos[j] = min(minDardos[j], minDardos[j - diana[i-1]] + 1);
		} 
	}

	///Solucion
	if (minDardos[V] != Infinito) {	//Hay una solución posible
		int i = S, j = V;
		while (j > 0) { //No hemos llegado a la suma que buscamos

			//Mientras el valor que estamos viendo no sea superior al que falta
			//Y Los minimos actuales sean igual al minimo anterior
			if (diana[i - 1] <= j && minDardos[j] == minDardos[j - diana[i - 1]] + 1) {
				// Tratamos de darle a la misma sección de la diana
				sol.push_back(diana[i - 1]);
				j -= diana[i - 1];	//Le restamos a lo que nos queda por sumar lo que acabamos de sumar
			}
			else { //No volvemos a dar en esa sección de la diana
				i--;
			}
		}
		
		cout << sol.size() << ":";
		for (auto i : sol) cout << " " << i;
		cout << '\n';
	}
	else {	//No hay solución posible
		cout << "Imposible\n";
	}
	


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
