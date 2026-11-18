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

 tiros(i, j) = Número de tiros necesarios para alcanzar la suma j con los sectores hasta i

 Casos base:
	tiros(i, 0) = 0		-> Para alcanzar la suma 0 necesitamos 0 tiros
	tiros(0, j) = INF	-> Es imposible sumar j sin sectores 

 Recursión:
 si es el valor del sector
 tiros(i,j) =
	tiros (i-1, j)	si si > j;
	min (tiros (i-1, j), tiros(i, j - si) + 1)	si si <= j;

 Llamada inicial:
 tiros(S, V) siendo S los sectores que tenemos y V el valor a sumar

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

EntInf tiros(vector<int> const& S, int V)
{
	int n = S.size();
	Matriz<EntInf> sectores(n + 1, V + 1, Infinito);

	sectores[0][0] = 0;

	for (int i = 1; i <= n; ++i)
	{
		sectores[i][0] = 0;
		for (int j = 1; j <= V; ++j)
			if (S[i - 1] > j) {
				sectores[i][j] = sectores[i - 1][j];
			}
			else {
				sectores[i][j] = min(sectores[i - 1][j], sectores[i][j - S[i - 1]] + 1);
			}
	}
	return sectores[n][V];
}

vector<int> devolver_puntuacion(vector<int> const& S, int V) 
{
	int n = S.size();
	Matriz<EntInf> sectores(n + 1, V + 1, Infinito);

	sectores[0][0] = 0;

	for (int i = 1; i <= n; ++i)
	{
		sectores[i][0] = 0;
		for (int j = 1; j <= V; ++j)
			if (S[i - 1] > j) {
				sectores[i][j] = sectores[i - 1][j];
			}
			else {
				sectores[i][j] = min(sectores[i - 1][j], sectores[i][j - S[i - 1]] + 1);
			}
	}

	vector<int> sol; 
	
	if (sectores[n][V] != Infinito) 
	{ 
		int i = n, j = V; 
		while (j > 0) //No hemos llegado a la puntuación 
		{ 
			if (S[i-1] <= j && sectores[i][j] != sectores[i-1][j]) // un dardo va al sector i
			{ 
				 sol.push_back(S[i-1]); 
				 j = j - S[i-1]; 
			} 
			else // no van más dardos a este sector
				--i; 
		} 
	} 
	return sol; 
}



void resuelveCaso() {
	// leer los datos de la entrada

	int V, S;
	cin >> V >> S;

	vector<int> Sectores;
	int s;
	for (int i = 0; i < S; i++) {
		cin >> s;
		Sectores.push_back(s);
	}

	// resolver el caso posiblemente llamando a otras funciones
	EntInf t = tiros(Sectores, V);

	// escribir la solución

	if (t != Infinito) {
		//Reconstruimos la solución de ser posible
		cout << t << ":";

		vector<int> p = devolver_puntuacion(Sectores, V);

		for(auto const& s : p)
			cout << " " << s;
		
	}
	else
		cout << "Imposible";
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
