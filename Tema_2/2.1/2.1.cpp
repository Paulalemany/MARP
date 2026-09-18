
/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

/*@ <answer>

 Para resolver este ejercicio se ha utilizado una cola de prioridad
 para poder coger el menor elemento de la suma en cada iteración ya
 que esto es lo que hace que el coste de sumarlos sea menor.

 La función coge los dos menores valores y los suma en cada iteración,
 vuelve a guardarlo en la cola para terminar la suma y va guardando en una
 variable el coste total de cada suma realizada.

 El coste de esta función está en el orden de O(M log N) Siendo N el numero
 de elementos de la cola y M la cantidad de pares totales de la suma.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

long long int CosteSuma(priority_queue<long long int, vector<long long int>, greater<long long int>> numeros) {

	if (numeros.size() < 2)
		return 0;

	long long int x, y;
	long long int sol = 0;
	while (numeros.size() > 1) {

		x = numeros.top();
		numeros.pop(); //O(log N)
		y = numeros.top();
		numeros.pop();

		sol += x + y;
		numeros.push(x + y); //O(log N)
	}

	return sol;
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int N;
	cin >> N;

	if (N == 0)
		return false;

	//Para que sea una cola de prioridad de minimos
	priority_queue<long long int, vector<long long int>, greater<long long int>> numeros;

	int dato;
	for (int i = 0; i < N; i++) {
		cin >> dato;
		numeros.push(dato);
	}

	cout << CosteSuma(numeros) << '\n';

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
