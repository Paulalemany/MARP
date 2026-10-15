/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

using namespace std;

#include "Digrafo.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class DFSDirigido {
public: 
	
	DFSDirigido(Digrafo const& g, int s) 
		: visit(g.V(), false) { 	
		dfs(g, s); 
	} 

	bool alcanzable(int v) const {
		return visit[v]; 
	} 

private: 
	std::vector<bool> visit; // visit[v] = ¿hay camino dirigido de s a v? 
	
	void dfs(Digrafo const& g, int v) {
		visit[v] = true; 
		for (int w : g.ady(v)) 
			if (!visit[w]) 
				dfs(g, w); 
	} 
};

int restaurantesAlcanzables(int NV, int ori, int dest, DFSDirigido origen, DFSDirigido destino) {

	int restaurantes = 0;
	for (int i = 0; i < NV; i++) {

		//Si el nodo NO es el origen
		//El nodo NO es el destino
		//Se puede llegar desde el origen al nodo
		//Se puede llegar desde el nodo al destino
		if (i != ori && i != dest && origen.alcanzable(i) && destino.alcanzable(i))
			restaurantes++;
	}

	return restaurantes;
}

void resuelveCaso() {
	// leer los datos de la entrada
	int NV, NA;

	cin >> NV >> NA;
	Digrafo ciudad(NV);

	int n1, n2;
	for (int i = 0; i < NA; i++) {

		cin >> n1 >> n2;
		ciudad.ponArista(n1 - 1, n2 - 1);
	}

	Digrafo inverso = ciudad.inverso();
	
	// resolver el caso posiblemente llamando a otras funciones
	int Q;
	cin >> Q;
	for (int i = 0; i < Q; i++) {
		cin >> n1 >> n2;

		DFSDirigido Origen(ciudad, n1 - 1);
		DFSDirigido Destino(inverso, n2 - 1);
	
		// escribir la solución
		if (Origen.alcanzable(n2 - 1)) //Si el destino es alcanzable desde el origen
			cout << restaurantesAlcanzables(NV, n1 - 1, n2 - 1, Origen, Destino) << " \n";
		else
			cout << "IMPOSIBLE\n";

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
