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

int comida_rec(vector<int> const& cubos, int i, int j, Matriz<int>& buche, int t) 
{
	if (i > j) return 0;
	int& res = buche[i][j]; 
	
	if (res == -1) 
	{ 
		
		if (t % 2 != 0)	//Turno de devoradora
		{
			if (i == j - 1)
				res = min(cubos[i], cubos[j]);	//La otra se ha cogido la mejor de las dos
			//Devoradora coge el cubo con mas comida
			else if (cubos[i] >= cubos[j])	//Coge el cubo de la izquierda
				res = comida_rec(cubos, i + 1, j, buche, t + 1);
			else //Coge el cubo de la derecha
				res = comida_rec(cubos, i, j - 1, buche, t + 1); 
		}
		else { //Nuestro turno 

			if (i == j - 1)
				res = max(cubos[i], cubos[j]);
			else
				res = max(comida_rec(cubos, i + 1, j, buche, t + 1) + cubos[i],
						  comida_rec(cubos, i, j - 1, buche, t + 1) + cubos[j]);
		}
	}

	return res; 
}

void resuelveCaso() {
	// leer los datos de la entrada
	int N;
	cin >> N;

	vector<int> cubos;
	int c;
	for (int i = 0; i < N; i++) {
		cin >> c;
		cubos.push_back(c);
	}

	// resolver el caso posiblemente llamando a otras funciones
	Matriz<int> buche(N, N, -1);

	// escribir la solución
	cout << comida_rec(cubos, 0, N - 1, buche, 0) << '\n';
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
