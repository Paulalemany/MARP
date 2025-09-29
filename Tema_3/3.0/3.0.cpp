// 3.0.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "IndexPQ.h"

using namespace std;

int main()
{
    IndexPQ<string, int> cola;
    cola.push("Pedro", 50);
    cola.push("Marta", 100);
    cola.push("Luis", 40);
    cola.update("Pedro", 30);
    cola.push("Eva", 60);
    cout << cola.top().elem << '\n';  // debe salir Pedro
    cola.pop();
    cola.update("Marta", 10);
    cout << cola.top().elem << '\n';  // debe salir Marta
    cola.update("Marta", 70);
    cout << cola.top().elem << '\n';  // debe salir Luis

        
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
