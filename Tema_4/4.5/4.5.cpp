/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>

using namespace std;

#include "Grafo.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class CaminoMasCorto {

private:
	std::vector<bool> visit; // visit[v] = ¿hay camino de s a v? 
	std::vector<int> ant; // ant[v]  = último vértice antes de llegar a v 
	std::vector<int> dist; // dist[v] = aristas en el camino s-v más corto 
	int s;

	void bfs(Grafo const& g) {
		std::queue<int> q;
		dist[s] = 0;
		visit[s] = true;
		q.push(s);
		while (!q.empty()) {
			int v = q.front();
			q.pop();
			for (int w : g.ady(v)) {
				if (!visit[w]) {
					ant[w] = v;
					dist[w] = dist[v] + 1;
					visit[w] = true;
					q.push(w);
				}
			}
		}
	}

public:
	CaminoMasCorto(Grafo const& g, int s) :
		visit(g.V(), false), ant(g.V()), dist(g.V()), s(s) {
		bfs(g);
	}

	// ¿hay camino del origen a v? 
	bool hayCamino(int v) const {
		return visit[v];
	}

	// número de aristas entre s y v 
	int distancia(int v) const {
		return dist[v];
	}

};


struct arista {
	string pelicula;
	string actor;
};

void resuelveCaso() {
	// leer los datos de la entrada

	int P;
	cin >> P;

	int nodo = 0;

	//Necesito guardar la relación nombre - numero de nodo
	unordered_map<string, int> mapeo;
	vector<arista> aristas;	//Para poder crear las aristas del grafo

	for (size_t i = 0; i < P; i++)
	{
		string titulo, actor;
		int n;

		cin >> titulo >> n;

		//Guardamos el mapeo del titulo con su nodo
		mapeo.insert({ titulo, nodo });
		nodo++;

		for (int j = 0; j < n; j++) {
			cin >> actor;

			//Mapeamos el nombre del actor a su numero de nodo
			if (mapeo.count(actor) == 0) {
				mapeo.insert({ actor, nodo });
				nodo++;
			}

			//Guardamos la arista para el futuro
			aristas.push_back({ titulo, actor });
			
		}
	}

	//Debemos construir el grafo
	Grafo Bacon(nodo);

	//Ponemos las aristas pertinentes
	for (int i = 0; i < aristas.size(); i++) {
		Bacon.ponArista(mapeo[aristas[i].actor], mapeo[aristas[i].pelicula]);
	}

	// resolver el caso posiblemente llamando a otras funciones

	//Debemos hacer un dfs
	int B;

	cin >> B;
	string actor;

	if (mapeo.count("KevinBacon") > 0) {

		CaminoMasCorto kevinBacon(Bacon, mapeo["KevinBacon"]);
		// escribir la solución
		for (int i = 0; i < B; i++) {

			cin >> actor;
			string sol;
			if (kevinBacon.hayCamino(mapeo[actor])) {
				//Dividimos entre 2 porque no queremos que nos cuente las pelis, solo los actores
				sol = to_string(kevinBacon.distancia(mapeo[actor]) / 2);
			}
			else
				sol = "INF";

			cout << actor << " " << sol << '\n';
		}
	}
	else {
		for (int i = 0; i < B; i++) {
			cin >> actor;
			cout << actor << " INF\n";
		}
	}


	cout << "---\n";

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
