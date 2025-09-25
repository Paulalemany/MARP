/*@ <authors>
 *
 * MARP01 Paula Alemany Rodríguez
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include <queue>
using namespace std;


/*@ <answer>

 Para hacer la solución más eficiente primero si el numero de partituras 
 es igual al numero de instrumentos nos ahorramos calculos y devolvemos 
 el grupo con más músicos por lo que el coste seria O(1).
 Por otro lado cuando no es así repartimos una partitura a cada grupo y repartimos las restantes
 al grupo más grande hasta que se equilibren poco a poco. La complejidad en este caso es O(N) siendo N 
 las partituras restantes después de darle una partitura a cada grupo

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>

struct mus {
    int N = 0; //numero de músicos
    int P = 0; //numero de partituras
    int res = 0;
};

bool operator<(const mus& a, const mus& b) {
    return (a.N / a.P) + a.res < (b.N / b.P + b.res);
}

bool resuelveCaso() {

    // leemos la entrada
    int P, N;
    cin >> P >> N;

    if (!cin)
        return false;

    // leer el resto del caso y resolverlo
    priority_queue<mus> cola;
    int dato = 0;
    mus instrumento;

    //Guardamos el número de músicos

    for (int i = 0; i < N; i++) {

        cin >> dato;
        instrumento.N = dato;
        instrumento.P = 1;
        cola.push(instrumento);
    }

    priority_queue<int> sol;

    if (P == N) cout << cola.top().N << '\n';     //Si solo hay una partitura por instrumento el que más músicos tenga será el que buscamos
    else {
        int res = P - N;    //Las partituras que faltan por repartir por prioridad son las que quedan después de darle una a cada instrumento
        mus mus;

        for (int i = 0; i < res; i++) {

            mus = cola.top();
            cola.pop();
            mus.P++;
            if (((mus.N + mus.res) % mus.P != 0) && (mus.res == 0)) mus.res += 1;
            else if (((mus.N + mus.res) % mus.P == 0 && mus.res == 1)) mus.res--;   //Si la división es exacta no hay que sumarle el resto
            cola.push(mus);
        }

        cout << (cola.top().N / cola.top().P + cola.top().res) << '\n';
    }

    return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    if (!in.is_open())
        cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
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
