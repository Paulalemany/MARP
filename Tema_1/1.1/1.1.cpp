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
bool AVL(BinTree <U> tree, int& alt, U& min, U& max) {

	//Caso base arbol vacío (Es una hoja)
	if (tree.empty()) return true; 

	int altIzq = 0, altDer = 0;	//Para comprobar que está equilibrado
	U maxIzq = tree.root(), minIzq = tree.root();
	U maxDer = tree.root(), minDer = tree.root();

	min = max = tree.root();

	if (tree.left().empty() && tree.right().empty()) 
	{
		alt++;
		return true;
	}
	
	//En caso de que no sea vacío miramos si los hijos son AVL
	if (!tree.left().empty()) {
		if(!AVL(tree.left(), altIzq, minIzq, maxIzq)) return false;
		if (maxIzq >= tree.root()) return false; // debe ser estrictamente menor
		min = minIzq;
	}
	if (!tree.right().empty()) {
		if(!AVL(tree.right(), altDer, minDer, maxDer)) return false;
		if (minDer <= tree.root()) return false; // debe ser estrictamente mayor
		max = maxDer;
	}

	//Para recuperar el nivel en el que estámos
	if (altDer > altIzq) alt = altDer;
	else alt = altIzq;
	alt++;

	return ((altIzq - altDer <= 1) && (altIzq - altDer >= -1) //Se cumple la condicion de las alturas niveladas
		&&(minDer >= tree.root() && maxIzq <= tree.root())); //Condición de que está ordenado
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
		int min, max;
		if (tree.empty()) min = 0, max = 0;
		else min = tree.root(), max = tree.root();	//Para comprobar que está ordenado
		sol = AVL(tree, alt, min, max);
 	}
	else if (tipo == 'P') {
		BinTree <string> tree = read_tree<string>(std::cin); //Lee un árbol de palabras
		string min, max;
		if (tree.empty()) min = "", max = "";
		else string min = tree.root(), max = tree.root();	//Para comprobar que está ordenado
		sol = AVL(tree, alt, min, max);
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
