
/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

#include "ConjuntosDisjuntos.h"

/*@ <answer>

 Estamos ante un problema que se puede solucionar mediante conjuntos disjuntos
 Cada grupo de amigos será un conjunto diferente por lo tanto
 para esparcir el rumor gastando lo menos posible habria que pagar a la persona
 del grupo que se venda más barata.

 Para ello la funcion menorPrecio recorre a todas las personas y va guardando 
 cual de cada conjunto es la más barata, al final suma el menor precio de cada conjunto
 siendo ese el resultado. Por ello el coste de este algoritmo es lineal respecto al numero de
 personas.
 O(n) siendo n el numero de personas

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int menorPrecio(const ConjuntosDisjuntos amigos, const vector<int> precio, const int n) {

	//Vector que guarda al menor de cada conjunto
	unordered_map<int, int>baratos; //<representante, precio>

	//Recorremos todos los valores
	for (int i = 0; i < n; i++) {

		//Si la clave ya existe nos quedamos con el más barato
		if (baratos.count(amigos.buscar(i)) == 1) {

			//El minimo del conjunto se elije entre 
			//el precio del que estamos viendo ahora y el minimo del conjunto guardado
			baratos[amigos.buscar(i)] = min(precio[i], baratos[amigos.buscar(i)]);
		}
		else 
			baratos.insert({ amigos.buscar(i), precio[i] });
	}

	//Sumamos todos los minimos
	int sum = 0;
	for (auto& par : baratos)
		sum += par.second;

	return sum;
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int N, M;
	cin >> N >> M;

	if (!std::cin)  // fin de la entrada
		return false;

	ConjuntosDisjuntos amigos(N);

	vector<int> precios;

	//Guardamos los precios
	int dato;
	for (int i = 0; i < N; i++)
	{
		cin >> dato;
		precios.push_back(dato);
	}

	//Rellenamos los conjuntos
	int a1, a2;
	for (int i = 0; i < M; i++) {
		cin >> a1 >> a2;
		amigos.unir(a1 - 1, a2 - 1);
	}

	cout << menorPrecio(amigos, precios, N) << '\n';

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
