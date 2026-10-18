/*@ <authors>
 *
 * Paula. Alemany Rodríguez (MARP01).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

#include "ConjuntosDisjuntos.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

using Mapa = vector<string>; // grafo implícito en el mapa 

class Manchas { 
public: 
	Manchas(Mapa const& M) 
		: F(M.size()), C(M[0].size()), maxim(0), visit(F, vector<bool>(C, false)), mancha(F*C)
	{ 

		//Recorremos todo el mapa
		for (int i = 0; i < F; ++i) 
		{ 
			for (int j = 0; j < C; ++j) 
			{ 
				//Si hay un # es un nuevo conjunto
				if (!visit[i][j] && M[i][j] == '#') { // se recorre una nueva mancha 
					
					dfs(M, i, j); 
					Nmaximo(i * C + j);
				} 
			} 
		} 
	}

	void unir(Mapa const& M, int i, int j) {

		//Llega una nueva mancha, vemos si hay que unirla con alguna actual
		for (auto d : dirs) {
			int ni = i + d.first, nj = j + d.second;
			if (correcta(ni, nj) && M[ni][nj] == '#') {

				//Unimos este vertice al conjunto
				int nodoV = i * C + j;
				int nodoW = ni * C + nj;
				mancha.unir(nodoV, nodoW);
			}
		}
		
	}

	int Nmaximo(int nuevo) { 
		maxim = max(maxim, mancha.cardinal(nuevo));
		return maxim;
	}

	int maximo() const {
		return maxim;
	}

private: 
	int F, C; // tamaño del mapa 
	int maxim;
	vector<vector<bool>> visit; // visit[i][j] = se ha visitado el píxel <i,j>? 
	ConjuntosDisjuntos mancha;
	vector<int> padres;


	bool correcta(int i, int j) const { 
		return 0 <= i && i < F && 0 <= j && j < C;
	}

	const vector<pair<int, int>> dirs = { {1,0},{0,1},{-1,0},{0,-1}, {1,1}, {1, -1}, {-1,-1}, {-1,1}};
	
	void dfs(Mapa const& M, int i, int j) {
		visit[i][j] = true; 
		for (auto d : dirs) 
		{
			int ni = i + d.first, nj = j + d.second;
			if (correcta(ni, nj) && M[ni][nj] == '#' && !visit[ni][nj]) {
				
				//Unimos este vertice al conjunto
				int nodoV = i * C + j;
				int nodoW = ni * C + nj;

				mancha.unir(nodoV, nodoW);
				dfs(M, ni, nj); 
			} 
		} 
	}
};

void resuelveCaso() {
	int F, C; 
	
	cin >> F >> C; // número de filas y columnas 
	
	Mapa mapa(F); 
	
	// leemos la imagen 
	for (string & linea : mapa) 
		cin >> linea; 
	
	// la analizamos 
	int N;
	cin >> N;

	
	Manchas manchas(mapa); //Primera situacion
	cout << manchas.maximo() << ' ';

	//Nueva mancha
	int f, c;
	for (int i = 0; i < N; i++) {

		cin >> f >> c;
		mapa[f - 1][c - 1] = '#';
		manchas.unir(mapa, f - 1, c - 1);

		int nodo = (f - 1) * C + (c - 1);
		cout << manchas.Nmaximo(nodo) << ' ';
	}

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
