/*@ <authors>
 *
 * MARP01 Paula Alemany Rodríguez
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
using namespace std;


/*@ <answer>

 Para solucionar este problema utilizamos una cola de prioridad
 que ordena en base a la densidad de musicos por partitura.
 Vamos repartiendo las partituras entre los diferentes instrumentos
 de manera que la densidad del que tenga mayor densidad sea cada vez menor
 hasta que nos quedemos sin partituras para repartir.

 La complejidad de este algoritmo es de O(m log n)
 siendo m el numero de partituras a repartir y
 siendo n el numero de instrumentos diferentes que hay

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>

//Struct que guarda la información de los grupos de instrumentos
struct instrumento {
    int musicos;
    int partituras = 1;
};

//Calcula numero de musicos por partitura
//Hacemos la suma y el -1 para asegurarnos de que nos da la parte más alta de la división
//O(1)
int densidad(const instrumento& a) {
    return (a.musicos + a.partituras - 1) / a.partituras;
}

//Queremos que el instrumento más prioritario sea aquel que tiene mayor densidad de musicos por partitura
//O(1)
bool operator<(const instrumento& a, const instrumento& b) {
    return densidad(a) < densidad(b);
}

//Vamos dandole partituras a aquellos grupos con mayor densidad de músicos
//Devolvemos el numero de integrantes del subgrupo mayoritarioç
//O(partituras log n) siendo partituras el numero de partituras a repartir 
// y siendo n el numero de distintos instrumentos que hay
int solucion(priority_queue<instrumento>& cola, int partituras) {

    //Vamos repartiendo las partituras a los grupos que tengan mayor densidad
    for (int i = 0; i < partituras; i++) {

        instrumento ins = cola.top();
        cola.pop();

        //Le sumamos una partitura más
        ins.partituras += 1;

        //Los volvemos a añadir a la cola
        cola.push(ins);
    }

    return densidad(cola.top());
}

bool resuelveCaso() {

    // leemos la entrada
    //P -> numero de partituras
    //N -> Grupos de musicos
    int P, N;
    cin >> P >> N;

    if (!cin)
        return false;

    // leer el resto del caso y resolverlo
    priority_queue<instrumento> cola;
    int dato = 0;
    int artistas = 0;
    instrumento ins;

    //Guardamos el número de músicos
    for (int i = 0; i < N; i++) {
        cin >> dato;
        artistas += dato;
        ins.musicos = dato;
        cola.push(ins);
    }

    //Calculamos las partituras que quedan por repartir
    //Teniendo en cuenta que minimo debe haber una por grupo
    int partRestantes = P - N;

    cout << solucion(cola, partRestantes) << '\n';
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
