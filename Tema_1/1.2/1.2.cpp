
/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
using namespace std;

#include "TreeSet_AVL.h" 

/*@ <answer>

 Primero para añadir la variable tam_i se ha modificado la función inserta de manera que
 al añadir un nuevo elemento o equilibrar el arbol se modifica este valor sin necesidad de recorridos,
 por lo tanto este no ha variado su complejidad.

 Ahora, para hacer el kesimo primero se ha hecho una función pública (kesim) para que se pueda hacer la primera llamada de
 la recursión, después la función interna (kesimo) lo que hace es comparar el valor que estamos buscando con el tam_i de
 la raiz actual:
	- Si k < tam_i el valor se encuentra en el hijo izquierdo
	- Si k > tam_i el valor se encuentra en el hijo derecho, en este caso para que nos siga valiendo 
	la misma función restamos a k el tam_i de la raiz actual para que no tenga esos nodos en cuenta.
	Acabaremos llegando al nodo deseado (si existe) o en su defecto a un arbol vacío lo cual significa 
	que el elemento que buscamos no existe.

Este algoritmo tiene una complejidad de O(log N), es decir que se van a hacer en el caso peor tantas iteraciones
como altura del arbol.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {
	// leer los datos de la entrada
	int N = 0;
	cin >> N;

	if (N == 0)
		return false;
	
	int dato = 0;
	Set <int> arbol;
	for (int i = 0; i < N; i++) {
		cin >> dato;
		arbol.insert(dato);
	}

	int M = 0;
	int sol = 0;
	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> dato;

		try {
			sol = arbol.kesim(dato);
			cout << sol << '\n';
		}
		catch (domain_error&) {
			cout << "??\n";
		}
	}

	cout << "---\n";

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
