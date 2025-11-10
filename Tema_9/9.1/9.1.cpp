
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
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

struct edificio
{
	int W;
	int E;
};

bool resuelveCaso() {
	// leer los datos de la entrada
	int N;
	cin >> N;

	if (N == 0)
		return false;

	vector<edificio> lineas;

	//Leemos los datos

	int W, E;
	for (int i = 0; i < N; i++) {
		cin >> W >> E;
		edificio a{W, E};

		lineas.push_back(a);	
	}

	//Ordenamos los edificios por orden de este de menor a mayor
	sort(lineas.begin(), lineas.end(), [](const edificio& a, const edificio& b) {
		return a.E < b.E;
	});

	int pasillos = 0;	//Contador de pasillos que llevamos
	int posicion = -1;	// posición donde colocamos el túnel actual

	for (auto& ed : lineas) {
		//Si la posición del último pasillo no cubre el edificio
		if (posicion <= ed.W) { // Necesitamos un nuevo pasillo
			pasillos++;
			posicion = ed.E; // Colocamos el pasillo en el extremo derecho del edificio
		}
	}
	

	// escribir la solución
	cout << pasillos << '\n';

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
