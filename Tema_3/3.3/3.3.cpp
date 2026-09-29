/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

#include "IndexPQ.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct tarea {
	int c;
	int f;
	int p;
	int id;
};

bool operator<(tarea const& a, tarea const& b){
	return b.c < a.c ||
	(b.c == a.c && b.f < a.f);
}

bool operator>(tarea const& a, tarea const& b){
	return b < a;
}

void resuelveCaso() {
	// leer los datos de la entrada

	int N, M, T;

	cin >> N >> M >> T;

	IndexPQ<int, tarea, greater<tarea>> tareas;

	// Tareas unicas
	int c, f, p;
	for (int i = 0; i < N; i++){
		cin >> c >> f;

		tareas.push(i, {c, f, 0, i});
	}

	// Tareas periódicas
	for (int i = 0; i < M; i++){
		cin >> c >> f >> p;
		tareas.push(N + i, {c, f, p, N + i});
	}

	// resolver el caso posiblemente llamando a otras funciones
	bool solapamiento = false;

	int t = 0;
	while (tareas.size() > 1 && !solapamiento && t < T){

		tarea act = tareas.top().prioridad; 

		// Si la tarea es periodica la acrualizamos
		if (act.p != 0 && act.c + act.p < T)
			tareas.update(act.id, {act.c + act.p, act.f + act.p, act.p, act.id});
		else
			tareas.pop();

		// Vemos si la siguiente tarea solapa
		int comienzo = tareas.top().prioridad.c;
		solapamiento = act.f >= comienzo;

		t++;
	}

	// escribir la solución
	if (solapamiento)
		cout << "SI\n";
	else
		cout << "NO\n";
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

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

// para dejar todo como estaba al principio y parar antes de salir
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	std::cout << "Pulsa Intro para salir..." << std::flush;
	std::cin.get();
#endif

	return 0;
}