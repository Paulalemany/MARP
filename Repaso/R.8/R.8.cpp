
/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/*@ <answer>

 Nos encontramos ante un problema que se puede solucionar mediante un algoritmo voraz
 El número mínimo de alumnos que se van a necesitar es según el número máximo de actividades
 que ocurren al mismo tiempo.

 Para realizar esto primero guardamos las actividades en una cola de prioridad de minimos
 que se ordena por la hora a la que comienzan las actividades siendo primero las que empiezan antes
 Despues tenemos otra cola de prioridad que guarda las tareas que ya han comenzado en orden creciente de 
 finalización, es decir, las tareas que terminan antes primero.

 El algoritmo funciona de la siguiente manera:
	Cuando una nueva actividad va a comenzar primero se comprueba si las que estaban en curso
	han terminado, de ser así se eliminan de la cola. Si no han terminado se encuentran a simultaneamente
	varias actividades por lo que el tamaño de la cola es el numero de alumnos que se necesitan. 
	Al final restamos uno porque el alumno que esta organizando no cuenta solo le interesan los
	alumnos extra que necesita.

Este algoritmo tiene un coste de O(N log n) siendo N el numero de actividades

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


struct CompareFirst {
	// Devuelve true si 'a' debe ir DESPUÉS de 'b' (es decir, si a es "mayor" en prioridad)
	// Para min-heap basado en el primer elemento:
	bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) {
		return a.first > b.first;
	}
};

struct CompareSecond {
	// Devuelve true si 'a' debe ir DESPUÉS de 'b' (es decir, si a es "mayor" en prioridad)
	// Para min-heap basado en el primer elemento:
	bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) {
		return a.second > b.second;
	}
};

using horario = std::priority_queue<pair<int,int>, vector<pair<int, int>>, CompareFirst>;
using simultanea = std::priority_queue<pair<int, int>, vector<pair<int, int>>, CompareSecond>;


int minAlumnos(horario actividades) {

	//Actividades en curso
	simultanea enCurso;

	int max = 0;
	while (!actividades.empty()) {

		//comprobamos si las tareas anteriores terminan antes de poner esta
		if (!enCurso.empty()) {

			//Mientras las tareas en curso finalicen antes que el principio de la de ahora
			//Eliminamos las tareas porque ya han terminado
			while (!enCurso.empty() && enCurso.top().second <= actividades.top().first) 
				enCurso.pop();
			
		}

		enCurso.push(actividades.top()); //Comienza una nueva tarea
		max = std::max((int)enCurso.size(), max);

		actividades.pop();
	}

	//Restamos 1 porque el alumno que lo organiza no cuenta
	return max - 1;
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int N;

	cin >> N;

	if (N == 0)
		return false;

	horario actividades;
	int c, f;
	for (int i = 0; i < N; i++) {
		cin >> c >> f;
		//actividades.push({ c, f });
		actividades.push({ c,f });
	}

	
	cout << minAlumnos(actividades) << '\n';

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
