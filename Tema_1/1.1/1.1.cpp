/*@ <authors>
 *
 * Paula, Alemany Rodríguez.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "bintree.h";

using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

template <typename U>
bool AVL(BinTree <U> tree, int& alt) {

	//Caso base arbol vacío (Es una hoja)
	if (tree.empty() || tree.left().empty() && tree.right().empty()) return true;

	bool izq = true, der = true;
	int altIzq = 1, altDer = 1;	//Para comprobar que está equilibrado
	U min = tree.root(), max = tree.root();	//Para comprobar que está ordenado
	
	//En caso de que no sea vacío miramos si los hijos son AVL
	if (!tree.left().empty()) {
		altIzq++;
		izq = AVL(tree.left(), altIzq);
	}
	if (!tree.right().empty()) {
		altDer++;
		der = AVL(tree.right(), altDer);
	}
	//Debemos incrementar alt
	alt++;
	return ((altIzq - altDer <= 1) && (altIzq - altDer >= -1)); //Se cumple la condicion de las alturas niveladas
}

bool resuelveCaso() {

	char tipo;
	cin >> tipo;

	if (!std::cin)  // fin de la entrada
		return false;

	bool sol = false;
	int alt = 0;

	if (tipo == 'N') {
		BinTree <int> tree = read_tree<int>(std::cin); //Lee un árbol numérico	
		sol = AVL(tree, alt);
 	}
	else if (tipo == 'P') {
		BinTree <string> tree = read_tree<string>(std::cin); //Lee un árbol de palabras
		sol = AVL(tree, alt);
	}

	// escribir la solución
	if (sol) cout << "SI";
	else cout << "NO";

	cout << endl;

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
