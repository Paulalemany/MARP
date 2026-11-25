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
#include "EnterosInf.h"

/*@ <answer>

 Para resolver este problema utilizaremos programación dinámica descendente.
 El objetivo es minimizar el número de letras necesarias para formar un palíndromo, para ello
 utilizamos la siguiente función:

 aibofobia(i,j) = Mínimo número de letras que hacen falta añadir con las letras [i...j]

 Casos recursivos:
					aibofobia (i-1, j+1)		si ai[i] == ai[j]
 aibofobia(i,j) =	min(aibofobia(i-1, j), 
						aibofobia(i, j+1)) + 1	si ai[i] != ai[j]

 Siendo ai[] la letra a revisar.

 Casos básicos:
 aibofobia(i,j) = 0 si i = j -> Si solo hay una letra ya es un palíndromo
 Inicializamos a 0

 Llamada inicial:
 Colocamos la i y la j en el centro de la palabra

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

EntInf aibofobia_rec(string const& palabra, Matriz<EntInf>& aibo, int i, int j)
{ 
	EntInf& res = aibo[i][j]; 
	
	if (res == Infinito) //No hemos calculado la respuesta aun
	{  
		if (i >= j) 
			res = 0; 
		else if (palabra[i] == palabra[j]) 
			res = aibofobia_rec(palabra, aibo, i + 1, j - 1);
		else 
			res = min(aibofobia_rec(palabra, aibo, i+1, j), aibofobia_rec(palabra, aibo, i, j - 1)) + 1;
	}
	return res;
}

string reconstruir(string const& palabra, Matriz<EntInf> const& aibo, int i, int j)
{ 
	if (i > j) return "";

	if (i == j)
		return {palabra[i]};
	
	if (palabra[i] == palabra[j])
		return palabra[i] + reconstruir(palabra, aibo, i + 1, j - 1) + palabra[j];
	
	else if (aibo[i + 1][j] <= aibo[i][j-1]) 
		return palabra[i] + reconstruir(palabra, aibo, i + 1, j) + palabra[i];
	
	else 
		return palabra[j] + reconstruir(palabra, aibo, i, j - 1) + palabra[j];
}

void resuelveCaso() {
	// leer los datos de la entrada
	string palabra;
	cin >> palabra;

	int n = palabra.length();

	Matriz<EntInf> aibo(n, n, Infinito);

	cout << aibofobia_rec(palabra, aibo, 0, n-1) << " " << reconstruir(palabra, aibo, 0, n-1) << '\n';
	
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
