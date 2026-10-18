/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
 //#include <...>

using namespace std;

#include "GrafoValorado.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class CaminosDFS {
private:
	std::vector<bool> visit; // visit[v] = ¿hay camino de s a v? 
	std::vector<int> ant; // ant[v] = último vértice antes de llegar a v 
	int s; // vértice origen 

	// visita los nodos alcanzables desde v respetando el umbral 
	void dfs(GrafoValorado<int> const& G, int v, int umbral)
	{
		visit[v] = true;
		for (auto a : G.ady(v))
		{
			if (a.valor() >= umbral)
			{
				int w = a.otro(v);
				if (!visit[w])
					dfs(G, w, umbral);
			}
		}
	}

public:

	CaminosDFS(GrafoValorado<int> const& g, int s, int ancho)
		: visit(g.V(), false), ant(g.V()), s(s)
	{
		dfs(g, s, ancho);
	}

	// ¿hay camino del origen a v? 
	bool hayCamino(int v) const { return visit[v]; }

};

void resuelveCaso() {
	// leer los datos de la entrada

	int V, E;
	cin >> V >> E;

	GrafoValorado<int> ciudad(V);
	int I1, I2, ancho;

	for (int i = 0; i < E; i++) {

		cin >> I1 >> I2 >> ancho;
		ciudad.ponArista({ I1-1, I2-1, ancho });
	}

	int K;
	cin >> K;

	for (int i = 0; i < K; i++) {

		int o, d, a;
		cin >> o >> d >> a;

		CaminosDFS camino(ciudad, o - 1, a);
		if (camino.hayCamino(d - 1))
			cout << "SI\n";
		else
			cout << "NO\n";
	}

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
