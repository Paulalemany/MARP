
/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
using namespace std;

#include "PriorityQueue.h"

/*@ <answer>

 Para la solución utilizamos una cola de prioridad de mínimos porque
 al sumar los valores más pequeños de los datos obtenemos el esfuerzo menor
 consiguiendo asi de forma sencilla el resultado. 
 Además guardamos la suma del esfuerzo en una variable para devolverla al final de forma eficiente

 La complejidad de este método sería de O(n log n) debido a que es la complejidad más alta que hay en el método
 (Por los pop de la cola)

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

long long sumaMinEsf(PriorityQueue<long long> cola) {

	long long a, b;
	long long sum = 0;

	while (cola.size() > 1) {
		//Cargamos los datos que vamos a sumar
		a = cola.top(); cola.pop();
		b = cola.top(); cola.pop();

		//Guardamos el resultado de la suma
		sum += a + b;
		cola.push(a + b);
	}

	return sum;
	
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int N;
	cin >> N;

	if (N == 0)
		return false;

	long long dato;
	PriorityQueue<long long> cola;
	for (int i = 0; i < N; i++) {
		cin >> dato;
		cola.push(dato);
	}

	cout << sumaMinEsf(cola) << '\n';

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
