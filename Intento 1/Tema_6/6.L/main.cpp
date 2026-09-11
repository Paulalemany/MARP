/*@ <authors>
 *
 * MARP01 Paula Alemany
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#include "GrafoValorado.h"
#include "PriorityQueue.h"
#include "ConjuntosDisjuntos.h"

/*@ <answer>
 
 Para solucionar este problema he utilizado un Grafo valorado y he buscado el camino de mínimo coste entre sus nodos.
 Para hacerlo más eficiente si una carretera es más cara que hacer un nuevo aeropuerto obviamos esta carretera como si no existiera,
 de esta manera el número de aeropuertos será el número de componentes conexas del grafo valorado. Todo esto lo hacemos coon ayuda del
 algoritmo dfs y de Kruskal.

 El coste de resolver un caso es el coste del algoritmo de Kruskal + el coste del dfs, es decir
 O(A log A) + O(N + A) siendo A el número de aristas y N el número de nodos del grafo
 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo (después de la marca)
//@ <answer>

template <typename Valor>
class ARM_Kruskal {
private:
    std::vector<Arista<Valor>> _ARM;
    Valor coste;
    vector<bool> visit;
    int comp;

    // visita los nodos alcanzables desde v respetando el umbral
    //Coste dfs O(N + A) siendo N el número de nodos y A el número de aristas
    void dfs(GrafoValorado<int> const& G, int v, int umbral) {
        visit[v] = true;
        for (auto a : G.ady(v)) {
            if (a.valor() < umbral) {
                int w = a.otro(v);
                if (!visit[w])
                    dfs(G, w, umbral);
            }
        }
    }
public:
    Valor costeARM() const {
        return coste;
    }
    std::vector<Arista<Valor>> const& ARM() const {
        return _ARM;
    }

    int compo() const {
        return comp;
    }

    //Coste Krustal O(A log A) siendo A las aristas del grafo
    ARM_Kruskal(GrafoValorado<Valor> const& g, int A) : coste(0), visit(g.V(), false), comp(0) {

        comp = componentes(g, A);
        PriorityQueue<Arista<Valor>> pq(g.aristas());
        ConjuntosDisjuntos cjtos(g.V());
        while (!pq.empty()) {
            auto a = pq.top(); pq.pop();
            int v = a.uno(), w = a.otro(v);
            if (!cjtos.unidos(v, w)) {
                cjtos.unir(v, w);
                _ARM.push_back(a); coste += a.valor();
                if (_ARM.size() == g.V() - 1) break;
            }
        }
    }

    //Coste O(C * N + A) siendo C el número de componentes conexas y N + A el coste del dfs
    int componentes(GrafoValorado<Valor> const& g, int A) {
        int comp = 0; 
        int i = 0;

        while (i < g.V()) {
            if (!visit[i]) {
                dfs(g, i, A);
                comp++;
            }
            i++;
        }
        
        return comp;
    }
};


bool resuelveCaso() {
  
  // leemos la entrada
  int N, M, A;
  cin >> N >> M >> A;
  if (!cin)
    return false;

  // leer el resto del caso y resolverlo
  int x, y, c;
  GrafoValorado <int> p(N);

  for (int i = 0; i < M; i++) {
      cin >> x >> y >> c;
      if (c < A ) p.ponArista(Arista <int>(x - 1, y - 1, c));
  }

  ARM_Kruskal <int> k(p, A);

  int coste = A * k.compo() + k.costeARM();
  cout << coste << " " << k.compo() << '\n';
  
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
#endif
  
  // Resolvemos
  while (resuelveCaso());
  
  // para dejar todo como estaba al principio
#ifndef DOMJUDGE
  cin.rdbuf(cinbuf);
#endif
  return 0;
}
