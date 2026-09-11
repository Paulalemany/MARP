
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

 Estamos ante un problema que se puede resolver mediante colas de prioridad

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct bateria {
	int tiempo;
	int bateria;
	int id;
};

struct ordenBateria {
	bool operator()(const bateria a, const bateria b) {

		if (a.tiempo == b.tiempo)
			return a.id > b.id;

		return a.tiempo > b.tiempo;
	}
};

void simulacion(priority_queue<bateria, vector<bateria>, ordenBateria>& enUso, queue<bateria>& reserva, int Z, int T) {


	int i = 0;	//Tiempo de simulacion

	while (i < T) {	//Tiempo de la simulacion

		bateria b = enUso.top();
		enUso.pop();

		i = b.tiempo;

		//Se gasta la bateria
		//Gestionamos la recarga
		b.bateria -= Z;

		//Si la bateria es menor a 0 se descarta y se sustituye
		if (b.bateria <= 0 ) {

			if (!reserva.empty()) {

				b = reserva.front();
				reserva.pop();

				b.tiempo += i;
				enUso.push(b);
			}
		}
		else{

			//Actualizamos cuando se acabará
			b.tiempo += b.bateria;
			enUso.push(b);
		}
		
		if (!enUso.empty())
			i = enUso.top().tiempo;
	}

}

bool resuelveCaso() {
	// leer los datos de la entrada
	int B;

	cin >> B;

	if (!std::cin)  // fin de la entrada
		return false;

	priority_queue<bateria, vector<bateria>, ordenBateria> enUso;
	queue<bateria> reserva;

	bateria b;
	for (int i = 0; i < B; i++) {
		b.id = i + 1;
		cin >> b.tiempo;
		b.bateria = b.tiempo;

		enUso.push(b);
	}

	//Guardamos las baterias de repuesto
	int R;
	cin >> R;
	for (int i = 0; i < R; i++) {
		b.id = B + 1 + i;
		cin >> b.tiempo;
		b.bateria = b.tiempo;

		reserva.push(b);
	}

	int Z, T;
	cin >> Z >> T;

	// resolver el caso posiblemente llamando a otras funciones
	simulacion(enUso, reserva, Z, T);

	// escribir la solución
	if (enUso.size() == B) 
		cout << "CORRECTO\n";
	else if (enUso.empty()) 
		cout << "ABANDONEN INMEDIATAMENTE LA BASE\n";
	else 
		cout << "FALLO EN EL SISTEMA\n";

	//Ponemos las pilas
	while (!enUso.empty()) {
		cout << enUso.top().id << " " << enUso.top().tiempo << "\n";
		enUso.pop();
	}

	//Guiones del final
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
