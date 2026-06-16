
/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01)
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <deque>

using namespace std;

#include "Grafo.h"

/*@ <answer>

 Este problema se trata de discernir si el grafo que nos presenta es o no es bipartito.
 Para ello utilizamos una búsqueda en profundidad.
 Con que una de sus componentes conexas NO sea bipartito el grafo ya no es bipartito.

 Para ello se ha modificado la busqueda en profundidad de manera que se van "marcando" 
 a que equipo pertenece cada amigo, si un amigo tiene una rivalidad con un miembro marcado
 como de su equipo la division no es posible. Además nos aseguramos de pasar por todos los amigos 
 para que no haya ninguno al que no se le asigne un equipo.

 El coste de este algoritmo sería de O(V+A) donde V es el número de vértices del grafo y A el número de aristas.

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
	bool bipartito; // Booleano para marcar la solucion
	std::vector<int> team; //Vamos "coloreando" en que equipo esta cada uno

	//Coste O(V + A)
	void dfs(Grafo const& G, int v, int color) {
		visit[v] = true;
		team[v] = color;
		for (int w : G.ady(v))
		{
			if (!visit[w])
			{
				ant[w] = v;
				dfs(G, w, -color);
			}
			else if (ant[v] != w && team[w] == team[v]) //Si es adyacente de un miembro de su equipo
				bipartito = false;	//el grafo no puede ser bipartito
		}
	}

public: 

	CaminosDFS(Grafo const& g, int s) : 
		visit(g.V(), false), ant(g.V()), s(s), bipartito(true), team(g.V(), 0)
	{ 
		for (int i = 0; i < g.V(); i++) {

			if (!visit[i])
			{
				dfs(g, i, 1);
			}
		}
	} 

	bool esBipartito() const { return bipartito; }
};

bool resuelveCaso() {
	// leer los datos de la entrada

	int A, R;

	//Guardamos el numero de amigos (vertices) y rivalidades (aristas)
	cin >> A >> R;

	if (!std::cin)  // fin de la entrada
		return false;

	//Creamos el grafo
	Grafo equipos(A);

	int a1, a2;
	//ponemos las aristas
	for (int i = 0; i < R; i++) {
		cin >> a1 >> a2;
		equipos.ponArista(a1 - 1, a2 - 1);
	}

	// resolver el caso posiblemente llamando a otras funciones
	CaminosDFS dfs(equipos, 0);

	// escribir la solución
	if (dfs.esBipartito())
		cout << "SI\n";
	else
		cout << "NO\n";

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
