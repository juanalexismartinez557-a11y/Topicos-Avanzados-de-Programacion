#include <iostream>
using namespace std;

#include "ordenarBurbuja.h"
#include "imprimirPaso.h"

void ordenarBurbuja(int arreglo[], int n, bool mostrarProceso)
{
    int i, j, temp;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - 1 - i; j++)
        {
            if (mostrarProceso)
                cout << "Comparando " << arreglo[j]
                << " y " << arreglo[j + 1] << endl;

            if (arreglo[j] > arreglo[j + 1])
            {
                temp = arreglo[j];
                arreglo[j] = arreglo[j + 1];
                arreglo[j + 1] = temp;

                if (mostrarProceso)
                {
                    cout << "Intercambio -> ";
                    imprimirPaso(arreglo, n);
                }
            }
        }
    }
}