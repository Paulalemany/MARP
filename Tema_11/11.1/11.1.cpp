/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "Matriz.h"

/*@ <answer>

 Para resolver este problema utilizaremos programación dinámica descendente.
 El objetivo es maximizar la cantidad de oro que podemos recuperar, para ello
 utilizamos la siguiente función:

 tesoros(i,j) = Máxima cantidad de oro recuperada con j de oxígeno y considerando
	los cofres del 1 al i.

 Casos recursivos:
					tesoros(i-1, j) si 3pi > j
 tesoros(i,j) =		max(tesoros(i-1, j), tesoros(i-1, j-3pi) + vi) si 3pi <= j

 Siendo pi el oxigeno que se gasta para bajar a por el cofre (3pi porque se gasta pi en bajar y 2pi en subir)
 y vi el valor del cofre i.

 Casos básicos:
 tesoros(0,j) = 0	tesoros(i,0) = 0

 Llamada inicial:
 tesoros(N, T)

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Cofre { int profundidad; int valor; };
struct Solucion {
	int max;
	int num;
	vector<Cofre> cof;
};

int tesoros_rec(vector<Cofre> const& cofres, int i, int j, Matriz<int>& botin) 
{
	if (botin[i][j] != -1) // subproblema ya resuelto 
		return botin[i][j]; 
	
	if (i == 0 || j == 0) 
		botin[i][j] = 0; 
	else if (cofres[i-1].profundidad * 3 > j) 
		botin[i][j] = tesoros_rec(cofres, i-1, j, botin); 
	else 
		botin[i][j] = max(tesoros_rec(cofres, i-1, j, botin), 
						  tesoros_rec(cofres, i-1, j - cofres[i-1].profundidad * 3, botin) + cofres[i-1].valor);
	
	return botin[i][j];
}

int tesoros(vector<Cofre> const& cofres, int T, Solucion& sol) {
	int n = cofres.size(); 
	Matriz<int> botin(n + 1, T + 1, -1); 

	sol.max = tesoros_rec(cofres, n, T, botin); 
	
	// cálculo de los objetos
	int i = n, j = T; 
	
	vector<bool> s(n, false); 
	
	while (i > 0 && j > 0) 
	{ 
		if (botin[i][j] != botin[i-1][j]) 
		{ 
			s[i-1] = true; 
			j = j - cofres[i-1].profundidad*3; 
			sol.num++;
			sol.cof.push_back({ cofres[i - 1] });
		}
		--i;
	} 
	
	return sol.max;
}

void resuelveCaso() {
	// leer los datos de la entrada
	int T, N;
	cin >> T >> N;

	vector<Cofre> cofres;
	int p, v;
	for (int i = 0; i < N; i++) {
		cin >> p >> v;
		cofres.push_back({ p, v });
	}

	// resolver el caso posiblemente llamando a otras funciones
	Solucion sol = { 0, 0 };
	cout << tesoros(cofres, T, sol) << '\n' <<
		sol.num << '\n';

	for (int i = sol.num - 1; i >= 0; i--) {
		cout << sol.cof[i].profundidad << " " << sol.cof[i].valor << '\n';
	}

	// escribir la solución
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
