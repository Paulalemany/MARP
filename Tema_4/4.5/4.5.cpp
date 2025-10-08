
/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <deque>
#include <queue>

#include "Grafo.h"

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

struct aristas {
	string pelicula;
	vector<string> actores;
};

string KevinBacon = "KevinBacon";

class NumBacon {
private:
	vector<bool> visit;	//Vector de nodos visitados
	vector<int> ant;	//guarda el último vértice antes de llegar a v
	vector<int> dist;	//guarda el último vértice antes de llegar a v
	int s;				//Origen del grafo

	using Camino = std::deque<int>;	
public:

	NumBacon(Grafo& g, int s) : visit(g.V(), false), 
								ant(g.V()), dist(g.V()), s(s) {
		bfs(g);
	}

	void bfs(Grafo& g) {
		queue<int> q;
		dist[s] = 0; visit[s] = true;
		q.push(s);

		while (!q.empty()) {
			int v = q.front(); q.pop();
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

	//¿Hay camino del origen a v?
	bool hayCamino(int v) const {
		return visit[v];
	}

	//Devuelve el camino más corto desde el origen a v (Si existe)
	Camino camino(int v) const {
		if (!hayCamino(v)) throw domain_error("No existe camino");
		Camino cam;
		for (int x = v; x != s; x != ant[x])
			cam.push_front(x);
		cam.push_front(s);
		return cam;
	}

	int distancia(int v) const {
		return dist[v]/2;
	}
};

bool resuelveCaso() {
	// leer los datos de la entrada
	int P, A;
	cin >> P;

	if (!std::cin)  // fin de la entrada
		return false;

	string peli, actor;					//Variables para leer los datos
	int act;
	vector<aristas> aris;				//Aristas que hay que ponerles al grafo
	unordered_map<string, int> mapa;	//Guardamos la relación entre el nombre y su nodo ç
										//(Para poder crear las aristas a partir de un string)
	int nodo = 0;	//Nodo que vamos a darle al mapa

	//Leemos todas las pelis, actores y aristas
	for (int i = 0; i < P; i++) {
		cin >> peli >> act;
		aristas a;
		a.pelicula = peli;
		mapa.insert({ peli, nodo });
		nodo++;

		for (int j = 0; j < act; j++) {
			cin >> actor;
			a.actores.push_back(actor);

			//Lo añadimos al mapa si es que no esta ya
			if (mapa.count(actor) == 0) {
				mapa.insert({ actor, nodo });
				nodo++;
			}
		}
		aris.push_back(a);
	}

	//Creamos el grafo
	Grafo Bacon(nodo);	//Los nodos son las peliculas y los actores

	//Hacemos las aristas
	for (int i = 0; i < aris.size(); i++) {
		for (int j = 0; j < aris[i].actores.size(); j++) {
			Bacon.ponArista(mapa[aris[i].pelicula], mapa[aris[i].actores[j]]);
		}
	}
	

	cin >> A;

	if (mapa.count(KevinBacon) == 0) {	//Si no está kevinBacon en la base de datos
		act = 0;

		for (int i = 0; i < A; i++) {
			cin >> actor;
			cout << actor << " INF\n";
		}
	}
	else {
		NumBacon num(Bacon, mapa[KevinBacon]);	//El origen es el nodo que tenga a KevinBacon
		//Esto lo haremos para las llamadas a función
		for (int i = 0; i < A; i++) {
			cin >> actor;

			act = num.distancia(mapa[actor]);

			if (act == 0 && actor != KevinBacon)
				cout << actor << " INF\n";
			else
				cout << actor << " " << act << '\n';

		}
	}
	

	cout << "---\n";
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
