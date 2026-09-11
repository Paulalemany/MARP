
/*@ <authors>
 *
 * Paula, Alemany Rodriguez (MARP01).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "ConjuntosDisjuntos.h"
#include "GrafoValorado.h"
#include "PriorityQueue.h"

/*@ <answer>

 Nos encontramos ante un problema de grafos que se soluciona con la utilización 
 del algoritmo de Kruskal y árboles de recubrimiento mínimo. 
 En el caso de que el grafo no sea conexo, es decir que tenga mas de 1 conjunto disjunto,
 la solución será imposible.

 El coste de este algoritmo es el coste del Algoritmo de Kruskal, es decir 
 en tiempo O(a log A)
 en espacio O(A)

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

template <typename Valor> 
class ARM_Kruskal 
{
private: 
	std::vector<Arista<Valor>> _ARM; 
	Valor coste; 
	bool conexo;

public: 
	Valor costeARM() const { return coste; } 
	std::vector<Arista<Valor>> const& ARM() const { return _ARM; }
	bool Conexo() const { return conexo; }

	ARM_Kruskal(GrafoValorado<Valor> const& g) : coste(0), conexo(true)
	{ 
		PriorityQueue<Arista<Valor>> pq(g.aristas());
		ConjuntosDisjuntos cjtos(g.V()); 
		while (!pq.empty()) { 
			auto a = pq.top(); 
			pq.pop(); 
			int v = a.uno(), w = a.otro(v); 
			if (!cjtos.unidos(v, w)) 
			{ 
				cjtos.unir(v, w);
				_ARM.push_back(a);
				coste += a.valor(); 
				if (_ARM.size() == g.V() - 1) 
					break; 

			} 
		} 
				
		conexo = cjtos.num_cjtos() == 1;
	}
};

bool resuelveCaso() {
	
	int N;

	cin >> N;

	if (!std::cin)  // fin de la entrada
		return false;

	int C, v1, v2, coste;
	GrafoValorado<int> calles(N);
	cin >> C;
	for (int i = 0; i < C; i++) {
		cin >> v1 >> v2 >> coste;
		calles.ponArista({ v1 - 1, v2 - 1, coste });
	}

	// resolver el caso posiblemente llamando a otras funciones
	ARM_Kruskal<int> presupuesto(calles);

	// escribir la solución

	if (presupuesto.Conexo())
		cout << presupuesto.costeARM() << '\n';
	else
		cout << "Imposible\n";

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
