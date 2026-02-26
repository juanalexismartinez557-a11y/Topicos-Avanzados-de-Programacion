#include <iostream>
using namespace std;

#include "ordenarSeleccion.h"
#include "imprimirPaso.h"

void ordenarSeleccion(int arreglo[], int n, bool mostrarProceso)
{
    int i, j, min, temp;

    for (i = 0; i < n - 1; i++)
    {
        min = i;

        for (j = i + 1; j < n; j++)
        {
            if (mostrarProceso)
                cout << "Comparando " << arreglo[j]
                << " con minimo actual " << arreglo[min] << endl;

            if (arreglo[j] < arreglo[min])
                min = j;
        }

        temp = arreglo[i];
        arreglo[i] = arreglo[min];
        arreglo[min] = temp;

        if (mostrarProceso)
        {
            cout << "Colocando minimo -> ";
            imprimirPaso(arreglo, n);
        }
    }
}