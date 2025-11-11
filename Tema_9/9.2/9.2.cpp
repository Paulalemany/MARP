
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
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

struct intervalo {
	int c, f;
};

class compare {

public:
	bool operator() (intervalo a, intervalo b) {
		return a.c > b.c;
	}
};



bool resuelveCaso() {
	// leer los datos de la entrada
	int C, F, N;
	cin >> C >> F >> N;

	if (C + F + N == 0)
		return false;

	priority_queue<intervalo, vector<intervalo>, compare> intervalos;
	int c, f;
	for (int i = 0; i < N; i++) {
		cin >> c >> f;
		intervalos.push({ c,f });
	}

	int tareas = 0;
	intervalo mejor;
	mejor.c = -1;
	mejor.f = -1;
	int posicion = C;	//Posición de finalización de la última tarea asignada
	bool posible = true;

	//Hacemos F-1 porque el intervalo es cerrado al final
	//si posicion == F - 1 ya no hace falta comprobar más
	while (posible && !intervalos.empty() && posicion < F) {
		//Miramos el primer intervalo y comprobamos si cubre el principio del intervalo general
		if (intervalos.top().c <= posicion) {	//El intervalo es potencialmente bueno
			if (intervalos.top().f > mejor.f) {	//sustituimos el mejor por el nuevo mejor
				mejor.c = intervalos.top().c;
				mejor.f = intervalos.top().f;
			}
			//Si no es mejor pasamos
		}
		else {	//El intervalo que estamos mirando se pasa del punto que queremos cubrir

			//Guardamos el intervalo mejor y continuamos a partir de ahí
			posible = mejor.c != -1;	//Si alguno de los dos puntos es -1 es que no se ha actualizado y no es posible
			posicion = mejor.f;
			mejor.c = intervalos.top().c;
			mejor.f = intervalos.top().f;
			posible = mejor.c <= posicion;
			if (posible) tareas++;
		}

		intervalos.pop();
	}

	//El último intervalo no se gestiona asi que lo hacemos aparte
	//Ponemos F - 1 porque eso significa que no ha llegado al final 
	if (posible && posicion < F && mejor.f >= F) {
		tareas++;
		posicion = mejor.f;
	}

	// escribir la solución
	// F - 1 porque eso significa que no ha llegado al final
	if (tareas == 0 || posicion < F) cout << "Imposible\n";
	else cout << tareas << '\n';

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
