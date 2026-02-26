#include <iostream>
using namespace std;

#include "submenuComplejidad.h"

int submenuComplejidad()
{
    int tipo;

    cout << "\n--- TIPO DE TAMANO ---\n";
    cout << "1. n\n";
    cout << "2. n*n\n";
    cout << "3. n*m\n";
    cout << "Seleccione: ";
    cin >> tipo;

    return tipo;
}