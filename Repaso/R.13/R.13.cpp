
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "EnterosInf.h"
#include "Matriz.h"

/*@ <answer>

 Nos encontramos ante un problema que puede solucionarse mediante programación dinámica ascendente
 Las restricciones que tenemos son:
	La solución debe estar entre Pmin <= sol <= Pmax
	Siendo Pmin la potencia mínima requerida
	Pmax la potencia máxima admitida

	Para solucionar esta restricción, una vez rellenados todos los casos mediante programación
	dinámica, se recorre el intervalo bombillas[b][PMin] bombillas[b][PMax], donde
	bombillas es la matriz donde se han guardado las soluciones y b es el número de bombillas distintas
	de la que disponemos, para encontrar cual tiene el coste menor. En caso de empate en costo
	se debe seleccionar el de menor potencia al recorrerlo en orden ascendente esto ya ocurre.

Traducción de las variables
	bombillas[i][j] -> Coste minimo con el que llegar justo a la potencia j
	i -> Tipo de bombilla
	j -> Potencia

Casos base
	bombillas[i][0] = 0 -> El coste de llegar a potencia 0 es 0
	bombillas[0][j] = Infinito -> Es imposible llegar a potencia j con bombillas de potencia 0

Recursión
	Para bombillas[i][j] tenemos 2 opciones:
		No usar ninguna bombilla de ese tipo -> El coste con esta es igual al coste con el tipo anterior 
			bombillas[i][j] = bombillas[i-1][j]
		Usar al menos una bombilla de ese tipo -> El coste de llegar a la potencia sin esta bombilla 
		mas el coste de esta bombilla
			bombillas[i][j] = bombillas[i][j - potencia[i-1]] + coste[i-1]
			En estos casos potencia y coste usan i - 1 porque sus vectores empiezan en 0

Coste
	El coste de este algoritmo de programación dinámica sería de
		O(b * Pmax)

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

pair<EntInf, int> costeMinimo(vector<int> const& potencias, vector<int> const& costes, int PMax, int PMin) 
{ 
	int b = potencias.size(); 
	Matriz<EntInf> bombillas(b + 1, PMax + 1, Infinito); 
	bombillas[0][0] = 0; 
	//EL segundo caso base como inicializamos a infinito no hace falta ponerlo

	for (int i = 1; i <= b; ++i) 
	{ 
		bombillas[i][0] = 0; //El coste de llegar a potencia 0 = 0 
		for (int j = 1; j <= PMax; ++j) 
			if (potencias[i - 1] > j) //Si la potencia de la bombilla es mayor a la potencia maxima
				bombillas[i][j] = bombillas[i - 1][j];  //No usamos esa bombilla
			else 
				bombillas[i][j] = min(bombillas[i - 1][j], bombillas[i][j - potencias[i-1]] + costes[i-1]);
				//Si no nos pasamos del limite nos quedamos con la opción más barata entre usarla y no usarla
	} 

	//Queremos devolver el coste menor entre Pmin y Pmax ademas en caso de empate se da la menor
	EntInf minCoste = Infinito;
	int potenciaOptima = -1;

	for (int j = PMin; j <= PMax; j++) {
		if (bombillas[b][j] < minCoste) {
			minCoste = bombillas[b][j];
			potenciaOptima = j;
		}
	}

	return {minCoste, potenciaOptima};
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int N, PMax, PMin;

	cin >> N >> PMax >> PMin;

	if (!std::cin)  // fin de la entrada
		return false;

	vector<int> potencias;
	vector<int> costes;

	int dato;
	for (int i = 0; i < N * 2; i++) {

		cin >> dato;
		if (i < N)
			potencias.push_back(dato);
		else
			costes.push_back(dato);
	}

	// resolver el caso posiblemente llamando a otras funciones
	pair<EntInf, int> sol = costeMinimo(potencias, costes, PMax, PMin);

	// escribir la solución
	if (sol.first == Infinito)
		cout << "IMPOSIBLE\n";
	else
		cout << sol.first << " " << sol.second << '\n';

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
