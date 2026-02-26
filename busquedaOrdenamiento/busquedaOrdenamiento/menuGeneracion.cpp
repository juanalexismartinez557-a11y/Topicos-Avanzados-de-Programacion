#include <iostream>
using namespace std;

#include "menuGeneracion.h"

int menuGeneracion()
{
    int opcion;

    cout << "\n--- GENERADOR DE NUMEROS ---\n";
    cout << "1. Permitir repetidos\n";
    cout << "2. No permitir repetidos\n";
    cout << "Seleccione: ";
    cin >> opcion;

    return opcion;
}