
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class Subir {
private:
	int N;
	vector<vector<int>> MaxSum;

	bool inMap(const int x, const int y) {
		//Si las coordenadas están dentro de los límites es válida
		return x < N && x >= 0 && y < N && y >= 0;
	}

	int Avanzar(const vector<vector<int>>& Mapa, const int x, const int y) {

		//Tenemos que ver si la coordenada es válida
		if (inMap(x, y)) {
			//Si MaxSum != -1 es que no tenemos calculado el max sum de esa casilla
			if (MaxSum[x][y] == -1) {
				if (x == 0) {
					//Estamos en la última fila, no podemos seguir avanzando
					return MaxSum[x][y] = Mapa[x][y];
				}
				else {
					//Nos quedamos con el máximo entre las 3 opciones que tenemos
					return MaxSum[x][y] =
						max({ Avanzar(Mapa, x - 1, y - 1), Avanzar(Mapa, x - 1, y), Avanzar(Mapa, x - 1, y + 1) })
						+ Mapa[x][y];
				}
			}
			else return MaxSum[x][y];
		}
		else return -1;
	}

public:

	Subir(vector<vector<int>>& Mapa) 
		: N(Mapa.size()), MaxSum(Mapa.size(), std::vector<int>(Mapa.size(), -1)) {

		//Hay que hacer esto con toda la última fila
		for (int i = N; i > 0; i--) {
			Avanzar(Mapa, N - 1, i - 1);
		}
	}

	pair<int,int> maxFila() {

		//Devolvemos la suma más alta entre los últimos elementos
		int maxS = -1;
		int indice = -1;

		for (int i = 0; i < N; i++) {

			if (MaxSum[N - 1][i] > maxS) {
				maxS = MaxSum[N - 1][i];
				indice = i;
			}
		}
		return { maxS, indice };
	}
};



bool resuelveCaso() {
	// leer los datos de la entrada
	int N;
	cin >> N;

	if (!std::cin)  // fin de la entrada
		return false;

	vector<vector<int>> Mapa;
	vector<int> linea;
	int d;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> d;
			linea.push_back(d);
		}
		Mapa.push_back(linea);
		linea.clear();
	}

	Subir mejorCasilla(Mapa);

	//Escribimos la solución
	pair<int, int> sol = mejorCasilla.maxFila();
	cout << sol.first << " " << sol.second + 1 << '\n';

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
