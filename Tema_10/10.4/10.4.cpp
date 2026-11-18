/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

using namespace std;

#include "EnterosInf.h"
#include "Matriz.h"

/*@ <answer>

 Restricciones:
	Andar lo mínimo posible
	Evitar las obras

 i,j -> Posición a llegar desde 1,1

 formas(i, j) = formas de llegar al cruce i,j satisfaciendo las restricciones

 Casos base:
	formas(i, j) = 0		-> Si la casilla tiene obras no se puede ir por ella
	formas(1, 1) = 1		-> La casilla de inicio tiene una forma de llegar a ella

 Recursión:
 formas(i,j) = formas(i-1, j) + formas(i, j-1);
	-> Tomamos solo estas dos opciones porque andar lo mínimo es siempre ir hacia abajo o derecha.
	Por lo tanto para llegar a la casilla actual hemos tenido que venir o de la izquierda
	o de arriba.

 Llamada inicial:
 formas(n, m) siendo n,m la posición de la esquina sureste de la ciudad

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

EntInf formas(Matriz<char> const& ciudad)
{
	int n = ciudad.numfils();
	int m = ciudad.numcols();
	Matriz<EntInf> f(n, m, 0);

	for (int i = 1; i < n; ++i)
	{
		for (int j = 1; j < m; ++j) {

			if (i == 1 && j == 1)
				f[i][j] = 1;
			else if (ciudad[i][j] == 'X') { //Estamos en una obra
				f[i][j] = 0;
			}
			else {
				f[i][j] = f[i - 1][j] + f[i][j - 1];
			}
		}
	}
	return f[n-1][m-1];
}

void resuelveCaso() {
	// leer los datos de la entrada

	int N, M;
	cin >> N >> M;

	//Lo creo sumando 1 para que sea igual a la que vamos a usar en la programación dinámica
	//Además así puedo hacer una calle en horizontal y en vertical invalida para no tratar 
	//Las primeras de forma diferente
	Matriz<char> ciudad(N + 1, M + 1, 'X');
	char c;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {

			cin >> c;
			ciudad[i][j] = c;
		}
	}

	cout << formas(ciudad) << '\n';
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
