/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

using namespace std;

#include "EnterosInf.h"
#include "Matriz.h"

/*@ <answer>

 Objetivo:
	Pagar lo mínimo posible con la menor cantidad de billetes/monedas posible

 precio(i, j) = Precio mínimo para pagar j con monedas hasta tipo i
 minM(i, j) = Número mínimo de monedas para pagar precio j con monedas hasta i

 Casos base:
	precio(0, j) = INF	-> Es imposible alcanzar el precio j sin monedas
	precio(i, 0) = 0	-> Para alcanzar el precio 0 el minimo precio es 0

	minM(0,j) = INF		-> Es imposible alcanzar el precio j sin monedas
	minM(i,0) = 0		-> Para alcanzar el precio 0 hacen falta 0 monedas

 Recursión:
	precio(i,j) = min(precio(i-1, j), precio(i-1, j-pi) + pi)
	minM(i,j) = min(minN(i-1, j), minN(i-1, j - Monedas[i - 1] + 1);

 Llamada inicial:
 precio(P, N) siendo P el precio a pagar y N la cantidad de monedas y billetes
 minN(Pmin, N) siendo Pmin el precio minimo que podemos pagars

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int inf = 1000000000;

int minCost(vector<int> const& Monedas, int P, int sum)
{
	int n = Monedas.size();
	vector<int> precio(sum + 1, inf);

	precio[0] = 0;

	for (int i = 1; i <= n; ++i)
	{
		for (int j = sum; j >= Monedas[i - 1]; --j) {
			precio[j] = min(precio[j], precio[j - Monedas[i - 1]] + Monedas[i - 1]);
		}

	}

	int i = P;
	if (precio[i] == inf) { 

		//No podemos pagar el precio justo, buscamos el precio más bajo superior
		
		while (P <= sum && precio[i] == inf)
			i++;
	}

	return precio[i];
}

int minNum(vector<int> const& Monedas, int P)
{
	int n = Monedas.size();
	vector<int> minN(P + 1, inf);

	minN[0] = 0;

	for (int i = 1; i <= n; ++i)
	{
		for (int j = P; j >= Monedas[i - 1]; --j) {
			minN[j] = min(minN[j], minN[j - Monedas[i - 1]] + 1);
		}

	}
	return minN[P];
}

void resuelveCaso() {
	// leer los datos de la entrada

	int P, N;
	cin >> P >> N;

	vector<int> monedas;
	int p;
	int sum = 0;
	for (int i = 0; i < N; i++) {
			cin >> p;
			monedas.push_back(p);
			sum += p;
	}

	sort(monedas.begin(), monedas.end());

	//Sumamos 1 para que no empiece en 0
	int mCost = minCost(monedas, P, sum);
	cout <<  mCost << " " << minNum(monedas, mCost) << '\n';
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
