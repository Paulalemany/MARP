
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

#include "Matriz.h"

/*@ <answer>

 Programacion dinámica descendente
 Restriccion
 Solo se puede coger de los extremos

 Traduccion
 sol[i][j] -> Máximos dias con la misma fruta en el fragmento de bizcocho i j
 i -> Extremo izquierdo del bizcocho
 j -> Extremo derecho del bizcocho

 casos base
 sol[i][j] = 0 si i >= j

 recursion
 coger 2 trozos izquierdos -> sol[i][j] = sol[i+2][j] + 1 si bizcocho[i] == bizcocho[i+1] && bizcocho[i] > 0
 coger 2 trozos derechos -> sol[i][j] = sol[i][j-2] + 1 si bizcocho[j] == bizcocho[j-1] && bizcocho[j] > 0
 coger 1 trozo por lado -> sol[i][j] = sol[i + 1][j-1] + 1 si bizcocho[i] == bizcocho[j] && bizcocho[j] > 0

 Primera llamada
 i = 0;
 j = N - 1 (Siendo N el numero de trozos)

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int diasMaximos(vector<int> const& bizcocho, int i, int j, Matriz<int>& sol) {

	//Si no queda suficiente bizcocho
	if (i >= j) 
		return 0;
	//Si ya hemos calculado ese caso
	if (sol[i][j] != -1) 
		return sol[i][j];

	//Coger dos trozos de la izquierda
	int izq = diasMaximos(bizcocho, i + 2, j, sol);
	if (bizcocho[i] == bizcocho[i + 1] && bizcocho[i] > 0) izq++;

	int der = diasMaximos(bizcocho, i, j - 2, sol);
	if (bizcocho[j] == bizcocho[j - 1] && bizcocho[j] > 0) der++;

	int par = diasMaximos(bizcocho, i + 1, j - 1, sol);
	if (bizcocho[i] == bizcocho[j] && bizcocho[i] > 0) par++;

	//Lo guardamos en la matriz y devolvemos
	sol[i][j] = max({ izq, der, par });
	return sol[i][j];
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int N;

	cin >> N;

	if (!std::cin)  // fin de la entrada
		return false;

	vector<int> bizcocho;
	int dato;
	for (int i = 0; i < N; i++) {
		cin >> dato;
		bizcocho.push_back(dato);
	}


	int i = 0;	//Extremo izquierdo del bizcocho
	int j = N - 1; //Extremo derecho del bizcocho
	Matriz<int> sol(N + 1, N + 1, -1);
	

	// escribir la solución
	cout << diasMaximos(bizcocho, i, j, sol) << "\n";

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
