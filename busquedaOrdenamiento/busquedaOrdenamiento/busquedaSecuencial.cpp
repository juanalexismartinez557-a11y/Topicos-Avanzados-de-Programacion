#include <iostream>
using namespace std;

#include "busquedaSecuencial.h"

int busquedaSecuencial(int arreglo[], int n, int valor, bool mostrarProceso)
{
    for (int i = 0; i < n; i++)
    {
        if (mostrarProceso)
            cout << "Comparando indice " << i << " -> " << arreglo[i] << endl;

        if (arreglo[i] == valor)
            return i;
    }
    return -1;
}