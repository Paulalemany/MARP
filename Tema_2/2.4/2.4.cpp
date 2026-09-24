
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

 Para resolver este problema utilizamos el struct paciente en el cual se guarda la siguiente información:
	- Nombre: El nombre del paciente para poder escribirlo
	- ID: Se les otorga el id para saber que pacientes han llegado primero
	- Gravedad: Para saber el nivel de urgencia
Con ello creamos una cola de prioridad que ordene a los pacientes de mayor a menor gravedad y, en caso
de que tengan la misma gravedad, se le da prioridad a aquel con el id más bajo ya que eso significa que 
lleva más tiempo esperando.

El bucle que va interando sobre los eventos (ingresar paciente o antender) tiene el siguiente coste:
	- Coste en espacio: O(P) Siendo P el numero de pacientes a atender.
	- Coste en tiempo: O(N log p) siendo N el numero de eventos a tratar y p el numero de pacientes
		- Por insertar en una cola de prioridad el caso peor es O(log p) siendo p el numero de pacientes
		en la cola.
		- Por eliminar a un paciente atendido igual O(log p) siendo p el numero de pacientes en la cola.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct paciente {
	string nombre;
	int id;
	int gravedad;
};

//El mas prioritario es el que tenga la mayor gravedad o en su defecto el que tenga el id mas bajo
//(Si tiene el id mas bajo es que lleva mas tiempo esperando
bool operator<(paciente const& a, paciente const& b) {
	return b.gravedad < a.gravedad ||
		(b.gravedad == a.gravedad && b.id > a.id);	//Aqui a lo mejor la estoy liando por cambiar el comparador
}

bool operator>(paciente const& a, paciente const& b) {
	return b < a;
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int N;

	cin >> N;

	if (N == 0)
		return false;

	priority_queue<paciente, vector<paciente>, greater<paciente>> pacientes;

	char dato;
	int id = 0;
	string nombre;
	int gravedad;

	for (int i = 0; i < N; i++) {
		cin >> dato;
		if (dato == 'I') {	//Ingresamos a un nuevo paciente
			cin >> nombre >> gravedad;
			pacientes.push({ nombre, id, gravedad });
			id++;
		}
		else {
			//Atendemos a un nuevo paciente
			cout << pacientes.top().nombre << '\n';
			pacientes.pop();
		}
	}

	cout << "---\n";

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
