
/*@ <authors>
 *
 * Paula, Alemany Rodriguez (MARP01).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "Matriz.h"

/*@ <answer>

 Nos encontramos ante un problema que se puede resolver mediante programación dinámica ascendente
 Contamos con distintas restricciones:
 No podemos salir de la matriz
	-> Para solucionarlo antes de saltar comprobaremos:
		1 <= i <= 50
		1 <= j <= 50
Nos movemos a[i][j] casillas
	-> Para ello al realizar los saltos sumaremos este numero a la i o a la j

Los distintos elementos de la tabla significan lo siguiente:
	i -> Fila en la que nos encontramos
	j -> Columna en la que nos encontramos
	dp[i][j] -> Numero de formas de llegar a la casilla i j

Contamos con un caso base:
	dp[1][1] = 1 -> La única forma de llegar a la casilla de salida es no moverse

Recurrencia
	La idea de esta recurrencia es ir pensando hacia delante 
	porque el numero de formas de llegar a la casilla actual ya lo tenemos
	Por lo tanto tenemos 2 opciones:
		- Saltar hacia abajo -> dp[i + a[i][j]] [j] += dp[i][j] //Formas de llegar a la casilla de abajo + formas de llegar a la casilla actual
		- Saltar hacia la derecha -> dp[i] [j + a[i][j]] += dp[i][j] //Formas de llegar a la casilla de la derecha + formas de llegar a la casilla actual

El coste de este algoritmo es de O(n * m) siendo n*m el tamaño de la matriz
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int formasPosibles(vector<vector<int>> const& a, int n, int m) 
{ 
	Matriz<int> dp(n, m, 0); 
	dp[0][0] = 1; //Nuestra representacion interna comienza en 0 y no en 1

	for (int i = 0; i < n; ++i) 
	{ 
		for (int j = 0; j < m; ++j) {

			int num = a[i][j];
			//no queremos minimizar ni maximizar nada queremos probar todos los caminos posibles

			//saltar hacia abajo
			if (i + num < n)
				dp[i + num][j] += dp[i][j];

			//saltar hacia la derecha
			if (j + num < m)
				dp[i][j + num] += dp[i][j];
		}
	} 
	return dp[n - 1][m - 1]; 
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int n, m;

	cin >> n >> m;

	if (!std::cin)  // fin de la entrada
		return false;

	//Creamos la matriz
	vector<vector<int>> matriz;
	int dato;
	vector<int> fila;

	for (int i = 0; i < n; i++) {

		for (int j = 0; j < m; j++) {
			cin >> dato;
			fila.push_back(dato);
		}
		matriz.push_back(fila);
		fila.clear();
	}

	// escribir la solución
	cout << formasPosibles(matriz, n, m) << '\n';

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
