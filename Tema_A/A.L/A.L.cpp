
/*@ <authors>
 *
 * Paula, Alemany, (MARP01).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "EnterosInf.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Para resolver este problema utilizamos programación dináminca. 
 El caso base sería tener una moneda o billete exactamente del precio a pagar,
 la recursión sería tener que sumar diferentes monedas/billetes para llegar al coste.

 Guardamos una tanto las formas que tenemos de pagar una cantidad 
 como lo minimo que utilizamos para poder pagar esa cantidad. Como podemos pasarnos,
 en este caso el máximo de los vectores debe ser la cantidad máxima que podemos pagar con lo que tenemos.

 Una vez tenemos todo esto rellenamos la tabla de los datos (Aprovechamos y relenamos ambas a la vez)
 esto tendría un coste de N * max, siendo N el número de monedas/billetes que tenemos y max la cantidad maxima que podemos pagar

 //Con las tablas completadas sacamos la solución, primero nuestro caso base: 
 Si tenemos una manera de pagar la cantidad exacta pagamos eso.
 Si no tenemos manera de pagar la cantidad exacta buscamos el precio superior más cercano que podemos pagar
 y damos ese como solución. Esta búsqueda tendría una complejidad lineal de p - C, siendo p el precio que sí podemos pagar
 y C el precio original.

 Como el enunciado asegura que el maximo da para pagar el coste no hacemos ninguna comprobación más, en el caso peor 
 habrá que pagar con todo lo que tenemos.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class CambioExacto {
private:

	int N;		//numero de monedas que tenemos
	int C;		//precio a pagar
	int sum;	//Cuanto llevamos pagado
	vector<int> formas;			//Cuantas maneras hay de obtener lo mínimo después de C
	pair<int, EntInf> sol;		//Solución


public:

	CambioExacto(vector<int>& cartera, int N, int C) :
		N(N), C(C), sum(0), formas((N + 1), 0) {

		//El máximo que podemos pagar es el sumatorio de lo que llevamos en la cartera
		int max = 0;
		for (auto& n : cartera) max += n;

		vector<EntInf> minMonedas(max + 1, Infinito);
		vector<int> formas(max + 1, 0);

		

		//Rellenamos la primera fila/columna
		minMonedas[0] = 0;
		formas[0] = 1;

		for (int i = 1; i <= N; ++i) {
			int c = cartera[i - 1];
			for (int j = c; j <= max; ++j) {	//Esto puede que no sea así porque nos podemos pasar
				minMonedas[j] = min(minMonedas[j], minMonedas[j - cartera[i - 1]] + 1);
				formas[j] += formas[j - c];
			}
		}

		//Hacemos la solución
		 //caso base podemos pagar justo lo necesario
		if (formas[C] != 0) {
			sol.first = C;	//Pagamos justo lo necesario
			sol.second = minMonedas[C];		// Con el mínimo de monedas
		}
		else {

			//Vemos cual es el precio mínimo a pagar más cercano a C
			int i = C;

			while (formas[i] == 0) i++;

			//Nos quedamos con la primera manera que se pueda pagar
			sol.first = i;
			sol.second = minMonedas[i];
		}
		
	}

	void EscribirSol() {
		cout << sol.first << " " << sol.second << '\n';
	}
};

bool resuelveCaso() {
	// leer los datos de la entrada

	int C, N;
	cin >> C >> N;

	if (!std::cin)  // fin de la entrada
		return false;

	int d;
	vector<int> cartera;

	for (int i = 0; i < N; i++) {
		cin >> d;
		cartera.push_back(d);
	}

	CambioExacto ce(cartera, N, C);
	ce.EscribirSol();
	

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
