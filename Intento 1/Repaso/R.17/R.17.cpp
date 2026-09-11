
/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

/*@ <answer>

 Nos encontramos ante un problema que puede resolverse mediante un algoritmo voraz
 El algortimo hace lo siguiente:
 Con los precios de los libros ordenados de mayor a menor lo que buscamos es aprovechar
 el descuento con los libros más caros, por lo tanto si compramos los libros más caros juntos
 de 3 en 3 regalarán el 3er libro más caro.

 El coste es de O(n log n) siendo n el numero de libros que se quieren comprar
 (Por la funcion sort)

 Este algoritmo funciona debido a diferentes motivos:
 1. El libro más caro de todos nunca va a poder ser el regalado 
 ya que se regala el más barato de cada grupo.
 2. Para conseguir el mayor descuento posible debemos agruparlo con los 2
 siguientes más caros consiguiendo asi un descuento con el 3er libro más caro.
 3. Este mismo argumento se replica con los libros restantes.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {
	// leer los datos de la entrada
	int L;

	cin >> L;

	if (!std::cin)  // fin de la entrada
		return false;

	vector<int> libros;
	int dato;
	for (int i = 0; i < L; i++) {
		cin >> dato;
		libros.push_back(dato);
	}

	//Ordenamos el vector y lo recorremos
	sort(libros.begin(), libros.end(), greater<int>());

	int maxDes = 0;
	int i = 0;
	//Vamos de 3 en 3 para aprovechar el descuento
	while (i + 2 < L) {
		i += 2;	//Indice con el que termina el grupo
		maxDes += libros[i];
		i++;
	}

	// escribir la solución
	cout << maxDes << '\n';

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
