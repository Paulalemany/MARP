
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

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct usuario {
	int id;		//Id del usuario
	int pAct;	//Tiempo en el que toca el envio
	int p;		//Periodo
};

bool operator<(usuario const& a, usuario const& b) {
	return b.pAct < a.pAct ||
		(b.pAct == a.pAct && b.id < a.id);
}

bool operator>(usuario const& a, usuario const& b) {
	return b < a;
}


bool resuelveCaso() {
	// leer los datos de la entrada
	int N;
	cin >> N;

	if (N == 0)
		return false;

	priority_queue<usuario> users;
	int id, p;

	for (int i = 0; i < N; i++) {
		cin >> id >> p;
		users.push({ id, p, p });
	}

	int k;
	cin >> k;

	for (int i = 0; i < k; i++) {
		usuario e = users.top();
		users.pop();

		//Escribimos el usuario
		cout << e.id << '\n';

		//Actualizamos su tiempo
		e.pAct += e.p;
		users.push(e);
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
