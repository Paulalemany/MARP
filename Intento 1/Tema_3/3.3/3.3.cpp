
/*@ <authors>
 *
 * Paula, Alemany Rodríguez (MARP01).
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

using namespace std;

#include "PriorityQueue.h"  // propios o los de las estructuras de datos de clase


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct tarea {
	int inter = 0;	//Intervalo de tiempo
	int p = 0;		//Periodo de repetición
	int t = 0;		//Tiempo que le falta para empezar
};

bool operator<(const tarea& a, const tarea& b) {
	return a.t < b.t;
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int N, M, T;

	cin >> N >> M >> T;

	if (!std::cin)  // fin de la entrada
		return false;

	PriorityQueue<tarea> tareas;
	int cAux, fAux, pAux;

	for (int i = 0; i < N; i++) {
		cin >> cAux >> fAux;
		//Metemos la tarea a la cola de prioridad solo si empieza dentro del periodo
		if (cAux < T) tareas.push({ fAux - cAux, 0, cAux});	//Metemos la tarea a la cola de prioridad
	}

	for (int i = 0; i < M; i++) {
		cin >> cAux >> fAux >> pAux;
		//Metemos la tarea a la cola de prioridad solo si empieza dentro del periodo
		if (cAux < T) tareas.push({ fAux - cAux, pAux, cAux});
	}

	bool superposicion = false;
	tarea enCurso;

	while (!superposicion && tareas.size() > 1) {
		enCurso = tareas.top();
		tareas.pop();

		//Vemos si hay superposicion
		//Hay superoposición solo si el inicio 
		// de la siguiente es estrictamente menor que el final de la actual
		superposicion = tareas.top().t < enCurso.t + enCurso.inter;	

		if (!superposicion && enCurso.p > 0) {	//Si no hay superposición y es periodica volvemos a insertar
			
			enCurso.t += enCurso.p;	//Calculamos cuando le vuelve a tocar
			//Con que comiencen antes de T ya las tenemos en cuenta
			if (enCurso.t < T) tareas.push(enCurso);	//Si seguimos dentro del tiempo a comprobar la añadimos
		}
	}

	if(superposicion) cout << "SI\n";
	else cout << "NO\n";

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
