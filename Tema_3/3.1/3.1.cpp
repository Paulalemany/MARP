
/*@ <authors>
 *
 * Paula, Alemany Rodriguez (MARP01).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
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

bool resuelveCaso() {
	// leer los datos de la entrada
	int p, n;

	cin >> p >> n;

	if (p == 0 && n == 0)
		return false;

	// Todos los hijos izquierdos de la bandada 
	// (Debe estar ordenador de menor a mayor para que el mas prioritario
	// Sea el siguiente que puede acabar en la punta)
	priority_queue<int> izq;	

	// Todos los hijos derechos de la bandada 
	// (Debe estar ordenador de mayor a menor para que el mas prioritario
	// Sea el siguiente que puede acabar en la punta)
	priority_queue<int, vector<int>, greater<int>> der;

	int centro = p;	//Pico

	int par1, par2;

	for (int i = 0; i < n; i++) {

		//LLega una pareja
		cin >> par1 >> par2;

		//Primero colocamos en su respectiva cola
		if (par1 < centro)
			izq.push(par1);
		else
			der.push(par1);

		if (par2 < centro)
			izq.push(par2);
		else
			der.push(par2);

		//Vemos si hace falta cambiar el centro
		if (izq.size() < der.size()) {	//Si hay menos elementos en la izquierda nivelamos

			izq.push(centro);
			centro = der.top(); der.pop();
		}
		else if (izq.size() > der.size()) {

			der.push(centro);
			centro = izq.top(); izq.pop();
		}

		//En otro caso no hace falta cambiarlo
		cout << centro << " ";
	}

	cout << '\n';

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
