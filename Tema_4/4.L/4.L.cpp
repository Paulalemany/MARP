/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 * MARP99 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <algorithm>
using namespace std;

/*@ <answer>

 Sustituye este p�rrafo por un comentario general sobre la soluci�n,
 explicando c�mo se resuelve el problema y cu�l es el coste de la soluci�n,
 en funci�n del tama�o del problema.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo (despu�s de la marca)
 //@ <answer>



bool resuelveCaso() {

    // leemos la entrada
    int N, C, A, L, T;
    cin >> N >> C >> A >> L >> T;
    if (!cin)
        return false;

    // leer el resto del caso y resolverlo




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
