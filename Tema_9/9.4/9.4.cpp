
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <deque>
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
	int P, S;
	cin >> P >> S;

	if (!std::cin)  // fin de la entrada
		return false;

	//Leemos los datos de los pesos de las personas 
	// y los ordenamos de menor peso a mayor
	int peso;
	priority_queue<int> ordenar;
	deque<int> personas;
	for (int i = 0; i < S; i++) {
		cin >> peso;
		ordenar.push(peso);
	}

	//Pasamos las personas ordenadas a la deque
	while (!ordenar.empty()) {
		personas.push_front(ordenar.top());
		ordenar.pop();
	}

	int sillas = 0;		//Sillas que estan siendo utilizadas
	while (!personas.empty()) {
		//Comprobamos si la persona que más pesa ocupa una silla ella sola
		if (personas.back() == P) {
			sillas++;
			personas.pop_back();
		}
		else if (personas.size() > 1 && personas.front() + personas.back() <= P) {
			//Esas personas ocupan una silla
			sillas++;
			personas.pop_front();
			personas.pop_back();
		}
		else {	 
			//Si esas dos personas se pasan quiere decir que la persona que más pesa
			//De las dos ya no podrá subirse acompañada ya que todas las personas que quedan
			//Pesa más que la pareja con la que se le compara
			//Esa persona va sola
			sillas++;
			personas.pop_back();
		}
	}

	cout << sillas << '\n';

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
