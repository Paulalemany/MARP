
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "EnterosInf.h"
#include <string>

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class CaminosMinimos {
private:
	int minManzanas;
	int N;
	int M;
	int caminos = 0;

	vector<vector<int>> sol;

	//Devuelve si es valida la posición
	bool valido(vector<string>& mapa, int x, int y, int man) {

		return ((x >= 0 && x < N) && (y >= 0 && y < M)
			&& (man < minManzanas) && mapa[x][y] != 'x');
	}

public:

	void avanzar(vector<string>& mapa, int x, int y, int man) {

		if (valido(mapa, x, y, man)) {	//Si las coordenadas son válidas

			//Comprobamos si hemos llegado al objetivo
			if (x == N - 1 && y == M - 1) {
				//Si hemos llegado al objetivo sumamos el numero de caminos totales que tenemos y terminamos
				caminos++;
				return;
			}
			else {	//No hemos llegado al objetivo

				//Probamos a avanzar por la derecha y por abajo
				//Si hay un punto por el que ya hemos pasado ya sabemos si ese camino puede llegar al final
				//La diferencia entre esas manzanas y las que llevamos son las que faltan
				//Si la suma de las que faltan más las que llevamos esta dentro del margen podemos sumar 1 sin terminar

				if (sol[x][y] != -1) {	//Ya hemos pasado por ahí
					int rest = sol[x][y] - man;
					if (sol[x][y] - man <= minManzanas) {
						caminos++;
						return;
					}
				}
				else {
					avanzar(mapa, x + 1, y, man++);
					avanzar(mapa, x, y + 1, man++);
				}
				
			}
		}
	}

};


bool resuelveCaso() {
	
	int N, M;
	cin >> N >> M;

	if (!std::cin)  // fin de la entrada
		return false;

	string linea;
	vector<string> mapa;

	for (int i = 0; i < N; i++) {
		cin >> linea;
		mapa.push_back(linea);
	}

	int minManzanas = (N - 1) + (M - 1);

	int manzanas = 0;

	///
	/// Comprobamos si las coordenadas están en el mapa y si está en obras
	/// Comprobamos si seguimos dentro de las mínimas
	/// Comprobamos si hemos llegado al objetivo
	///		Si es así paramos
	///		Guardamos que hemos llegado al final con 1 camino
	/// Si no hemos llegado al objetivo
	///		Si seguimos dentro de las manzanas mínimas
	///		Probamos los diferentes caminos
	///			Avanzar(x + 1, y) Avanzamos hacia la derecha 
	///			Avanzar(x, y + 1) Avanzamos hacia abajo
	///		Si nos hemos pasado de las manzanas mínimas
	///			volvemos
	///

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
