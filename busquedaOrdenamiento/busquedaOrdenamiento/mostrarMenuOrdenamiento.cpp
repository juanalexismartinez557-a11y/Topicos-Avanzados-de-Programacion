#include <iostream>
using namespace std;

#include "mostrarMenuOrdenamiento.h"

int mostrarMenuOrdenamiento()
{
    int opcion;

    cout << "\n=== METODOS DE ORDENAMIENTO ===\n";
    cout << "1. Burbuja\n";
    cout << "2. Seleccion\n";
    cout << "3. Insercion\n";
    cout << "4. QuickSort\n";
    cout << "5. MergeSort\n";
    cout << "Seleccione metodo: ";
    cin >> opcion;

    return opcion;
}