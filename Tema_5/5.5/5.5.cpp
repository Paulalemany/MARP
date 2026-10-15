/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>

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

const int MAX = 10000; 
const int INF = 1000000000; // ∞ int 

class SerpientesYEscaleras {
public:

	SerpientesYEscaleras(int N, int K, unordered_map<int, int> especiales) 
		: visit(N* N + 1, false), dist(N* N + 1, -1), K(K), especiales(especiales) {

		bfs(1, N * N);
	}

	int distancia(int v) {
		return dist[v];
	}



private:

	unordered_map<int, int> especiales;	//Casillas que llevan a otra casilla
	vector<bool> visit;					//Vector que marca si se han visitado
	vector<int> dist;					//Vector que marca a cuantos movimientos esta
	int K;
	
	int adyacente(int v, int i) { 

		int destino = v + i;
		//Podemos caer en una casilla especial
		if (especiales.count(destino) > 0)
			destino = especiales[destino];

		return destino;
	}

	int bfs(int origen, int destino) { 

		if (origen == destino)	//Si llegamos a la casilla final terminamos
			return 0; 
	
		//Marcamos como visitado
		visit[origen] = true;
		dist[origen] = 0;

		//Añadimos la casilla a la cola
		queue<int> cola; 
		cola.push(origen); 
	
		while (!cola.empty()) { 
			int v = cola.front(); cola.pop(); 

			for (int i = 1; i <= K; ++i) { 
				int w = adyacente(v, i); 

				//Si esta dentro del tablero y no lo hemos visitado
				if (w < visit.size() && !visit[w]) {
					dist[w] = dist[v] + 1;
					visit[w] = true;

					if (w == destino) return dist[w];
					else cola.push(w);
				}
			} 
		} 


	}

};



void resuelveCaso() {
	// leer los datos de la entrada
	int N, K, S, E;

	cin >> N >> K >> S >> E;

	unordered_map<int, int> especiales;

	int ori, dest;
	for (int i = 0; i < S + E; i++) {
		cin >> ori >> dest;

		especiales.insert({ ori, dest});
	}

	// resolver el caso posiblemente llamando a otras funciones

	SerpientesYEscaleras juego(N, K, especiales);

	// escribir la solución
	cout << juego.distancia(N * N) << '\n';
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
