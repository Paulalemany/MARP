
/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

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

using Mapa = vector<string>; // grafo implícito en el mapa 
class Manchas 
{ 
public: 
	Manchas(Mapa const& M) : F(M.size()), C(M[0].size()), 
		visit(F, vector<bool>(C, false)), num(0), numB(0)
	{ 
		for (int i = 0; i < F; ++i) 
		{ 
			for (int j = 0; j < C; ++j) 
			{ 
				if (!visit[i][j] && M[i][j] == 'X') 
				{ // se recorre una nueva oveja
					++num; 
					int nuevotam = dfs(M, i, j); 
				} 
			} 
		} 
	}

int numero() const { return num; } 
int blancas() const { return numB; } 
private: 
	int F, C; // tamaño de la foto 
	vector<vector<bool>> visit; // visit[i][j] = se ha visitado el píxel <i,j>? 
	int num; // número de ovejas
	int numB; //Numero de ovejas blancas
	bool correcta(int i, int j) const { 
		return 0 <= i && i < F && 0 <= j && j < C; 
	}

	bool pared(int i, int j) {
		return i == 0 || i == F-1 || j == 0 || j == C-1;
	}

	/*
	* Abajo -> 1,0
	* Derecha -> 0,1
	* Arriba -> -1,0
	* Izquierda -> 0, -1
	* 
	* Ponemos tambien las diagonales
	* abajo derecha -> 1,1
	* arriba derecha -> -1, 1
	* arriba izquierda -> -1, -1
	* abajo izquierda -> 1, -1
	*/
	const vector<pair<int, int>> dirs = { {1,0},{0,1},{-1,0},{0,-1}, 
		{1,1}, {-1, 1}, {-1,-1}, {1,-1} };
	int dfs(Mapa const& M, int i, int j) 
	{ 
		visit[i][j] = true; 
		int tam = 1; 
		for (auto d : dirs) 
		{ 
			int ni = i + d.first, nj = j + d.second; 
			if (correcta(ni, nj) && M[ni][nj] == 'X' && !visit[ni][nj]) 
			{ 
				tam += dfs(M, ni, nj); 
			} 
			else if (correcta(ni, nj)  && !pared(ni, nj) && M[ni][nj] == '.' && !visit[ni][nj])
			{
				if (dfsHueco(M, ni, nj))
					numB++;
			}
		} return tam; 
	}

	bool dfsHueco(Mapa const& M, int i, int j)
	{
		visit[i][j] = true;
		bool hueco = true;

		//En el momento en el que el booleano cambie paramos
		int d = 0;
		while (hueco && d < dirs.size() / 2) {

			int ni = i + dirs[d].first, nj = j + dirs[d].second;

			if (correcta(ni, nj) && pared(ni, nj))
				return false;

			//Si no se ha llegado a una pared seguimos investigando el hueco
			if (correcta(ni, nj) && M[ni][nj] == '.' && !visit[ni][nj])
				hueco = dfsHueco(M, ni, nj);

			d++;
		}
		return hueco;
	}
};

bool resuelveCaso() {
	int F, C; 
	cin >> C >> F; // número de filas y columnas 

	if (!cin) return false; 

	Mapa mapa(F); // leemos la imagen 
	for (string & linea : mapa) 
		cin >> linea; 

	// la analizamos 
	Manchas manchas(mapa);

	cout << manchas.blancas() << ' ' << '\n'; 

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
