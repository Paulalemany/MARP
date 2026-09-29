
/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

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

	int N, A, B;
	cin >> N >> A >> B;

	priority_queue<int> bateriaA;	//pilas de 9V
	int dato;

	for (int i = 0; i < A; i++) {
		cin >> dato;
		bateriaA.push(dato);
	}

	priority_queue<int> bateriaB;	//pilas de 9V

	for (int i = 0; i < B; i++) {
		cin >> dato;
		bateriaB.push(dato);
	}

	if (!std::cin)  // fin de la entrada
		return false;

	//Simulacion de los dias
	//Mientras queden pilas de ambos tipos
	while (!bateriaA.empty() && !bateriaB.empty()) {

		//Miramos por cada numero de drones que tenemos en un dia
		int vueloTotal = 0;
		int i = 0;
		vector<int> bateriasA;
		vector<int> bateriasB;

		// O(log A) siendo A el numero de baterias en la cola menor
		while (i < N && !bateriaA.empty() && !bateriaB.empty()) {

			//Vemos cuanto vuela el dron
			bateriasA.push_back(bateriaA.top()); bateriaA.pop();
			bateriasB.push_back(bateriaB.top()); bateriaB.pop();

			int horas = min(bateriasA[i], bateriasB[i]);
			vueloTotal += horas;

			bateriasA[i] -= horas;
			bateriasB[i] -= horas;

			i++;
		}

		//Escribimos el vuelo total del dia
		cout << vueloTotal << " ";
		
		//Añadimos las pilas que no se hayan gastado
		//Deberian ser de la misma longitud asi que da igual
		// O(j log j) Siendo j el numero de drones que han podido volar
		for (int j = 0; j < bateriasA.size(); j++) {

			if (bateriasA[j] > 0)
				bateriaA.push(bateriasA[j]);
			if (bateriasB[j] > 0)
				bateriaB.push(bateriasB[j]);
		}
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
