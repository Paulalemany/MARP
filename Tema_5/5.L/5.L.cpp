
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

#include "Digrafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

	Para resolver el problema utilizamos un algoritmo dfs que comprueba los ciclos.
	Esperamos descifrar si el programa se ejecuta entero siempre, a veces o nunca,
	para ello formamos un grafo en el que las instrucciones A tienen una arista a la siguiente instrucción,
	las instrucciones J tienen una arista a la instrucción especificada y las intrucciones C tienen dos aristas; 
	una a la siguiente instrucción y otra a la instrucción especificada.

	Una vez dentro del dfs vamos comprobando los caminos y los ciclos: Si el Digrafo no tiene ciclos el programa
	SIEMPRE va a terminar, sin embargo si el programa tiene ciclos puede pasar 2 cosas. Si el ciclo es por culpa
	de una instrucción J el programa no va a terminar de ejecutarse nunca pero si el ciclo está formado por una
	instrucción C debemos seguir comprobando el grafo para ver si es un NUNCA (Hay después un ciclo de J) o un 
	A VECES (No hay más ciclos después o siguen siendo condicionales).

	El algoritmo tiene la complejidad del dfs ya que no se recorre más que eso una sola vez, por lo tanto tiene
	una complejidad de O (V + A) siendo V el número de instrucciones de la parte conexa unida a la primera instrucción
	y siendo A las conexiones entre las mismas.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class TerminaProgramaOscuro {
private:

	vector<bool> visit;					//vector de vértices visitados
	vector<bool> pila;					//vector de vértices por comprobar adyacentes
	pair <bool, char> ciclico;			//booleano para indicar si un digrafo tiene un ciclo y si es condicional o no

	//O (V + A)
	void dfs(Digrafo& g, int v, unordered_map <int, char>& map) {
		visit[v] = true;
		pila[v] = true;
		for (int w : g.ady(v)) {
			//Hay un ciclo NO condicional por lo tanto el programa no termina
			//Si el ciclo es condicional seguimos mirando el programa porque las opciones es a veces o puede que nunca
			if (ciclico.first && ciclico.second == 'J') return;	
			if (!visit[w]) {		//Continuamos el recorrido en profundidad
				dfs(g, w, map);
			}
			else if (pila[w])	//Hay un ciclo
			{
				ciclico.first = true;
				ciclico.second = map[v];	//Guardamos la instrucción que ha llevado a esto
			}
				
		}
		pila[v] = false;
	}

public:

	TerminaProgramaOscuro(Digrafo& g, unordered_map <int,char> & map) : visit(g.V(), false), pila(g.V(), false),
		ciclico(false, ' ') {

		//Aquí lo único que hay que comprobar es si hace un bucle infinito desde la primera vez que se llama
		//Si hay instrucciones que no se llaman nunca o hay ciclos en instrucciones a las que no se puede llegar
		//no nos importa porque el programa va a terminar igualmente
		dfs(g, 0, map);


		if (ciclico.first && ciclico.second == 'J') std::cout << "NUNCA";
		else if (ciclico.first && ciclico.second == 'C') std::cout << "A VECES";
		else std::cout << "SIEMPRE";
	}

};

bool resuelveCaso() {
	// leer los datos de la entrada
	int L;

	cin >> L;

	if (!std::cin)  // fin de la entrada
		return false;

	Digrafo instrucciones(L);	//Digrafo de las instrucciones
	int d;			//Para saber a que instrucción vamos a saltar
	char inst1;		//Para saber que instrucción estamos leyendo

	unordered_map <int, char> datoInstr;	//Para guardar que instrucción tiene cada nodo

	for (int i = 0; i < L; i++) {
		cin >> inst1;

		//Los nodos están numerados de 1 a L por lo tanto restamos 1 a todo para que cuadre (Aunque sume y reste 1 lo voy a dejar por legibilidad)
		switch (inst1)
		{
		case 'A':	//Instruccion aritmética y asignacion

			//Hacemos una arista a la siguiente (si es que hay)
			if (i < L - 1) instrucciones.ponArista(i, i + 1);
			break;

		case 'J':	//Instrucción de salto

			//Ponemos una arista entre la instrucción y el destino
			cin >> d;
			instrucciones.ponArista(i, d - 1);	
			break;

		case 'C':	//Salto condicional

			//Ponemos dos aristas una de la siguiente instrucción (si hay) por si no se realiza el salto
			//Otra a donde va si se realiza el salto

			cin >> d;
			instrucciones.ponArista(i, d - 1);
			if (i < L - 1) instrucciones.ponArista(i, i + 1);
			break;

		default:
			break;
		}

		datoInstr.insert({ i, inst1 });
	}

	TerminaProgramaOscuro fin(instrucciones, datoInstr);

	std::cout << '\n';

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
