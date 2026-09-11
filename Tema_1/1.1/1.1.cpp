
/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

using namespace std;

#include "bintree.h"

/*@ <answer>

 Para saber si un arbol es AVL debe cumplir dos condiciones:
	- Los elementos del hijo izquierdo deben ser menor que la raiz y los del hijo derecho deben ser mayores.
		Para comprobar si se cumple esta condicion se utiliza el inorden del arbol, si el resultado de este
		es ordenado de menor a mayor esta condicion se cumple.
		El coste de esta funcion es O(N) siendo N el numero de nodos del arbol ya que debemos recorrerlos todos si o si

	- El arbol debe estar equilibrado
		Para comprobar si el arbol esta equilibrado se ha realizado una funcion recursiva que comprueba que cada nodo
		esta equilibrado (Comparando la altura de ambos hijos y verificando que la diferencia es <= 1), en el momento
		en el que algun nodo no esta equilibrado el arbol no lo esta por lo que dejamos de buscar.
		El coste de esta funcion en el caso peor es de O(N) siendo N el numero de nodos del arbol.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


template <typename T>
bool Ordenado(BinTree<T> &tree) {
	bool ordenado = true;
	bool primero = true;
	T anterior;

	tree.inorder([&](const T& valor)
	{
		if (!primero && valor <= anterior)
			ordenado = false;

		anterior = valor;
		primero = false;
	});

	return ordenado;
}

template <typename T>
pair<bool, int> Equilibrado(BinTree<T> tree) {

	int alt = 0;
	//Si el arbol es vacio
	if (tree.empty())
		return { true, 0 };

	//Comprobamos de forma recursiva la altura de cada sub arbol
	//altura de sub arbol izquierdo - altura de subarbol derecho = +- 1 o 0
	pair<bool, int> hizq = { true, 0 };
	pair<bool, int> hder = { true, 0 };

	hizq = Equilibrado(tree.left());
	//Con que un subNodo este desequilibrado ya todo el arbol lo esta por lo que deberiamos dejar de buscar

	if (hizq.first) //Si esta equilibrado seguimos buscando
		hder = Equilibrado(tree.right());
	else
		return{ false, -1 };	//Si no esta equilibrado dejamos de buscars

	if (!hder.first)
		return{ false, -1 };



	alt = max(hizq.second, hder.second) + 1; //Por el nodo actual
	int sol = abs(hizq.second - hder.second);
	return { sol <= 1,  alt};	//Si esto se cumple el sub arbol esta equilibrado
}

template <typename T>
bool IsAVL(BinTree<T>& tree) {

	bool ordenado = Ordenado(tree);
	pair<bool, int> equilibrado = Equilibrado(tree);


	return ordenado && equilibrado.first;
}

bool resuelveCaso() {
	char tipo;
	cin >> tipo;

	if (!std::cin)  // fin de la entrada
		return false;

	bool sol = false;

	if (tipo == 'N') {
		BinTree <int> tree = read_tree<int>(std::cin); //Lee un árbol numérico	
		sol = IsAVL(tree);
	}
	else if (tipo == 'P') {
		BinTree <string> tree = read_tree<string>(std::cin); //Lee un árbol de palabras
		sol = IsAVL(tree);
	}

	if (sol)
		cout << "SI\n";
	else
		cout << "NO\n";

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
