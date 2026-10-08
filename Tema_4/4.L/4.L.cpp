/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_set>

using namespace std;

#include "Grafo.h"

/*@ <answer>

 Para resolver este ejercicio se utilizan diferentes recorridos en anchura:
	- Recorrido para ver la distancia entre el Trabajo y todos los demas sitios.
	- Recorrido para ver la distancia que hay entre la casa de Alex y la cada de Lucas.

 Tras esto primero tomamos dos casos por separado:
	- Coste que tendria que cada uno fuera al trabajo por separado, es decir la distancia
	que hay del trabajo a cada una de las casas en su camino minimo sumadas.

	- Coste que tendria si quedan primero en algún sitio en común y después van juntos al trabajo.
		Para esto vemos si hay algun nodo entre ambas casas que pille de camino al trabajo del otro 
		(Del otro para evitar que se tenga en cuenta por estar en su propia casa)
		El coste en este caso es el coste que tiene cada uno para llegar al comun y luego el coste desde
		ese punto comun al trabajo

 Al final para la solución se comparan ambas opciones y nos quedamos con aquella que tenga el coste menor.

 El coste de este algoritmo en tiempo estaría en el orden de O(n * N + C) siendo n el numero de nodos
 que hay entre ambas casas, N el numero de nodos de la ciudad y C el numero de calles

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

using Camino = unordered_set<int>;

class CaminoMasCorto {
public: 
	
	CaminoMasCorto(Grafo const& g, int s) 
		: visit(g.V(), false), ant(g.V()), dist(g.V()), s(s) {
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
	
	// devuelve el camino más corto desde el origen a v (si existe) 
	Camino camino(int v) const { 
		
		if (!hayCamino(v)) 
			throw std::domain_error("No existe camino"); 
		Camino cam; 
		
		for (int x = v; x != s; x = ant[x]) 
			cam.insert(x); 
		
		cam.insert(s); 
		return cam;
	}

private: 
	
	std::vector<bool> visit; // visit[v] = ¿hay camino de s a v? 
	std::vector<int> ant; // ant[v]  = último vértice antes de llegar a v 
	std::vector<int> dist; // dist[v] = aristas en el camino s-v más corto 
	int s;

	void bfs(Grafo const& g) { 
		std::queue<int> q; 
		dist[s] = 0; visit[s] = true; 
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
};

void resuelveCaso() {
	// leer los datos de la entrada
	int N, C, A, L, T;
	cin >> N >> C >> A >> L >> T;

	Grafo ciudad(N);

	int d1, d2;
	for (int i = 0; i < C; i++) {

		cin >> d1 >> d2;
		ciudad.ponArista(d1 - 1, d2 - 1);
	}

	// resolver el caso posiblemente llamando a otras funciones
	// vemos la distancia del trabajo a todas partes
	//O(N + C)
	CaminoMasCorto trabajo(ciudad, T - 1);

	//Guardamos el coste de si van por separado
	//Aqui no estoy teniendo en cuenta la posibilidad de que la casa de uno este de camino al trabajo con el otro
	int separados = trabajo.distancia(A - 1) + trabajo.distancia(L - 1);

	//O(N + C)
	CaminoMasCorto casas(ciudad, A - 1);
	//Buscamos el nodo comun entre el camino entre las casas y el camino del trabajo a las casas

	Camino amigos = casas.camino(L - 1);
	Camino trabA = trabajo.camino(A - 1);	//Camino al trabajo de alex
	Camino trabL = trabajo.camino(L - 1);	//Camino al trabajo de lucas

	//Vamos comparando los caminos buscando si en el camino al trabajo se pasa por algún punto en comun
	//Puede haber varios nodos en comun, cogemos el que tenga la menor distancia al trabajo
	int menorDist = -1;

	//O (n) siendo n el numero de nodos entre ambas casas
	for (const auto& nodo : amigos) {
		
		//Vemos si el nodo esta en alguno de los caminos al trabajo
		if (nodo != T-1 && ((trabA.count(nodo) > 0 && nodo != A -1) || (trabL.count(nodo)) > 0 && nodo != L - 1)) {

			if (menorDist == -1 || trabajo.distancia(nodo) < trabajo.distancia(menorDist))
				menorDist = nodo;
		}
	}

	//Calculamos el coste del camino esperandose mutuamente
	int distL = abs(casas.distancia(L - 1) - casas.distancia(menorDist));
	int costeJuntos = casas.distancia(menorDist) + distL + trabajo.distancia(menorDist);

	// escribir la solución
	cout << min(separados, costeJuntos) << '\n';
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
