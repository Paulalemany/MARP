
/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <stack>
#include <vector>

using namespace std;

#include "PriorityQueue.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
struct elem {
	int num;
	int pila;
};

bool operator<(const elem& a, const elem& b) {

	return a.num < b.num;
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int N, K, dato, min = 0;
	vector<stack<elem>> pilas;
	PriorityQueue<elem> mejores;

	cin >> N;

	for (int i = 0; i < N; i++) {
		stack<elem> pila;
		cin >> K;

		for (int j = 0; j < K; j++) {
			cin >> dato;
			if (dato < min || min == 0) min = dato;
			pila.push({ dato, i });
		}
		pilas.push_back(pila);
	}

	if (!std::cin)  // fin de la entrada
		return false;

	// resolver el caso posiblemente llamando a otras funciones

	//Guardamos el primer elemento de cada stack en la cola
	for (int i = 0; i < N; i++) {
		mejores.push(pilas[i].top());
		//Eliminamos el elemento
		pilas[i].pop();
	}

	int cont = 1;	//Para ver cuando se saca el bueno
	int pila;

	while (mejores.top().num != min) {

		//Eliminamos el de la cima y volvemos a guardar la pila con el resto
		pila = mejores.top().pila;
		mejores.pop();
		if (!pilas[pila].empty()) {	//Si se termina una pila ya no añadimos más de ahí
			mejores.push(pilas[pila].top());
			pilas[pila].pop();
		}
		cont++;
	}


	// escribir la solución
	cout << cont << '\n';

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
