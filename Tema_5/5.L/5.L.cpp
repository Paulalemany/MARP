/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <deque>

using namespace std;

#include "Digrafo.h"

/*@ <answer>

 Nos encontramos ante un problema que puede resolverse mediante Digrafos no valorados,
 donde los nodos son las instrucciones y las aristas las conexiones entre instrucciones,
 tenemos 3 tipos:
	- A: Esta instruccion conecta directamente con la siguiente
	- J: Esta instruccion conecta con otra determinada
	- C: Esta instruccion conecta con la siguiente a la vez que con otra determinada
 Debemos determinar si el programa termina y con que certeza, para ello se ha creado
 un nodo extra "fantasma" que simboliza la finalización del programa, el programa puede terminar si 
 se llega a este nodo extra.

 Para la resolución se ha utilizado una busqueda en profundidad, primero para determinar si hay
 alguna manera de llegar al final del programa desde la primera instrucción, en caso negativo
 el programa no terminará nunca. En caso positivo tenemos dos posibilidades o que el programa
 termine siempre o que termine a veces, para saber esto diferenciamos entre dos casos.
	- Las isntrucciones pueden caer en un ciclo infinito
	- No hay ciclos, todos los caminos llevan al final
 Diferenciamos solo entre estas dos opciones ya que si ninguno de los dos caminos llevan al
 final se habría detenido la resolución en el primer caso, no hay manera de llegar al final.
 Si el programa tiene la posibilidad de acabar en un bucle infinito solo terminará a veces,
 si no existe esta posibilidad el programa terminará siempre.

 La complejidad de este programa es la del propio DFS por tanto esta en el orden de o(L + A)
 siendo L el numero de instrucciones del programa (Contando el nodo extra del final) y A
 el numero de aristas.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

using Camino = deque<int>;

class DFSDirigido {
public: 
	
	DFSDirigido(Digrafo const& g, int s) 
		: visit(g.V(), false), ant(g.V(), -1), apilado(g.V(), false), hayciclo(false) {
	
		dfs(g, s); 
	} 

	bool hayCamino(int v) const {
		return visit[v]; 
	} 

	bool hayCiclo() const { return hayciclo; }

private: 
	
	std::vector<bool> visit; // visit[v] = ¿hay camino dirigido de s a v? 
	std::vector<int> ant; // ant[v]  = último vértice antes de llegar a v

	std::vector<bool> apilado; // apilado[v] = ¿está el vértice v en la pila?
	bool hayciclo;
	
	void dfs(Digrafo const& g, int v) { 
		apilado[v] = true;
		visit[v] = true; 

		for (int w : g.ady(v)) {

			if (!visit[w]) {
				ant[w] = v;
				dfs(g, w); 
			}
			else if (apilado[w]) // hemos detectado un ciclo
				hayciclo = true; 
		}
		apilado[v] = false;
	} 
};

void resuelveCaso() {
	// leer los datos de la entrada
	int L;

	cin >> L;
	
	Digrafo programa(L + 1);
	char instruccion;
	int dest;

	for (int i = 0; i < L; i++) {
		cin >> instruccion;

		//Conectamos esta instruccion con la siguiente
		if (instruccion == 'A' || instruccion == 'C')
			programa.ponArista(i, i + 1);

		if (instruccion == 'J' || instruccion == 'C') {
			cin >> dest;
			programa.ponArista(i, dest - 1);
		}
		
	}

	// resolver el caso posiblemente llamando a otras funciones
	DFSDirigido flujo(programa, 0);

	//Si no hay camino entre la primera instruccion y la última es que no se va a llegar nunca
	if (!flujo.hayCamino(L))
		cout << "NUNCA\n";
	else if (flujo.hayCiclo())
		cout << "A VECES\n";
	else
		cout << "SIEMPRE\n";
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
