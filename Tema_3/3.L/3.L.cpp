/*@ <authors>
 *
 * MARP01 Paula Alemany Rodríguez
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

#include "IndexPQ3L.h"


/*@ <answer>

 Para hacer este problema he creado una cola de prioridad variable que se ordene según el número de espectadores por canal,
 los datos de los canales (espectadores y prime time) se guardan en un struct que es la prioridad de la cola.
 Una vez guardado el estado inicial de los canales vemos lo que ocurre en cada actualización; primero le sumamos el intervalo de tiempo
 al canal que estaba en primera posición antes de la actualización, luego hacemos los respectivos cambios en los canales y repetimos hasta que no haya más actualizaciones.
 Una vez se han acabado las actuaizaciones le sumamos los minutos restantes (D) al canal que se encuentra en la primera posición.
 Para escribirlo guardamos los canales que han tenido algún minuto de prime time en una nueva cola de prioridad siendo la prioridad el primeTime del canal.

 Para la complejidad del algoritmo primero tenemos un bucle que mira cada actualización, por lo tanto se repite N veces y dentro de este un while que se repite entre 1 y C veces
 por lo tanto C veces en el caso peor. Por otro lado dentro de estos bucles la función con más coste es update() que tiene un coste de O(log n). 
 Es por ello que la complejidad de ete algoritmo de es O(N (c log n))

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>

struct canal {  //Estructura que guarda la información del canal
    int espectadores = 0;
    int primeTime = 0;
};

struct sol {
    int canal = 0;
    int primeTime = 0;
};

bool operator>(const canal& a, const canal& b) {
    return a.espectadores > b.espectadores;
}

bool operator>(const sol& a, const sol& b) {
    return (a.primeTime > b.primeTime) ||
        ((a.primeTime == b.primeTime) &&
            (a.canal < b.canal));
}

bool resuelveCaso() {

    // leemos la entrada
    int D, C, N;
    cin >> D >> C >> N;
    if (!cin) return false;

    // leer el resto del caso y resolverlo  
    IndexPQ<int, canal> canales;

    //Guardamos el estado inicial de los espectadores en el minuto 0
    int datos;
    canal cnl;

    for (int i = 0; i < C; i++) {
        cin >> datos;
        cnl.espectadores = datos;
        canales.push(i + 1, { cnl.espectadores,0 });
    }

    //Vamos con las actualizaciones
    int min = 0;    //minuto de la última actualización
    int puntos = 0; //Tiempo de primetime a sumar
    int c = 0;  //Para leer el canal que hay que actualizar
    int ult = 0;   //para saber cuanto tiempo llevamos de programa

    for (int i = 0; i < N; i++) {

        //Sumamos el tiempo de primeTime que lleva el canal en primera posición
        cin >> min;

        puntos = min - ult;
        ult = min;  //La ultima actualización ahora es la actual

        canales.update(canales.top().elem,
            { canales.top().prioridad.espectadores,
            canales.top().prioridad.primeTime + puntos });

        //Vemos el nuevo orden de los canales
        while (cin >> c && c != -1) {
            cin >> datos;
            canales.update(c, {datos, canales.priority(c).primeTime});
        }
    }

 
    //El tiempo restante se lo sumamos al ultimo que se quedó en cabeza
    puntos = D - ult;
    canales.update(canales.top().elem,
        { canales.top().prioridad.espectadores,
        canales.top().prioridad.primeTime + puntos });

    IndexPQ <int, sol> s;
    while (!canales.empty()) {
        s.push(canales.top().elem, { canales.top().elem, canales.top().prioridad.primeTime });
        canales.pop();
    }

    //Escribimos la solución
    while (!s.empty()) {
        if (s.top().prioridad.primeTime > 0)
            cout << s.top().elem << " " << s.top().prioridad.primeTime << "\n";
        s.pop();
    }
     
    cout << "---\n";


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
