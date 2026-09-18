
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

struct caja {
	int num;	//Numero de la caja (empieza en 1)
	int t;		//Tiempo de espera de la caja
};

bool operator<(caja const& a, caja const& b) {
	return b.t < a.t ||
		(a.t == b.t && b.num < a.num);
}

bool operator>(caja const& a, caja const& b) {
	return b < a;
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int N, C;

	cin >> N >> C;

	if (N == 0 && C == 0)
		return false;

	// resolver el caso posiblemente llamando a otras funciones
	priority_queue<caja> fila;

	for (int i = 0; i < N; i++) {
		fila.push({ i + 1, 0 });	//Todas las cajas empiezan con tiempo 0
	}

	//Vamos viendo los clientes
	int cliente;
	for (int i = 0; i < C; i++) {
		cin >> cliente;

		caja act = fila.top(); fila.pop();
		act.t += cliente;
		fila.push(act);
	}

	// escribir la solución
	cout << fila.top().num << "\n";

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
