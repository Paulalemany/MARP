/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

#include "EnterosInf.h"
#include "Matriz.h"

/*@ <answer>

 Restricciones:
	La casilla a visitar debe estar dentro del tablero
 
 Objetivo:
	Conseguir la máxima puntuación posible
	Saber que casilla es la primera para conseguir la puntuación

 puntuacion(i, j) = Máxima puntuación posible para la casilla i, j

 Casos base:
	Las casillas fuera del tablero tienen una puntuación inválida de 0

 Recursión:
 puntuacion(i,j) = max(puntuacion(i-1, j-1), puntuacion(i-1, j), puntuacion(i-1, j+1)) + P(i,j)
	-> La puntuacion máxima de la casilla será la puntuación más alta de las casillas a las
	que puede ir más la puntuación de su propia casilla

 Llamada inicial:
 puntuacion(n, m) siendo n,m la posición de la esquina sureste de la ciudad

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

pair<EntInf, int> puntuacion(Matriz<int> const& tablero)
{
	int n = tablero.numfils();
	int m = tablero.numcols();
	Matriz<EntInf> p(n + 1, m + 2, 0);	//Sumo dos para tener las invalidas del extremo derecho también
	vector<EntInf> fila;

	for (int i = 1; i <= n; ++i)
	{
		fila.clear();
		for (int j = 1; j <= m; ++j) {	//No ponemos <= porque tenemos una columna extra que no queremos rellenar

			p[i][j] = max({ p[i - 1][j - 1], p[i - 1][j], p[i - 1][j + 1] }) + tablero[i - 1][j - 1];
			fila.push_back(p[i][j]);
		}
	}

	//Vemos que casilla es la de mayor puntuacion
	EntInf max = 0;
	int index = 0;
	for (int i = 0; i < fila.size(); i++) {
		if (fila[i] > max) {
			max = fila[i];
			index = i;
		}
	}

	return {max, index};
}

void resuelveCaso() {
	// leer los datos de la entrada

	int N;
	cin >> N;

	//Lo creo sumando 1 para que sea igual a la que vamos a usar en la programación dinámica
	//Además así puedo hacer una calle en horizontal y en vertical invalida para no tratar 
	//Las primeras de forma diferente
	Matriz<int> tablero(N, N, 0);
	int p;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {

			cin >> p;
			tablero[i][j] = p;
		}
	}

	pair<EntInf, int> sol = puntuacion(tablero);
	//Sumamos 1 para que no empiece en 0
	cout << sol.first << " " << sol.second + 1 << '\n';
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
