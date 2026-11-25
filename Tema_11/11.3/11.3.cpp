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
 El objetivo es maximizar los beneficios de la venta, para ello
 utilizamos la siguiente función:

 beneficio(i,j) = Máximo beneficio con el número de cajas j teniendo en cuenta los vecinos de 0 a i

 Casos recursivos:
					max(Beneficio(i-1, j -1) + b1	si j >= 1
 beneficio(i,j) =		Beneficio(i-1, j -2) + b2	si j >= 2
						Beneficio(i-1, j -3) + b3	si j >= 3
						Beneficio(i-1, j -4) + b4	si j >= 4

 Siendo bi lo que paga el vecino j por i numero de cajas

 Casos básicos:
 beneficio(0,j) = 0	beneficio(i,0) = 0

 Llamada inicial:
 beneficio(V, C)

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct ven {
	int beneficio;
	int numCajas;
};

ven beneficio_rec(Matriz<int> const& vecinos, int i, int j, Matriz<ven>& ben) 
{
	if (ben[i][j].beneficio != -1) // subproblema ya resuelto 
		return ben[i][j]; 
	
	if (i == 0 || j == 0) 
		ben[i][j] = { 0, 0 };
	else {

		int maxB = 0;
		int num = 0;
		for (int k = 0; k <= 4 && k <= j; k++) {
			
			ven benk = beneficio_rec(vecinos, i - 1, j - k, ben);
			if (benk.beneficio + vecinos[k][i] > maxB) {
				maxB = benk.beneficio + vecinos[k][i];
				num = k;
			}
		}
		
		ben[i][j] = { maxB, num };
	}

	return ben[i][j];
}

int beneficio(Matriz<int> const& vecinos, int C, vector<int>& sol) 
{
	int n = vecinos.numcols();	//Numero de vecinos que hay
	Matriz<ven> ben(n, C + 1, { -1, -1 });
	int valor = beneficio_rec(vecinos, n - 1, C, ben).beneficio; 
	// cálculo de los objetos 
	int i = n - 1, j = C; 
	
	sol = vector<int>(n - 1, 0); 
	while (i > 0 && j > 0) 
	{ 
		if (ben[i][j].beneficio != ben[i-1][j].beneficio) 
		{ 
			sol[i-1] = ben[i][j].numCajas;
			j = j - ben[i][j].numCajas; //Necesito la K tanto para ponerla en sol como para restarla aqui
		}
		--i;
	} 
	return valor; 
}

void resuelveCaso() {
	// leer los datos de la entrada
	int V, C;
	cin >> V >> C;

	Matriz<int> vecinos(5, V + 1, 0);	//Maximo 4 cajas por persona
	int p;
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= V; j++) {
			cin >> p;
			vecinos[i][j] = p;
		}
	}

	Matriz<int> ben(V + 1, C + 1, -1);
	vector<int> sol;

	cout << beneficio(vecinos, C, sol) << '\n';
	for (const auto v : sol)
		cout << v << " ";
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
