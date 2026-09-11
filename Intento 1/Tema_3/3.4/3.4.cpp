

#include <iostream>
#include <fstream>
#include <vector>
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

struct dron {
	int nV;
	int ucV;
	int menor;
};

bool operator<(const dron& a, const dron& b) {
	//Luego vemos cual de los menores es el menor
	return a.menor < b.menor;
}

bool resuelveCaso() {
	// leer los datos de la entrada

	int N, A, B;

	cin >> N >> A >> B;

	if (!std::cin)  // fin de la entrada
		return false;

	priority_queue<int> nueveV;
	priority_queue<int> unoConCincoV;

	int dato;

	for (int i = 0; i < A; i++) {
		cin >> dato;
		nueveV.push(dato);
	}

	for (int i = 0; i < B; i++) {
		cin >> dato;
		unoConCincoV.push(dato);
	}

	while (!nueveV.empty() && !unoConCincoV.empty()) {

		//Guardamos el estado de los drones al principio del dia
		priority_queue<dron> drones;
		dron dron;

		int j = 0;
		while (j < N && !nueveV.empty() && !unoConCincoV.empty()) {
			dron.nV = nueveV.top();
			nueveV.pop();
			dron.ucV = unoConCincoV.top();
			unoConCincoV.pop();

			if (dron.nV < dron.ucV) dron.menor = dron.nV;
			else dron.menor = dron.ucV;

			drones.push(dron);
			j++;
		}

		//Actualizamos las pilas al final del día
		//Cuando un dron se queda sin batería volvemos a guardar las pilas
		
		int t = 0;
		int n = drones.size();
		for (int i = 0; i < n; i++) {
			dron = drones.top();
			drones.pop();

			dron.nV -= dron.menor;
			dron.ucV -= dron.menor;
			t += dron.menor;

			if (dron.nV > 0) nueveV.push(dron.nV);
			if (dron.ucV > 0) unoConCincoV.push(dron.ucV);
		}

		cout << t << " ";
		
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
