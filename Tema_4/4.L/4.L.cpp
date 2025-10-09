/*@ <authors>
 *
 * MARP01 Paula Alemany
 *
 *@ </authors> */

#include <iostream>
#include <algorithm>
#include <fstream>
#include <deque>
#include <queue>
#include <unordered_set>
using namespace std;

#include "Grafo.h"

/*@ <answer>

 Sustituye este párrafo por un comentario general sobre la solución,
 explicando cómo se resuelve el problema y cuál es el coste de la solución,
 en función del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>

class MenosDinero {
private:
    vector<bool> visit;	//Vector de nodos visitados
    vector<int> ant;	//guarda el último vértice antes de llegar a v
    vector<int> dist;	//guarda el último vértice antes de llegar a v
    int s;				//Origen del grafo
    int l;				//Origen del grafo
    int t;				//Origen del grafo

	unordered_set<int> Al;
	unordered_set<int> Lu;
	unordered_set<int> Co;



    using Camino = std::deque<int>;

public:

	MenosDinero(Grafo& g, int s, int l, int t) : visit(g.V(), false),
		ant(g.V()), dist(g.V()), s(s), l(l), t(t) {
		bfs(g, s);

		//Buscamos el camino más corto desde la casa de Alex a la casa de Lucas
		//Miro el camino que debe Alex lucas al trabajo
		Camino camA = camino(s, t, Al);

		//Miro el camino que tiene que hacer lucas al trabajo
		for (int i = 0; i < visit.size(); i++) visit[i] = false;
		bfs(g, l);
 		Camino camL = camino(l, t, Lu);

		//Miramos donde coinciden	//Si el punto comun está en el camino de alguno de los dos tomamos ese camino
		Camino cam = camino(l, s, Co);

		int decision = coinciden(camA, camL, cam);
		int d = 0;

		if (decision == -1) {	//No coinciden ninguno

			//Podemos o obligarlos a coinicidir  o que vayan por separado depende de que sea mejor
			d = 1;

		}
		else if (decision == 2) {	//Coincide con el camino de lucas
			d = camL.size() - 1;	//Luz de lo que se gasta en el camino de Lucas
			//Le sumamos lo que tarda Alex al punto comun
			d += Camino(cam.front(), s).size() - 1;
		}
		else {	//Coincide con el camino de Alex
			d = camA.size() - 1;	//Luz que se gasta en el camino de alex
			//Le sumamos lo que tarda Lucas al punto comun
			int c = cam.size();
			d += c - 1;
		}


		////Miramos también a qué distancia está
		//int d = cam.size() - 1;

		////Con estos datos quitamos de la cola la mitad para que queden a mitad de camino
		//for (int i = 0; i < d / 2; i++) cam.pop_front();

		////Buscamos la distancia que hay desde el punto medio de sus casas a su trabajo
		//cam = camino(cam.front(), t);

		////Probar si es más eficiente hacerlo buscando un camino en vez de esto
		//d += cam.size() - 1;

		cout << d << '\n';

	}

	int coinciden(Camino A, Camino L, Camino& comun) {

		int i = 0;
		int encontrado = 0;
		while (i < comun.size() && encontrado == 0) {
			encontrado = Al.count(comun.front());
			if (encontrado == 0) Lu.count(comun.front());
			else return 1;	//Encontrado eb el camino de alex
			if (encontrado == 0) comun.pop_front();
			else return 2; //Encontrado en el camino de Lucas
		}
		
		return -1;	//No coincide con el camino de ninguno
	}

	void bfs(Grafo& g, int o) {
		queue<int> q;
		dist[o] = 0; visit[o] = true;
		q.push(o);

		while (!q.empty()) {
			int v = q.front(); q.pop();
			for (int w : g.ady(v)) {
				if (!visit[w]) {
					ant[w] = v;
					dist[w] = dist[v] + 1;
					visit[w] = true;
					q.push(w);
				}
			}
		}

	}

	//¿Hay camino del origen a v?
	bool hayCamino(int v) const {
		return visit[v];
	}

	//Devuelve el camino más corto desde el origen a v (Si existe)
	Camino camino(int o, int v, unordered_set<int>& set) const {
		if (!hayCamino(v)) throw domain_error("No existe camino");
		Camino cam;
		for (int x = v; x != o; x = ant[x]) {
			cam.push_front(x);
			set.insert(x);
		}
			
		cam.push_front(o);
		set.insert(o);
		return cam;
	}

	int distancia(int v) const {
		return dist[v];
	}
};

bool resuelveCaso() {

    // leemos la entrada
    int N, C, A, L, T;
    cin >> N >> C >> A >> L >> T;
    if (!cin)
        return false;

    // leer el resto del caso y resolverlo

    //Creamos el grafo y sus aristas
    Grafo luz(N);

    int d1, d2;
    for (int i = 0; i < C; i++) {
        cin >> d1 >> d2;
        luz.ponArista(d1 - 1, d2 - 1);  //Hacemos -1 porque los nodos están numerados de 1 a N
    }

	MenosDinero dinero(luz, A - 1, L - 1, T - 1);	//El origen va a ser la casa de Alex


    return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    if (!in.is_open())
        cout << "Error: no se ha podido abrir el archivo de entrada." << endl;
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif // !DOMJUDGE

    // Resolvemos
    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
#endif
    return 0;
}
