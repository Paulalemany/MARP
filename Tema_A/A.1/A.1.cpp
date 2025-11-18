
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
	int N, L;
	cin >> N >> L;

	if (!std::cin)  // fin de la entrada
		return false;

	//Necesitamos guardar los tipos de cuerda y la cantidad de cuerdas de cada tipo que tenemos
	vector<cuerda> cuerdas;
	cuerda c;
	for (int i = 0; i < N; i++) {
		cin >> c.largo >> c.coste;
		cuerdas.push_back(c);
	}

	// vectores para las soluciones
	vector<long long> formas(L + 1, 0);			//Cuantas maneras hay de obtener L
	vector<long long> minCuerdas(L + 1, INF);	//Cuerdas mínimas necesarias
	vector<long long> minCoste(L + 1, INF);		//Coste mínimo

	//Rellenamos la primera fila/columna
	formas[0] = 1;	//Si la resta da 0 es que hay 1 forma de llegar a ese número
	minCuerdas[0] = 0;
	minCoste[0] = 0;

	//Cada cuerda se utiliza como máximo una vez
	for (auto& c : cuerdas) {
		//Hacemos el for hacia atrás para tener cuanto nos queda por poner de cuerda
		for (int x = L; x >= c.largo; x--) {	

			//Primero contamos el número de formas posibles
			formas[x] += formas[x - c.largo];

			// Contamos el mínimo de cuerdas
			minCuerdas[x] = min(minCuerdas[x], minCuerdas[x - c.largo] + 1);

			//Contamos el mínimo coste
			minCoste[x] = min(minCoste[x], minCoste[x - c.largo] + c.coste);
		}
	}


	// escribir la solución
	if (formas[L] == 0) {	//No hay solución
		cout << "NO\n";
	}
	else {
		cout << "SI "
			<< formas[L] << " "
			<< minCuerdas[L] << " "
			<< minCoste[L] << "\n";
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
