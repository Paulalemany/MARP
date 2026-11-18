/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
 //#include <...>

using namespace std;

#include "EnterosInf.h"
#include "Matriz.h"

/*@ <answer>

 formas(N, T) = formas de pagar la tarifa T con sellos de hasta tipo N

 Casos base:
	formas(i, 0) = 1 -> Solo hay 1 manera de pagar 0 (No poner ningun sello)
	formas(0, j) = 0 -> No hay ninguna manera de pagar j con 0 sellos

 Recursión
 mi es el valor del sello
 formas(i,j) = 
	formas(N-1, T)	si mi > T 
			-> Si el valor es mas alto que la tasa las formas de pagar es igual a las formas de pagar con el sello anterior
	formas(N-1, T) + formas(N, T - mi))	si mi <= T
			-> Sumamos las formas de llegar al monto si usamos el sello y si no usamos el sello

 Llamada inicial
 formas(N, T)

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

const int MOD = 1000000007;

pair<int, bool> formas(vector<int> const& N, int T) 
{
	int n = N.size(); 
	Matriz<int> sellos(n + 1, T + 1, 0);
	Matriz<bool> posible(n + 1, T + 1, false);

	for (int i = 1; i <= n; ++i) 
	{
		sellos[i][0] = 1; 
		posible[i][0] = true;
		for (int j = 1; j <= T; ++j) 
			if (N[i - 1] > j) {
				sellos[i][j] = sellos[i - 1][j]; 
				posible[i][j] = posible[i - 1][j];
			}
			else {
				sellos[i][j] = (sellos[i - 1][j] + sellos[i][j - N[i - 1]]) % MOD;
				posible[i][j] = posible[i - 1][j] || posible[i][j - N[i - 1]];
			}
	}
	return { sellos[n][T], posible[n][T] };
}

vector<int> devolver_forma(vector<int> const& N, int T) 
{
	// rellenar la matriz monedas como antes 
	int n = N.size();
	Matriz<bool> posible(n + 1, T + 1, false);

	for (int i = 1; i <= n; ++i)
	{
		posible[i][0] = true;
		for (int j = 1; j <= T; ++j)
			if (N[i - 1] > j) {
				posible[i][j] = posible[i - 1][j];
			}
			else {
				posible[i][j] = posible[i - 1][j] || posible[i][j - N[i - 1]];
			}
	}

	vector<int> sol; 
	
	if (posible[n][T])	//Si se puede pagar
	{
		int i = n, j = T; 
		while (j > 0) // no se ha pagado todo 
		{
			if (posible[i - 1][j])
				--i;
			else {
				sol.push_back(N[i - 1]);
				j = j - N[i - 1];
			}
			
		} 
	} 
	return sol; 
}

void resuelveCaso() {
	// leer los datos de la entrada

	int N, T;
	cin >> N >> T;

	vector<int> Sellos;
	int s;
	for (int i = 0; i < N; i++) {
		cin >> s;
		Sellos.push_back(s);
	}

	// resolver el caso posiblemente llamando a otras funciones
	pair f = formas(Sellos, T);

	// escribir la solución
	cout << f.first << '\n';

	if (f.second) {
		//Reconstruimos la solución de ser posible
		vector<int> sol = devolver_forma(Sellos, T);
		
		for (auto const& x : sol)
			cout << x << " ";
	}
	else
		cout << "NO HAY";
	cout << '\n';
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
