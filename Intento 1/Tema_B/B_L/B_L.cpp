/*@ <authors>
 *
 * Paula Alemany Rodriguez MARP01
 * Ines Primo Lopez MARP52
 *
 *@ </authors> */

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>


using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

*** CASO RECURSIVO ***
playlist con las canciones coincidentes en el mismo orden de ambas playlist

					// si la cancion en playlist1 es igual a la de playlist 2, se
					// guarda la cancion en la solucion y se avanza en ambas playlists
				 |	playlist(i+1, j+1)			si playlist1[i] == playlist2[j]
playlist(i, j) = |
				 |	max(size(playlist(i+1, j)),	si playlist1[i] != playlist2[j]
						size(playlist(i, j+1))
						)
					// si la cancion es distinta en ambas playlists, se compara la
					// solucion que devuelve si probamos con una posicion mas en i y
					// una posicion mas en j y cogemos el resultado mas largo

*** CASOS BASE ***
// si o i o j llegan al final del vector, se devuelve nada
playlist(i, size(playlist2)) = vector vacio
playlist(size(playlist1), j) = vector vacio

! marcamos un caso no resuelto con un vector con su primera posicion con un '*'

*** LLAMADA INICIAL ***
// llamada inicial con los indices de playlist1 y playlist 2
playlist(0, 0)

*** MATRIZ ***
Matriz de tamaño [playlist1.size()+1, playlist2.size()+1] que rellenamos de forma descendente

*** COSTE ***
El coste esta en O(playlist1.size() * playlist2.size()) tanto en tiempo como en espacio adicional

@ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

class PlayList {
public:
	PlayList(const vector<string>& playlist1, const vector<string>& playlist2)
		: playlist1(playlist1), playlist2(playlist2) {
		// matriz de vectores de string inicializadas a vectores vacios
		matriz = Matriz<int>(playlist1.size() + 1, playlist2.size() + 1, -1);	//Inicializamos a -1

		playlist(0, 0);

	}

	//Reconstruimos la solución
	vector<string> getSol() {

		vector<string> sol;

		//Vamos viendo con que canciones nos quedamos
		int i = 0, j = 0;

		while (i < playlist1.size() && j < playlist2.size()) {

			//Si son iguales guardamos la canción y aumentamos ambos indices
			if (playlist1[i] == playlist2[j]) {
				sol.push_back(playlist1[i]);
				i++;
				j++;
			}
			//Si es una mejor opción incrementar la primera playlist
			else if (matriz[i + 1][j] > matriz[i][j + 1]) {
				i++;
			}
			else j++;
		}

		return sol;
	}

private:
	vector<string> playlist1;
	vector<string> playlist2;
	Matriz<int> matriz;

	int playlist(int i, int j) {
		int& res = matriz[i][j];

		// si res esta vacio es porque la solucion ya ha sido calculada (no hay solucion)
		if (res == 0) return res;
		// si no se ha mirado la solucion en esta posicion aun 
		if (res == -1) {
			// casos base: si cualquiera de los indices llega al maximo, devuelve un vector vacio
			if (i >= playlist1.size() || j >= playlist2.size())
				return 0;
			// si ambas canciones son iguales
			if (playlist1[i] == playlist2[j]) {

				res = playlist(i + 1, j + 1);
				res++;	//Ponemos las que teniamos antes mas la que tenemos ahora
				return res;
			}
			// si ambas canciones son distintas
			else {
				//
				int a = playlist(i + 1, j);
				int b = playlist(i, j + 1);
				res = max_playlist(a, b);
				return res;
			}
		}
		return res;
	}

	int max_playlist(int a, int b) {
		if (a > b)
			return a;
		else
			return b;
	}
};


bool resuelveCaso() {
	// leer los datos de la entrada

	string aux;
	vector<string> playlist1;
	vector<string> playlist2;

	if (!std::cin)  // fin de la entrada
		return false;

	char a = ' ';
	string word = "";

	// lee las dos playlists
	a = cin.get();
	while (a != '\n') {
		if (a != ' ')
			word.push_back(a);
		else {
			playlist1.push_back(word);
			word.clear();
		}
		a = cin.get();
	}
	playlist1.push_back(word);
	word.clear();

	a = cin.get();
	while (a != '\n' && std::cin) {
		if (a != ' ')
			word.push_back(a);
		else {
			playlist2.push_back(word);
			word.clear();
		}
		a = cin.get();
	}
	playlist2.push_back(word);
	word.clear();

	// resolver el caso posiblemente llamando a otras funciones
	PlayList pl(playlist1, playlist2);
	vector<string> sol = pl.getSol();

	// escribir la solución
	for (int i = 0; i < sol.size(); i++)
		cout << sol[i] << " ";
	cout << "\n";

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
