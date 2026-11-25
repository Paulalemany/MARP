/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

#include "EnterosInf.h"
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

void Floyd(Matriz<EntInf> const& G, Matriz<EntInf>& C) {
	
	int V = G.numfils(); // número de vértices de G 
	
	// inicialización 
	C = G; 
	// actualizaciones de las matrices 
	for (int k = 0; k < V; ++k) 
	{ 
		for (int i = 0; i < V; ++i) 
		{ 
			for (int j = 0; j < V; ++j) 
			{ 
				if (i == j) //El coste de ir a si mismo es 0
					C[i][j] = 0;
				else {

					auto temp = C[i][k] + C[k][j]; 
					if (temp < C[i][j]) // es mejor pasar por k 
					{ 
						C[i][j] = temp; 
					} 
				}
			
			} 
		} 
	} 
}

void resuelveCaso() {
	// leer los datos de la entrada
	int P, R;
	cin >> P >> R;

	if (P == 1) cout << 0 << '\n';
	else {

		unordered_map<string, int> personas;
		Matriz<EntInf> G(P, P, Infinito);	//Matriz de adyacencia del grafo

		string p1, p2;
		int cont = 0;
		for (int i = 0; i < R; i++) {
			cin >> p1 >> p2;

			if (!personas.contains(p1)) {
				personas.emplace(p1, cont);
				cont++;
			}
			if (!personas.contains(p2)) {
				personas.emplace(p2, cont);
				cont++;
			}

			//Ponemos la relación en la matriz de adyacencia
			//La ponemos en ambos sentidos para que sea simetrica
			G[personas[p1]][personas[p2]] = 1;
			G[personas[p2]][personas[p1]] = 1;
		}

		// resolver el caso posiblemente llamando a otras funciones
		Matriz<EntInf>C;

		Floyd(G, C);

		EntInf maxim = 0;
		//Buscamos la distancia más larga
		for (int i = 0; i < P; i++) {
			for (int j = i; j < P; j++) {
				maxim = max(maxim, C[i][j]);
			}
		}

		if (maxim == Infinito)
			cout << "DESCONECTADA\n";
		else
			cout << maxim << '\n';
	}
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
