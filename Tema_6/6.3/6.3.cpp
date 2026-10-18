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
#include "ConjuntosDisjuntos.h"
#include "PriorityQueue.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

template <typename Valor> 
class ARM_Kruskal {
private: 
	std::vector<Arista<Valor>> _ARM; 
	Valor coste; 
	bool conexo;

public: 
	Valor costeARM() const { return coste; } 
	std::vector<Arista<Valor>> const& ARM() const { return _ARM; }
	bool esConexo() const { return conexo; }

	ARM_Kruskal(GrafoValorado<Valor> const& g) : coste(0), conexo(true) {
		PriorityQueue<Arista<Valor>> pq(g.aristas());
		ConjuntosDisjuntos cjtos(g.V()); 
		
		while (!pq.empty()) { 
			auto a = pq.top(); pq.pop(); 
			int v = a.uno(), w = a.otro(v); 
			
			if (!cjtos.unidos(v, w)) { 
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

void resuelveCaso() {
	// leer los datos de la entrada
	int I, P;

	cin >> I >> P;

	GrafoValorado<int> islotes(I);
	int isla1, isla2, p;
	for (int i = 0; i < P; i++) {

		cin >> isla1 >> isla2 >> p;
		islotes.ponArista({ isla1 - 1, isla2 - 1, p });
	}

	// resolver el caso posiblemente llamando a otras funciones
	ARM_Kruskal<int> arm(islotes);

	// escribir la solución
	if (arm.esConexo())
		cout << arm.costeARM() << '\n';
	else
		cout << "No hay puentes suficientes\n";
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
