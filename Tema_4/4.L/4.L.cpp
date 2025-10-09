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
using namespace std;

#include "Grafo.h"

/*@ <answer>

 Sustituye este p�rrafo por un comentario general sobre la soluci�n,
 explicando c�mo se resuelve el problema y cu�l es el coste de la soluci�n,
 en funci�n del tama�o del problema.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo (despu�s de la marca)
 //@ <answer>

class MenosDinero {
private:
    vector<bool> visit;	//Vector de nodos visitados
    vector<int> ant;	//guarda el �ltimo v�rtice antes de llegar a v
    vector<int> dist;	//guarda el �ltimo v�rtice antes de llegar a v
    int s;				//Origen del grafo
    int l;				//Origen del grafo
    int t;				//Origen del grafo

    using Camino = std::deque<int>;

public:

	MenosDinero(Grafo& g, int s, int l, int t) : visit(g.V(), false),
		ant(g.V()), dist(g.V()), s(s), l(l), t(t) {
		bfs(g);

		//Buscamos el camino m�s corto desde la casa de Alex a la casa de Lucas
		Camino cam = camino(s, l);
		//Miramos tambi�n a qu� distancia est�
		int d = distancia(l);

		//Con estos datos quitamos de la cola la mitad para que queden a mitad de camino
		for (int i = 0; i < d / 2; i++) cam.pop_front();

		//Buscamos la distancia que hay desde el punto medio de sus casas a su trabajo
		cam = camino(cam.front(), t);

		//Probar si es m�s eficiente hacerlo buscando un camino en vez de esto
		d += cam.size() - 1;

		cout << d << '\n';

	}

	void bfs(Grafo& g) {
		queue<int> q;
		dist[s] = 0; visit[s] = true;
		q.push(s);

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

	//�Hay camino del origen a v?
	bool hayCamino(int v) const {
		return visit[v];
	}

	//Devuelve el camino m�s corto desde el origen a v (Si existe)
	Camino camino(int o, int v) const {
		if (!hayCamino(v)) throw domain_error("No existe camino");
		Camino cam;
		for (int x = v; x != o; x = ant[x]) {
			cam.push_front(x);
		}
			
		cam.push_front(o);
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
        luz.ponArista(d1 - 1, d2 - 1);  //Hacemos -1 porque los nodos est�n numerados de 1 a N
    }

	MenosDinero dinero(luz, A - 1, L - 1, T - 1);	//El origen va a ser la casa de Alex


    return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta l�nea ya no forma parte de la soluci�n.

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
