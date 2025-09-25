
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
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


struct paciente {
	string nombre = "";		//Nombre del paciente
	int gravedad = 0;		//Gravedad del caso
	int espera = 0;			//Tiempo que lleva esperando
};

bool operator<(const paciente& a, const paciente& b) {
	return a.gravedad > b.gravedad ||
		((a.gravedad == b.gravedad) && (a.espera < b.espera));	
	//El que tenga la espera más baja se atiende primero porque es como el turno de llegada
}


bool resuelveCaso() {

	// leer los datos de la entrada
	int N;
	cin >> N;

	if (N == 0)
		return false;
	char Action;
	PriorityQueue<paciente> cola;
	paciente paciente;
	string nombre;
	int prioridad;
	int cont = 0;
	
	for (int i = 0; i < N; i++) {
		cin >> Action;	//Leemos la acción a proceder

		if (Action == 'A') {	//Toca atender a un paciente

			cont++;
			cout << cola.top().nombre << '\n';
			cola.pop();
		}
		else if (Action == 'I') {	//Llega nuevo ingreso
			cin >> nombre >> prioridad;

			paciente.nombre = nombre;
			paciente.gravedad = prioridad;
			paciente.espera = cont;

			cola.push(paciente);
		}
		else throw("Acción no contemplada");
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
