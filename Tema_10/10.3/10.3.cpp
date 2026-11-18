/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

using namespace std;

#include "EnterosInf.h"
#include "Matriz.h"

/*@ <answer>

 Restricciones:
	Andar lo mínimo posible
	Evitar las obras

 i,j -> Posición a llegar desde 1,1

 formas(i, j) = formas de llegar al cruce i,j satisfaciendo las restricciones

 Casos base:
	formas(i, j) = 0		-> Si la casilla tiene obras no se puede ir por ella
	formas(1, 1) = 1		-> La casilla de inicio tiene una forma de llegar a ella

 Recursión:
 formas(i,j) = formas(i-1, j) + formas(i, j-1);
	-> Tomamos solo estas dos opciones porque andar lo mínimo es siempre ir hacia abajo o derecha.
	Por lo tanto para llegar a la casilla actual hemos tenido que venir o de la izquierda
	o de arriba.

 Llamada inicial:
 formas(n, m) siendo n,m la posición de la esquina sureste de la ciudad

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


long long formas(vector<int> const& cordeles, int L)
{
	int n = cordeles.size(); 
	vector<long long> form(L + 1, 0);
	form[0] = 1; 
	
	for (int i = 1; i <= n; ++i) 
	{
		for (int j = L; j >= cordeles[i-1]; --j) {
				form[j] = form[j] + form[j - cordeles[i - 1]];
		}
	}
	return form[L];
}

EntInf minNum(vector<int> const& cordeles, int L)
{
	int n = cordeles.size();
	vector<EntInf> minN(L + 1, Infinito);

	minN[0] = 0;

	for (int i = 1; i <= n; ++i)
	{
		for (int j = L; j >= cordeles[i-1]; --j) {
			minN[j] = min(minN[j], minN[j - cordeles[i - 1]] + 1);
		}

	}
	return minN[L];
}

EntInf minCost(vector<int> const& cordeles, vector<int> const& precio, int L)
{
	int n = cordeles.size();
	vector<EntInf> minN(L + 1, Infinito);

	minN[0] = 0;

	for (int i = 1; i <= n; ++i)
	{
		for (int j = L; j >= cordeles[i-1]; --j) {
			minN[j] = min(minN[j], minN[j - cordeles[i - 1]] + precio[i - 1]);
		}

	}
	return minN[L];
}


void resuelveCaso() {
	// leer los datos de la entrada

	int N, L;
	cin >> N >> L;

	//Lo creo sumando 1 para que sea igual a la que vamos a usar en la programación dinámica
	//Además así puedo hacer una calle en horizontal y en vertical invalida para no tratar 
	//Las primeras de forma diferente
	vector<int> cordeles;
	vector<int> precio;
	int c, p;
	for (int i = 1; i <= N; i++) {
		cin >> c >> p;
		cordeles.push_back(c);
		precio.push_back(p);
	}

	long long form = formas(cordeles, L);
	if (form > 0) {

		EntInf minN = minNum(cordeles, L);
		EntInf minC = minCost(cordeles, precio, L);
		cout << "SI " << form << " " << minN << " " << minC << '\n';
	}
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
