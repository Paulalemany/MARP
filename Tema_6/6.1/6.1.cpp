
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

using namespace std;

#include "ConjuntosDisjuntos.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

using Mapa = vector<string>;	//Para guardar el mapa

class manchas2 {
private:
	vector<char> manchas;
	vector<bool> visitado;
	int F;
	int C;
	int max;
	ConjuntosDisjuntos mancha;

	//Comprobamos si la posición es válida
	bool correcta(int i, int j) const {
		return 0 <= i && i < F && 0 <= j && j < C;
	}

	int Pos(int i, int j) {
		return C * (i + 1) - (C - j);
	}

public:

	manchas2(Mapa const& map, int F, int C) : manchas(F*C, ' '), visitado(F*C, false), 
		F (F), C(C), max(0), mancha(F*C) {

		//Tenemos que recorrer todo el mapa
		for (int i = 0; i < map.size(); i++) {
			for (int j = 0; j < map[i].size(); j++) {

				//Calculamos la posición en los vectores
				int pos = Pos(i, j);
			
				if (!visitado[pos] && map[i][j] == '#') {	//La posición está manchada
					//Empezamos una búsqueda de como de grande es esa mancha
					buscarMancha(pos, i, j, mancha, map);

					//Debemos guardarnos la cabecera de la mancha y cuantos tiene
					int a = mancha.cardinal(mancha.buscar(pos));
					if (a > max) max = a;
					
				}

			}
		}

		cout << max << " ";
	}

	//Vector de direcciones a comprobar (Horizontal, Vertical y Diagonal)
	const vector<pair<int, int>> dirs = { {1,0}, {0,1}, {-1,0}, {0,-1}, {1,1}, {-1, -1}, {-1,1}, {1,-1} };

	void buscarMancha(int pos, int x, int y, ConjuntosDisjuntos& manchas, Mapa const& map) {
		//Miramos si hay manchas en las posiciones adyacentes
		visitado[pos] = true;	//Marcamos la posición como visitada

		for (auto d : dirs) {

			//Para sacar la nueva posición primero actualizamos las coordenadas
			int nx = x + d.first;
			int ny = y + d.second;

			int pos2 = Pos(nx, ny);

			if (correcta(nx, ny) && !visitado[pos2] && map[nx][ny] == '#') {
				//Si tiene una mancha y es una posición válida unimos y avanzamos
				manchas.unir(pos, pos2);

				//Seguimos investigando la mancha
				buscarMancha(pos2, nx, ny, manchas, map);
			}
			
			
		}
	}

	void actualizarMancha(int x, int y, Mapa& map) {

		//Actualizamos la posición en el mapa
		map[x][y] = '#';

		//Calculamos la posición
		int pos = Pos(x,y);

		//Vemos si tiene manchas adyacentes
		for (auto d : dirs) {
			//Para sacar la nueva posición primero actualizamos las coordenadas
			int nx = x + d.first;
			int ny = y + d.second;

			int pos2 = Pos(nx, ny);
			//Si se une con alguna mancha lo marcamos
			if (correcta(nx, ny) && map[nx][ny] == '#') mancha.unir(pos, pos2);
		
		}

		//Vemos si el nuevo tamaño de esta mancha es mayor al actual
		int a = mancha.cardinal(mancha.buscar(pos));
		if (a > max) max = a;

		cout << max << " ";
	}
};

bool resuelveCaso() {
	// leer los datos de la entrada
	int F, C;
	cin >> F >> C;

	if (!std::cin)  // fin de la entrada
		return false;

	//Primero habrá que crear el mapa
	Mapa map(F);

	//Leemos el mapa
	for (string& linea : map) 
		cin >> linea;
	

	// Creamos el estado inicial
	manchas2 m(map, F, C);

	int N;
	cin >> N;

	int Fm, Cm;

	for (int i = 0; i < N; i++) {
		cin >> Fm >> Cm;
		m.actualizarMancha(Fm - 1, Cm - 1, map);
	}

	cout << '\n';

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
