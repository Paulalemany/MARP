/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

/*@ <answer>

 Para resolver este problema primero guardamos los grupos de músicos en una cola de prioridad de máximos
 Para que el grupo más prioritario sea aquel que tiene más músicos que comparten partitura.

 Como caso base, sabemos que si hay más partituras que músicos cada músico tendrá una partitura por lo que
 en ese caso nos ahorramos el cáculo. Otra cosa ha tener en cuenta es que se nos asegura que cada grupo de
 instrumentos tiene al menos una partitura por lo que, contamos como si tuviesemos p - n partituras 
 (siendo p el numero de partituras y n el numero de grupos de instrumentos diferentes) para reducir un poco
 la longitud del bucle.

 El bucle lo que hace es dar una partitura extra al grupo mayor, dividiendo ese grupo en dos diferentes y añadiendolos
 a la cola. Así siempre se le dará una partitura a aquellos músicos que esten compartiendo con más compañeros.
 El coste de este bucle esta en el orden de O(p log n), siendo p el número de partituras disponibles y n el número 
 de grupos de instrumentos que tenemos.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

void resuelveCaso() {
	// leer los datos de la entrada
	int p, n;
	cin >> p >> n;
	priority_queue<int> musicos;

	int m;
	int numeroMusicos = 0;
	for (int i = 0; i < n; i++) {
		cin >> m;
		musicos.push(m);
		numeroMusicos += m;
	}

	// resolver el caso posiblemente llamando a otras funciones

	// Cada grupo de musicos tiene minimo 1 partitura asegurada asi que restamos ese numero
	// para hacer el bucle más pequeño

	//Si tenemos mas partituras que musicos cada musico tendra una
	if (p >= numeroMusicos) {
		cout << "1" << '\n';
	}
	else {

		// Le damos minimo una partitura a cada grupo de instrumentos
		p -= n;

		while (p > 0) {

			// Le damos una partitura al grupo mayor
			int top = musicos.top(); musicos.pop();
			int g1, g2;

			//Dividimos en dos grupos
			g1 = top / 2;
			g2 = top - g1;

			musicos.push(g1); musicos.push(g2);

			//Hemos gastado una partitura
			p--;
		}


		// escribir la solución
		cout << musicos.top() << '\n';
	}
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
