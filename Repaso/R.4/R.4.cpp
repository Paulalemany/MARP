/*@ <authors>
 *
 * Paula, Alemany Rodriguez (MARP01).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

using namespace std;

#include "PriorityQueue.h"
#include "ConjuntosDisjuntos.h"
#include "GrafoValorado.h"

/*@ <answer>

 Nos encontramos ante un problema de árboles de recubrimiento y caminos mínimos
 Utilizaremos el algoritmo de Kruskal para solucionarlo pero con algunos detalles a tener en cuenta.
 Primero la solución no es la suma total de los costes sino el coste mayor 
 ya que trabajan de forma simultánea, después si no están conectados todos los pueblos se da por imposible

 Para el primer matiz (Que el tiempo que tardan es el tiempo mayor) 
 simplemente se ha hecho que en vez de sumar el coste se guarde el mayor elemento
 entre la nueva arista añadida o la mayor que ya teniamos guardada en coste

 Para el segundo matiz (El hecho de que si no es conexo es imposible)
 Se han utilizado los conjuntos disjuntos ya implementados, si el grafo tiene más de
 un conjunto disjunto no es conexo por lo tanto es imposible conectar todos los pueblos.

 El coste de esta solución es el coste del algoritmo de Kruskal, es decir
 O(A log A) Siendo A el número de aristas y tiene un espacio adiocional de O(A)


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

	bool esConexo() const { return conexo; }

	ARM_Kruskal(GrafoValorado<Valor> const& g) : 
		coste(0), conexo(true)
	{ 
		PriorityQueue<Arista<Valor>> pq(g.aristas()); 
		ConjuntosDisjuntos cjtos(g.V()); 
		
		while (!pq.empty()) 
		{
			auto a = pq.top(); 
			pq.pop(); 
			int v = a.uno(), w = a.otro(v); 
			if (!cjtos.unidos(v, w)) 
			{ 
				cjtos.unir(v, w); 
				_ARM.push_back(a); 
				coste = max(a.valor(), coste); 
				if (_ARM.size() == g.V() - 1) break; 
			} 
		} 

		conexo = cjtos.num_cjtos() == 1;	//Si solo tenemos un conjunto es que es conexo
	}
};

void resuelveCaso() {
	
	int N, M;

	cin >> N >> M;

	//creamos el grafo valorado
	int p1, p2, h;
	GrafoValorado <int> pueblos(N);

	for (int i = 0; i < M; i++)
	{
		cin >> p1 >> p2 >> h;
		Arista <int> a(p1 - 1, p2 - 1, h);
		pueblos.ponArista(a);
	}

	ARM_Kruskal <int> sol(pueblos);

	if (sol.esConexo())
		cout << sol.costeARM() << '\n';
	else
		cout << "Imposible\n";
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
