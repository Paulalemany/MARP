
/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

using namespace std;

#include "Grafo.h"  // propios o los de las estructuras de datos de clase


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

using Mapa = vector<string>;	//Grafo implicito en el mapa

class Manchas {
private:
	vector<vector<bool>> visit;	//Vector de nodos visitados visit[i][j]
	int F, C;			//Tamaño del mapa
	int num;			//Componentes conexas encontradas
	int maxim;			//Tamaño de la componente conexa mayor

	bool correcta(int i, int j) const {
		return 0 <= i && i < F && 0 <= j && j < C;
	}

public:
	Manchas(Mapa const& M) : F(M.size()), C(M[0].size()),
							 visit(F, vector<bool>(C, false)), num(0), maxim(0) {

		vector<vector<bool>> _visit(F, vector<bool>(C, false));
		visit = _visit;

		for (int i = 0; i < F; i++) {
			for (int j = 0; j < C; j++) {
				if (!visit[i][j] && M[i][j] == '#') {	//Nueva mancha
					num++;
					int nuevotam = dfs(M, i, j);	//Se supone que hay que pasarle los índices del vértice
					maxim = max(maxim, nuevotam);
				}
			}
		}
	}

	int numero() const { return num; }
	int maximo() const { return maxim; }

	const vector<pair<int, int>> dirs = { {1,0}, {0,1}, {-1,0}, {0,-1} };

	//Comprobamos si el grafo es conexo
	int dfs(Mapa const& M, int i, int j) {	//Recorrido en profundidad
		visit[i][j] = true;
		int tam = 1;

		//Comprobamos si hay más mancha en el resto de direcciones
		for (auto d : dirs) {
			int ni = i + d.first, nj = j + d.second;	//Cambiamos la coordenada del mapa
			//Si es una posición válida, tiene una mancha y no se ha visitado avanzamos
			if (correcta(ni, nj) && M[ni][nj] == '#' && !visit[ni][nj]) {	
				tam += dfs(M, ni, nj);
			}
		}
		return tam;
	}
};

bool resuelveCaso() {
	// leer los datos de la entrada
	int F, C;
	cin >> F >> C;

	if (!std::cin)  // fin de la entrada
		return false;

	Mapa mapa(F);

	//Leemos la imagen
	for (string& linea : mapa) {
		cin >> linea;
	}

	//La analizamos
	Manchas manchas(mapa);
	cout << manchas.numero() << " " << manchas.maximo() << '\n';

	
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
