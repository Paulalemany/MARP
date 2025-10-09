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

	unordered_set<int> Al;
	unordered_set<int> Lu;
	unordered_set<int> Co;



    using Camino = std::deque<int>;

public:

	MenosDinero(Grafo& g, int s, int l, int t) : visit(g.V(), false),
		ant(g.V()), dist(g.V()), s(s), l(l), t(t) {
		bfs(g, s);

		//Buscamos el camino m�s corto desde la casa de Alex a la casa de Lucas
		//Miro el camino que debe Alex lucas al trabajo
		Camino camA = camino(s, t, Al);

		//Miro el camino que tiene que hacer lucas al trabajo
		for (int i = 0; i < visit.size(); i++) visit[i] = false;
		bfs(g, l);
 		Camino camL = camino(l, t, Lu);

		//Miramos donde coinciden	//Si el punto comun est� en el camino de alguno de los dos tomamos ese camino
		Camino cam = camino(l, s, Co);

		int decision = coinciden(camA, camL, cam);
		int d = 0;

		if (decision == -1) {	//No coinciden ninguno

			//Podemos o obligarlos a coinicidir  o que vayan por separado depende de que sea mejor
			d = 1;

		}
		else if (decision == 1) {	//Est� en ambos caminos
			//Si est� en ambos caminos ese punto es el punto de encuentro
			//El coste en luz ser� lo que tarda 1 de los dos en ir al trabajo m�s lo que tarda el otro en ir al punto de encuentro
			d += cam.size() - 1;
			d += camA.size() - 1;	///Podr�a ser tambi�n el otro el que haya que sumar? hay que verlo
		}
		else if (decision == 2) {	//Coincide con el camino de lucas
			d = camL.size() - 1;	//Luz de lo que se gasta en el camino de Lucas
			//Le sumamos lo que tarda Alex al punto comun
			d += cam.size() - 1;
			
		}
		else {	//Coincide con el camino de Alex
			d = camA.size() - 1;	//Luz que se gasta en el camino de alex
			//Le sumamos lo que tarda Lucas al punto comun
			int c = cam.size();
			d += c - 1;
		}

		cout << d - 1 << '\n';

	}

	int coinciden(Camino A, Camino L, Camino& comun) {

		int i = 0;
		int encontradoA = 0;
		int encontradoL = 0;
		while (i < comun.size() && encontradoA == 0 && encontradoL == 0) {
			encontradoA = Al.count(comun.front());
			encontradoL = Lu.count(comun.front());

			//Encontrado en ambos
			if (encontradoA == 1 && encontradoL == 1) return 0;		//Ambos caminos
			else if (encontradoA == 1) return 1;					//Camino de alex
			else if (encontradoL == 1) return 2;					//Camino de Lucas
			else comun.pop_front();
		}
		
		return -1;	//Ning�n camino
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

	//�Hay camino del origen a v?
	bool hayCamino(int v) const {
		return visit[v];
	}

	//Devuelve el camino m�s corto desde el origen a v (Si existe)
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
