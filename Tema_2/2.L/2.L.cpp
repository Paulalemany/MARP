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
 Para que el grupo más prioritario sea aquel que tiene más músicos que comparten partitura, es decir, el numero de musicos
 entre el numero de partituras tiene un conjunto mayor.

 Contamos como si tuviesemos p - n partituras 
 (siendo p el numero de partituras y n el numero de grupos de instrumentos diferentes) para reducir un poco
 la longitud del bucle, ya que sabemos que como minimo cada grupo tiene 1 partitura.

 El bucle lo que hace es dar una partitura extra al grupo mayor y lo vuelve a añadir
 a la cola. Así siempre se le dará una partitura a aquellos músicos que esten compartiendo con más compañeros.
 El coste de este bucle esta en el orden de O(p log n), siendo p el número de partituras disponibles y n el número 
 de grupos de instrumentos que tenemos.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct musicos {
	int integrantes;
	int partituras;
};

bool operator<(musicos const& a, musicos const& b)
{
	return b.integrantes / b.partituras < a.integrantes / a.partituras ||
		(b.integrantes / b.partituras == a.integrantes / a.partituras && b.integrantes < a.integrantes);
}

bool operator>(musicos const& a, musicos const& b) {
	return b < a;
}

void resuelveCaso() {
	// leer los datos de la entrada
	int p, n;
	cin >> p >> n;
	priority_queue<musicos, vector<musicos>, greater<musicos>> mus;

	int m;
	for (int i = 0; i < n; i++) {
		cin >> m;
		mus.push({ m, 1 });
	}

	// Le damos minimo una partitura a cada grupo de instrumentos
	p -= n;

	while (p > 0) {

		// Le damos una partitura al grupo mayor
		musicos top = mus.top(); mus.pop();

		//Hemos gastado una partitura
		top.partituras++;
		p--;

		mus.push(top); 

	}

	int sol = mus.top().integrantes / mus.top().partituras;
	if (mus.top().integrantes % mus.top().partituras != 0)
		sol++;

	cout << sol << '\n';

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
