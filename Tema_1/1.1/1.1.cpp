/*@ <authors>
 *
 * Paula, Alemany Rodríguez.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
 //#include <...>

using namespace std;

#include "TreeSet_AVL.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {

	char tipo;
	cin >> tipo;

	if (!std::cin)  // fin de la entrada
		return false;

	//if (tipo == 'N') 
	//	//TreeNode<char> tree = new TreeNode();
	//	//bintree<char> tree = leerArbol('.');	//Lee un árbol numérico
	//else if (tipo == 'P') 
		//bintree<string> tree = leerArbol(string("."));	//Lee un árbol de palabras
	
	// resolver el caso posiblemente llamando a otras funciones

	// escribir la solución

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
