/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#include "IndexPQ.h"

/*@ <answer>

 Para resolver este ejercicio se ha hecho uso de una cola de prioridad por indices y del algoritmo heapsort para la solución
 Primero la cola de prioridad va guardando cual es el canal con mas audiencia en cada momento
 Al ir actualizando la audiencia si el canal que estaba en el top cambia por otro le sumamos a este su prime time
 Una vez terminadas todas las actualizaciones le sumamos el primeTime final al ultimo canal en estar en top 1.
 El coste de esto esta en el orden O(N * U * log(C)) Siendo N el numero de actualizaciones, U el numero de canales que se 
 modifican en cada actualización y log(C) el coste de cada update de la cola de prioridad (C es el numero de canales que hay).

 Tras esto se prepara la solución, para ello guardamos los canales en un vector que ordenamos por heapsort (Por tener ya todos
 los elementos desde el princio) según el primeTime, los canales con mayor PrimeTime van primero.
 Por ello escribir la solución tiene un coste de O(C log C) ya que tenemos que recorrer todos los canales para guardarlos
 en el vector y después ordenarlos. 

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct canal {
	int id;
	int audiencia;
	int primeTime;
};


bool operator<(canal const& a, canal const& b) {
	return b.audiencia < a.audiencia;
}

struct solucion {
	int id;
	int primeTime;
};

bool operator<(solucion const& a, solucion const& b) {
	return b.primeTime < a.primeTime ||
		(b.primeTime == a.primeTime && a.id < b.id);
}
 
void heapSortSTL(vector<solucion>& v) {
	std::make_heap(v.begin(), v.end()); // Construir Max Heap
	std::sort_heap(v.begin(), v.end()); // Ordenar el heap
}

void resuelveCaso() {
	// leer los datos de la entrada
	int D, C, N;
	cin >> D >> C >> N;

	// El elemento es el nombre del canal
	IndexPQ<int, canal> canales;

	int audiencia;
	for (int i = 0; i < C; i++) {

		cin >> audiencia;
		canales.push(i + 1, { i+1, audiencia, 0 });
	}

	// resolver el caso posiblemente llamando a otras funciones
	int t = 0;
	int m, u;
	for (int i = 0; i < N; i++) {

		//Sumarle el tiempo de prime time al canal que iba en cabeza
		cin >> m >> u;
		canal top = canales.top().prioridad;

		//Canales que se actualizan
		int c, a;
		for (int j = 0; j < u; j++) {

			cin >> c >> a;
			canales.update(c,
				{
					c,
					a,
					canales.priority(c).primeTime
				});
		}

		if (top.id != canales.top().elem) {	//Ha cambiado el canal en cabeza, sumamos el primeTime

			t = m - t;	//Tiempo de primeTime a sumar
			top = canales.priority(top.id);
			canales.update(top.id, {
			top.id,
			top.audiencia, 
			top.primeTime += t	//Sumamos el tiempo hasta este instante
			});	//La audiencia se ha cambiado anteriormente

			t = m;	//Actualizamos t al ultimo instante
		}
	}

	//Sumamos el primeTime restante al canal que este en cabeza
	canal top = canales.top().prioridad;
	t = D - t;
	canales.update(canales.top().elem, {
			top.id,
			top.audiencia, //La audiencia se ha cambiado anteriormente
			top.primeTime += t,	//Sumamos el tiempo hasta este instante
			});	
	t = D;	//Actualizamos t al ultimo instante

	// escribir la solución
	//Toca ordenar por prime Time
	vector<solucion> sol;

	for (int i = 0; i < C; i++) {
		sol.push_back({ canales.top().elem, canales.top().prioridad.primeTime });
		canales.pop();
	}

	heapSortSTL(sol);

	size_t i = 0;
	while (i < sol.size() && sol[i].primeTime > 0) {

		cout << sol[i].id << " " << sol[i].primeTime << '\n';
		i++;
	}

	cout << "---\n";
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
