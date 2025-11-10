
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
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

struct intervalo {
	int c, f;
};

bool resuelveCaso() {
	// leer los datos de la entrada
	int C, F, N;
	cin >> C >> F >> N;

	if (C + F + N == 0)
		return false;

	vector<intervalo> inter;
	int c, f;
	for (int i = 0; i < N; i++) {
		cin >> c >> f;
		inter.push_back({ c,f });
	}

	//Ordenamos los intervalos de menor a mayor fin
	sort(inter.begin(), inter.end(), [](const intervalo& a, const intervalo& b) {
		return a.f < b.f;
	});

	int tareas = 0;
	int posicion = C;	//Posición de finalización de la última tarea asignada

	//minimo va a hacer falta 1 a no ser que sea imposible
	//Es F - 1 porque el intervalo del final es abierto
	int i = 0;
	if (!inter.empty()) {
		if (inter.size() == 1 && inter[0].c < C && inter[0].f >= F - 1) {
			//Si solo hay una tarea comprobamos si cubre el intervalo
			//Si no cubre el intervalo entero es imposible
			tareas++;
			posicion = inter[0].f;
		}
		else {
			while (i < inter.size() - 1 && posicion < F) {
				if (inter[i + 1].c > posicion) {	//Si el siguiente se pasa nos quedamos con el actual
					tareas++;
					posicion = inter[i].f;
				}
				i++;
			}

			//Como mira hasta el -1 habría que procesar el último caso de ser necesario
			if (posicion < F && inter[i].c == posicion) {	//añadimos la tarea
				tareas++;
				posicion = inter[i].f;
			}
		}
	}

	// escribir la solución
	if (posicion < F) cout << "Imposible\n";
	else cout << tareas << '\n';

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
