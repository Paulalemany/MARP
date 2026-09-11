/*@ <authors>
 *
 * Paula, Alemany Rodriguez (MARP01)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "Matriz.h"  

/*@ <answer>

 Se trata de un problema de programación dinámica similar al de las monedas
 puede resolverse mediante programación dinámica ascendente

 Restricciones
 Hay que evitar duplicados y no importa el orden en el que esten los dados
 Para solucionar esto se suman siempre los dados de menor a mayor

 Tabla de programación dinámica
 i -> cara del dado
 j -> Suma a alcanzar
 dp[i][j] -> Número de maneras de alcanzar la suma j con caras de tipo i

 Casos base
 dp[i][0] -> Formas de sumar 0 = 1, no tirar ningún dado
 dp[0][j] j > 0 -> Formas de sumar J con 0 caras = 0, es imposible

 Recurrencia
 En el caso de dp[i][j] tenemos 2 opciones
 - NO usar la cara i -> dp[i][j] = dp[i-1][j]
 - Usar la cara i al menos una vez -> dp[i][j] = dp[i-1][j] + dp[i][j-i]

 El coste de esta solución sería en el orden O(K * S)
 siendo K el numero de caras del dado y S la suma que queremos alcanzar

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

// K -> Numero de caras del dado
// S -> Suma a alcanzar
int posiblesSumas(int K, int S) 
{  
	Matriz<int> suma(K + 1, S + 1, 0);

	//Casos base
	suma[0][0] = 1;

	for (int i = 1; i <= K; ++i) 
	{ 
		//Caso base
		suma[i][0] = 1; //No lanzar ningun dado 

		for (int j = 1; j <= S; ++j) 
			if (i > j) //Si la cara es mayor a la suma que falta 
				suma[i][j] = suma[i - 1][j]; //no usamos esa cara 
			else suma[i][j] = suma[i - 1][j] + suma[i][j - i]; 
	} 
	return suma[K][S]; 
}


void resuelveCaso() {
	// leer los datos de la entrada
	int K, S;

	cin >> K >> S;

	// resolver el caso posiblemente llamando a otras funciones
	cout << posiblesSumas(K, S) << '\n';
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
