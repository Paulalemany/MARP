
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <deque>

using namespace std;

#include "Digrafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

using Camino = std::deque<int>;

class PaellaDeJueves {
private:

	vector<bool> visitS;
	vector<bool> visitD;
	int s;

	void dfs(Digrafo& g, int v, vector<bool>& visit) {
		visit[v] = true;
		for (int w : g.ady(v))
			if (!visit[w]) {
				dfs(g, w, visit);
			}
	}


public:

	PaellaDeJueves(Digrafo& g, int s, int d) : visitS(g.V(), false), visitD(g.V(), false), s(s) {
		dfs(g, s, visitS);	//Nodos a los que se puede llegar desde s (El origen)
		Digrafo gi = g.inverso(); //Invertimos el grafo para que sea fiable
		dfs(gi, d, visitD);	//Nodos que se puede llegar desde d (El destino)

		//La unión de ambos es la solución
		int cont = 0;
		for (int i = 0; i < g.V(); i++) {
			if (visitS[i] && visitD[i]) cont++;
		}

		if (cont > 0) cout << cont - 2 << '\n';	//Restamos 2 porque no contamos ni el origen ni el destino
		else cout << "IMPOSIBLE\n";

	}

};

bool resuelveCaso() {
	// leer los datos de la entrada
	int NA, NV;
	cin >> NV >> NA;

	if (!std::cin)  // fin de la entrada
		return false;

	Digrafo g(NV);
	int d1, d2;

	for (int i = 0; i < NA; i++) {

		cin >> d1 >> d2;
		g.ponArista(d1 - 1, d2 - 1);
	}

	int Q, o, d;
	cin >> Q;

	for (int i = 0; i < Q; i++) {

		cin >> o >> d;
		PaellaDeJueves p(g, o - 1, d - 1);
	}

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
