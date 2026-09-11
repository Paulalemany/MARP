
/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;


/*@ <answer>

 Este es un problema de programación dinámica un poco extraño porque se resuelve
 en un vector y no en una matriz

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Estado {
	int beneficio;
	bool usada;
	int anterior;
};

bool resuelveCaso() {
	// leer los datos de la entrada
	int N, S;
	cin >> N >> S;

	if (!std::cin)  // fin de la entrada
		return false;

	vector<int> tiendas;
	vector<int> beneficio;
	int dato;
	for (int i = 0; i < N * 2; i++) {
		cin >> dato;
		if (i < N)
			tiendas.push_back(dato);	//Guardamos la posicion de la tienda
		else
			beneficio.push_back(dato); //Guardamos el beneficio de la tienda
	}

	// resolver el caso posiblemente llamando a otras funciones
	//Guarda un pair de beneficio maximo - componentes de la solucion
	vector<Estado> sol(N+1);
	sol[0].beneficio = 0;
	for (int i = 1; i <= N; i++) {
		int limite = tiendas[i - 1] - S;

		// Busca el primer elemento > limite
		auto it = std::upper_bound(tiendas.begin(), tiendas.end(), limite);

		// El índice válido es justo el anterior a ese iterador
		int k = it - tiendas.begin() - 1;  // -1 porque queremos el de ANTES

		if (k == -1) k = 0;
		else k++;

		int noUsar = sol[i - 1].beneficio;
		int usar = sol[k].beneficio + beneficio[i - 1];

		if (noUsar > usar) { //No se usa la tienda
			sol[i].beneficio = sol[i - 1].beneficio;
			sol[i].usada = false;
			sol[i].anterior = i - 1;
		}
		else {
			sol[i].beneficio = usar;
			sol[i].usada = true;
			sol[i].anterior = k;
		}
	}

	// reconstruimos la solución
	int i = N;
	vector<int> elegidos; //Para colocarlos en orden

	while (i > 0) {
		if (sol[i].usada) 
			elegidos.push_back(tiendas[i - 1]);
		i = sol[i].anterior;
	}

	cout << sol[N].beneficio << ":";

	for (int j = elegidos.size() - 1; j >= 0; j--) {
		cout << " " << elegidos[j];
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
