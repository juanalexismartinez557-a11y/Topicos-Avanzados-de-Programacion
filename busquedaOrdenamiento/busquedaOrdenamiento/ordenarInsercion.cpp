#include <iostream>
using namespace std;

#include "ordenarInsercion.h"
#include "imprimirPaso.h"

void ordenarInsercion(int arreglo[], int n, bool mostrarProceso)
{
    int i, j, clave;

    for (i = 1; i < n; i++)
    {
        clave = arreglo[i];
        j = i - 1;

        if (mostrarProceso)
            cout << "Insertando " << clave << endl;

        while (j >= 0 && arreglo[j] > clave)
        {
            arreglo[j + 1] = arreglo[j];
            j--;

            if (mostrarProceso)
                imprimirPaso(arreglo, n);
        }

        arreglo[j + 1] = clave;

        if (mostrarProceso)
        {
            cout << "Estado -> " << endl;
            imprimirPaso(arreglo, n);
        }
    }
}