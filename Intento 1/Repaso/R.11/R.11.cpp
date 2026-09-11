
/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <deque>

using namespace std;

#include "Matriz.h"
#include "EnterosInf.h"


/*@ <answer>

 Nos encontramos ante un problema que puede solucionarse con el Algoritmo de Floyd
 ya que buscamos encontrar el camino más corto entre cada par de vertices.

 El coste del algoritmo de Floyd es de O(V^3) Siendo V el número de vertices del grafo

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

void Floyd(Matriz<EntInf> const& G, Matriz<EntInf>& C) 
{
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
				auto temp = C[i][k] + C[k][j]; 
				if (temp < C[i][j]) 
				{ 
					// es mejor pasar por k 
					C[i][j] = temp; 
				} 
			} 
		} 
	} 
}


bool resuelveCaso() {
	// leer los datos de la entrada
	int N;

	cin >> N;

	if (!std::cin)  // fin de la entrada
		return false;

	//Rellenamos la matriz de los pueblos
	Matriz<EntInf> grafo(N,N, 0);
	int dato;
	for (int i = 0; i < N; i++) {
		for (int j = i; j < N; j++) {

			if (i == j) grafo[i][j] = 0;
			else {
				cin >> dato;
				grafo[i][j] = dato;
				grafo[j][i] = Infinito; // no se puede ir contra la corriente

			}
		}
	}

	// resolver el caso posiblemente llamando a otras funciones
	Matriz<EntInf> C;
	Floyd(grafo, C);

	// escribir la solución

	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			cout << C[i][j] << " ";
		}
		cout << '\n';
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
