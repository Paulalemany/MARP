/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

#include "Matriz.h"

/*@ <answer>

 Para resolver este problema vamos a hacer uno de la programación dinámica descendente.
 
 Objetivo:
	Maximizar el número de canciones de la lista teniendo en cuenta las restricciones.
 
 Restricciones:
	- No se admitirán en la lista final ninguna canción que no hayan incluido en las suyas.
	- Las canciones deben aparecer en el mismo orden en el que aparecían en su lista.

 La función lista_rec(i,j) representa:
	lista_rec(i,j) = Máximo número de canciones que podemos poner en común con la primera lista
	hasta i y la segunda lista hasta j.

 La funcion lista(i,j) reconstruye la solución para darnos la playlist en orden

 Recursión:
				 lista(i+1, j+1) + 1				si CA[i] == CB[j]
	lista(i,j) =  
				 max(lista(i+1, j), lista(i, j+1))	si CA[i] != CB[j]
	Siendo CA la lista de canciones de la mañana y CB la lista de canciones de tarde

 Casos base:
	lista(i,j) = 0 si i >= CA.size() || j >= CB.size()

 Llamada inicial:
	lista(0,0)

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int lista_rec(vector<string> const& l1, vector<string> const& l2, int i, int j, Matriz<int>& playlist) {

	if (i >= l1.size() || j >= l2.size()) return 0;

	int& res = playlist[i][j];
	if (res == -1) {
		if (l1[i] == l2[j])
			res = lista_rec(l1, l2, i + 1, j + 1, playlist) + 1;
		else
			res = max(lista_rec(l1, l2, i + 1, j, playlist),
					  lista_rec(l1, l2, i, j + 1, playlist));
	}
	return res;
}

string lista(vector<string> const& l1, vector<string> const& l2, Matriz<int> const& playlist, int i, int j) {
	
	if(i >= l1.size() || j >= l2.size()) return {};

	if (l1[i] == l2[j]) //Como empezamos desde el final añadimos la palabra al principio
		return l1[i] + " " + lista(l1, l2, playlist, i + 1, j + 1);	
	else if (i + 1 < l1.size() && playlist[i][j] == playlist[i + 1][j])
		return lista(l1,l2, playlist, i + 1, j);
	else
		return lista(l1,l2, playlist, i, j + 1);
}

void resuelveCaso() {
	// leer los datos de la entrada
	string linea1;
	while(linea1.empty())
		getline(std::cin, linea1);
	istringstream iss(linea1);
	vector<string> manana;
	string c;
	while (iss >> c)
		manana.push_back(c);


	string linea2;
	getline(std::cin, linea2);
	iss = istringstream(linea2);
	vector<string> tarde;
	while (iss >> c)
		tarde.push_back(c);

	// resolver el caso posiblemente llamando a otras funciones
	Matriz<int> playlist(manana.size(), tarde.size(), -1);
	lista_rec(manana, tarde, 0, 0, playlist);

	// escribir la solución
	cout << lista(manana, tarde, playlist, 0, 0) << '\n';
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
