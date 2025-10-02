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

struct pT {     //Estructura para escribir la solución
    int c = 0;
    int pt = 0;
};

bool operator<(const canal& a, const canal& b) {
    return b.espectadores < a.espectadores;
}
bool operator<(const pT& a, const pT& b) {
    return b.pt > a.pt;
}

bool resuelveCaso() {

    // leemos la entrada
    int D, C, N;
    cin >> D >> C >> N;
    if (!cin) return false;

    // leer el resto del caso y resolverlo
    IndexPQ<int, canal> canales;    //Estructura donde guardamos los canales
    int datos;
    canal can;

    //Guardamos el estado de los canales en el minuto 0
    for (int i = 0; i < C; i++) {
        cin >> datos;
        can.espectadores = datos;

        canales.push(i + 1, can);   //Lo guardamos con i + 1 como id porque los canales van ordenados empezando en 1
    }

    //Empezamos el bucle del primeTime
    int min = 0;    //minuto de la última actualización
    int puntos = 0; //Tiempo de primetime a sumar
    int canal = 0;  //Para leer el canal que hay que actualizar
    int cont = 0;   //para saber cuanto tiempo llevamos de programa
    for (int i = 0; i < N; i++) {

        //Vemos cuantos minutos han pasado hasta la actualización
        cin >> datos;   //Minuto en el que se actualiza

        puntos = datos - min;
        cont += puntos;
        min = datos;

        //Se lo sumamos al top de los canales
        can = canales.top().prioridad;
        canales.update(canales.top().elem, { can.espectadores, can.primeTime + puntos }); 

        cin >> canal;
        //Hacemos la actualización
        while (canal != -1) {
            cin >> datos;
            can = canales.priority(canal);
            canales.update(canal, { datos, can.primeTime });    //Tengo la ligera sospecha de que esto me va a truncar mi primeTime del canal en vez de sumar
            cin >> canal;
        }
    }

    //El tiempo restante se lo sumamos al ultimo que se quedó en cabeza
    puntos = D - cont;
    can = canales.top().prioridad;
    canales.update(canales.top().elem, { can.espectadores, can.primeTime + puntos });

    priority_queue<pT> prime;

    for (int i = 0; i < C; i++) {
        if (canales.top().prioridad.primeTime > 0) {
            prime.push({ canales.top().elem, canales.top().prioridad.primeTime });
        }
        canales.pop();
    }

    datos = prime.size();
    for (int i = 0; i < datos; i++) {
        cout << prime.top().c << " " << prime.top().pt << '\n';
        prime.pop();
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
