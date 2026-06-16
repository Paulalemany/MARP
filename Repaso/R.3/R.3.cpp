
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "Matriz.h"

/*@ <answer>

 Nos encontramos ante un caso que puede resolverse con programación dinámica de 
 forma similar al problema de la mochila pero con más condiciones.
 Para resolverlo lo que hacemos es ir guardando el beneficio que da hacer 0 tipos de un bollo
 o hacer 1, 2... hasta el máximo que se puedan hacer de ese tipo y comparar si es mejor hacerlo
 o hacer de los siguientes.

 El coste de este algoritmo de programación dinámica descendente
 es de O(N * M * K) siendo:
 N numero de tipos que tenemos
 M la masa de la que disponemos
 K numero de bollos que se pueden hacer de cada tipo

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Bollos 
{ 
	int Gdisponibles; 
	int Gnecesarios;
	int Mnecesaria;
	int precio;
}; 

//boll -> tipos distintos de bollos que tenemos
//i -> Indice de la matriz que muestra el tipo de bollo que estamos mirando
//j -> Indice de la matriz que muestra la masa que tenemos
//beneficio -> Matriz donde guardamos el beneficio
double mochila_rec(vector<Bollos> const& boll, int i, int j, Matriz<double>& beneficio) 
{
	if (beneficio[i][j] != -1) // subproblema ya resuelto 
		return beneficio[i][j]; 

	if (i == 0 || j == 0) 
		beneficio[i][j] = 0; //No tenemos nada

	else
	{
		//Comprobamos cuantos más de este tipo podemos hacer
		//hacemos i - 1 porque la matriz empieza en 0 pero i empieza en 1
		int max_bollos = boll[i - 1].Gdisponibles / boll[i - 1].Gnecesarios;

		//Empezamos con la opcion de no hacer ningun bollo de este tipo
		//Pasamos con toda la masa al siguiente tipo con recursion
		beneficio[i][j] = mochila_rec(boll, i - 1, j, beneficio);

		//Probamos con hacer k bollos de este tipo
		//Empezamos en 1 porque hacer 0 es la opcion anterior
		for (int k = 1; k <= max_bollos; k++)
		{
			//contamos cuanta masa hemos gastado
			int masa = k * boll[i - 1].Mnecesaria;

			//Si la masa supera la masa total que tenemos paramos
			if (masa > j) break;

			//Vemos si da mas beneficio hacer de un tipo nuevo
			double opcion = mochila_rec(boll, i - 1, j - masa, beneficio) 
				+ k * boll[i - 1].precio; //Sumamos el dinero generado por crear estos

			//Comparamos que nos da mas beneficio si no hacer bollos de este tipo o si hacerlos
			beneficio[i][j] = max(beneficio[i][j], opcion);
		}
	}
	return beneficio[i][j];
}

//bollos -> Tipos totales que hay
//M -> Masa total de la que disponemos
double Beneficio(vector<Bollos> const& bollos, int M) {
	//Numero de tipos distintos que hay
	int n = bollos.size(); 
	Matriz<double> beneficio(n + 1, M + 1, -1);  
	return mochila_rec(bollos, n, M, beneficio); // cálculo de los bollos 

	//Devuelve el beneficio final
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int N, M;
	cin >> N >> M;

	if (!std::cin)  // fin de la entrada
		return false;

	//Guardamos los tipos de bollos
	vector<Bollos> bollos;

	int G, g, m, e;
	Bollos b;
	for (int i = 0; i < N; i++) {
		cin >> G >> g >> m >> e;
		b.Gdisponibles = G;
		b.Gnecesarios = g;
		b.Mnecesaria = m;
		b.precio = e;

		bollos.push_back(b);
	}

	cout << Beneficio(bollos, M) << '\n';

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
