
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
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


struct usuario {
	int id = 0;		//Identificador del usuario
	int per = 0;	//Intervalo de tiempo que quiere las noticias
	int mom = 0;	//Tiempo que falta para mandarles actualización

	//El mom se irá actualizando en cada it restandole el transcurrido (per) pera saber cuanto le queda a cada 1)
};

bool operator<(const usuario& a, const usuario& b) {
		return a.mom < b.mom ||
			((a.mom == b.mom) && (a.id < b.id)) ;
}


bool resuelveCaso() {

	// leer los datos de la entrada
	int N;
	cin >> N;

	if (N == 0)
		return false;

	int idnt, p;
	usuario user;
	PriorityQueue<usuario> cola;

	for (int i = 0; i < N; i++) {

		cin >> idnt >> p;
		user.id = idnt;
		user.per = user.mom = p;

		cola.push(user);
	}

	int M;	//Numero de posiciones que tenemos que decir

	cin >> M;
	
	for (int i = 0; i < M; i++) {

		cout << cola.top().id << '\n';	//Escribimos el prioritario

		user = cola.top(); 
		cola.pop();

		user.mom += user.per;	//Usamos el tiempo absoluto

		cola.push(user);	
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
