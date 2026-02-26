#include <iostream>
using namespace std;

#include "quickSort.h"
#include "imprimirPaso.h"

void quickSort(int arreglo[], int izquierda, int derecha,
    int& comparaciones, int& intercambios, bool mostrarProceso)
{
    int i = izquierda;
    int j = derecha;
    int pivote = arreglo[(izquierda + derecha) / 2];
    int temp;

    if (mostrarProceso)
        cout << "\nQuickSort con pivote: " << pivote << endl;

    while (i <= j)
    {
        while (arreglo[i] < pivote)
        {
            i++;
            comparaciones++;
        }

        while (arreglo[j] > pivote)
        {
            j--;
            comparaciones++;
        }

        if (i <= j)
        {
            temp = arreglo[i];
            arreglo[i] = arreglo[j];
            arreglo[j] = temp;
            intercambios++;

            if (mostrarProceso)
            {
                cout << "Intercambio -> ";
                imprimirPaso(arreglo, derecha + 1);
            }

            i++;
            j--;
        }
    }

    if (izquierda < j)
        quickSort(arreglo, izquierda, j, comparaciones, intercambios, mostrarProceso);

    if (i < derecha)
        quickSort(arreglo, i, derecha, comparaciones, intercambios, mostrarProceso);
}