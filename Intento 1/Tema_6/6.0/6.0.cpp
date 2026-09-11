#include <iostream>
#include "ConjuntosDisjuntos.h"

int main()
{
    //Partición unitaria de 10 elementos
    ConjuntosDisjuntos prueba(10);

    //Mostrar contenido del vector id[] si utiliza "búsqueda rápida"
    //Voy a mostrar p[] que es lo que nos da la clase
    prueba.mostrarP();
    std::cout << "\n";

    ///El unir actual es el de por tamaños
    //Se unen los siguientes elementos 9-0 3-4 5-8 7-2 2-1 5-7 0-3 4-2
    std::cout << "Unimos 9 - 0\n";
    prueba.unir(9, 0);
    prueba.mostrarP();
    std::cout << "\n";

    std::cout << "Unimos 3 - 4\n";
    prueba.unir(3, 4);
    prueba.mostrarP();
    std::cout << "\n";

    std::cout << "Unimos 5 - 8\n";
    prueba.unir(5, 8);
    prueba.mostrarP();
    std::cout << "\n";

    std::cout << "Unimos 7 - 2\n";
    prueba.unir(7, 2);
    prueba.mostrarP();
    std::cout << "\n";

    std::cout << "Unimos 2 - 1\n";
    prueba.unir(2, 1);
    prueba.mostrarP();
    std::cout << "\n";

    std::cout << "Unimos 5 - 7\n";
    prueba.unir(5, 7);
    prueba.mostrarP();
    std::cout << "\n";

    std::cout << "Unimos 0 - 3\n";
    prueba.unir(0, 3);
    prueba.mostrarP();
    std::cout << "\n";

    std::cout << "Unimos 4 - 2\n";
    prueba.unir(4, 2);
    prueba.mostrarP();
    std::cout << "\n";

}
