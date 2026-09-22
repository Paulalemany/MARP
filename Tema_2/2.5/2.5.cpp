
/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

/*@ <answer>

 Para resolver este problema primero se ha montado una estructura para guardar toda la informacion en un vector
 Cada indice del vector es una pila de comics en la que se guardan los comics de esa pila.
 Cada comic guarda su id y la pila a la que pertenece. Al mismo tiempo que esto se guarda cual es el mejor ejemplar
 para que podamos saber cuando parar.

 Tras esto se guarda en una cola de prioridad el primer elemento de cada pila para saber las opciones
 que tiene cada persona para elegir y saber en que orden se van a coger. Con ello sabemos en que orden se van tomando
 los tomos y cuando tocara el bueno

 El coste de la solucion es O(P log N) Siendo N el numero de opciones que hay para elegir y P el numero de tomos que hay
 Antes de poder elegir el mejor tomo.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct comic {
	int id;
	int pila;
};

bool operator<(comic const& a, comic const& b) {
	return b.id < a.id;
}

bool resuelveCaso() {
	// leer los datos de la entrada

	int N;	//Numero de pilas

	cin >> N;

	if (!std::cin)  // fin de la entrada
		return false;

	vector<stack<comic>> pilas;
	int mejor = -1;	//Para saber cual es el mejor ejemplar de antemano

	priority_queue<comic> opciones;

	for (int i = 0; i < N; i++) {
		int K;	//Cantidad de comics en la pila
		stack<comic> pila;
		cin >> K;
		for (int j = 0; j < K; j++) {
			int id;
			cin >> id;

			//Si es el primer comic que vemos ese es el mejor
			if (mejor == -1)
				mejor = id;
			else {
				//Nos quedamos el mejor de los dos
				mejor = min(id, mejor);
			}

			pila.push({ id, i });
		}
		opciones.push(pila.top());
		pilas.push_back(pila);
	}

	// resolver el caso posiblemente llamando a otras funciones

	int mejorAct = -1;
	int cont = 0;
	while (mejorAct != mejor) {

		//Vemos cual es el mejor de cada pila
		comic act = opciones.top(); opciones.pop();
		mejorAct = act.id;

		//Lo sacamos de la pila
		pilas[act.pila].pop();
		if (!pilas[act.pila].empty())
			opciones.push(pilas[act.pila].top());
		cont++;
	}

	// escribir la solución
	cout << cont << '\n';

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
