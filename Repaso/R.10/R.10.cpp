
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

 Nos encontramos ante un problema que puede resolverse mediante un algoritmo voraz
 queremos que se repitan las sumas más pequeñas por lo que queremos sumar primero 
 los elementos más bajos, es decir, que compitan primero los equipos con menos seguidores.

 El algoritmo hace lo siguiente:
	Van "compitiendo" los dos equipos con menos seguidores, despues del partido
	se suman los seguidores y se quedan para el siguiente partido. La suma total se guarda aparte
	Esto continua hasta que solo queda un equipo en pie.

El coste de este algoritmo seria de O(n log N) siendo N el numero de equipos

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {
	// leer los datos de la entrada
	int N;

	cin >> N;

	if (N == 0)
		return false;

	// resolver el caso posiblemente llamando a otras funciones

	priority_queue<long long, vector<long long>, greater<long long>> seguidores;

	int d;
	for (int i = 0; i < N; i++) {
		cin >> d;
		seguidores.push(d);
	}

	long long sum = 0;

	while (seguidores.size() > 1) {

		long long equipo1 = seguidores.top();
		seguidores.pop();
		long long equipo2 = seguidores.top();
		seguidores.pop();

		sum += equipo1 + equipo2;

		seguidores.push(equipo1 + equipo2);
	}

	cout << sum << '\n';

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
