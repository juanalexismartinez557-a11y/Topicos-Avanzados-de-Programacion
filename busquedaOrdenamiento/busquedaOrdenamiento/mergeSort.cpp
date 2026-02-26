#include <iostream>
using namespace std;

#include "mergeSort.h"
#include "imprimirPaso.h"

void merge(int arreglo[], int izquierda, int medio, int derecha,
    int& comparaciones, bool mostrarProceso)
{
    int i = izquierda;
    int j = medio + 1;
    int k = 0;
    int temp[100];

    if (mostrarProceso)
        cout << "\nFusionando subarreglos...\n";

    while (i <= medio && j <= derecha)
    {
        comparaciones++;

        if (arreglo[i] <= arreglo[j])
            temp[k++] = arreglo[i++];
        else
            temp[k++] = arreglo[j++];
    }

    while (i <= medio)
        temp[k++] = arreglo[i++];

    while (j <= derecha)
        temp[k++] = arreglo[j++];

    for (i = izquierda, k = 0; i <= derecha; i++, k++)
        arreglo[i] = temp[k];

    if (mostrarProceso)
    {
        cout << "Resultado parcial -> ";
        imprimirPaso(arreglo, derecha + 1);
    }
}

void mergeSort(int arreglo[], int izquierda, int derecha,
    int& comparaciones, bool mostrarProceso)
{
    if (izquierda < derecha)
    {
        int medio = (izquierda + derecha) / 2;

        mergeSort(arreglo, izquierda, medio, comparaciones, mostrarProceso);
        mergeSort(arreglo, medio + 1, derecha, comparaciones, mostrarProceso);
        merge(arreglo, izquierda, medio, derecha, comparaciones, mostrarProceso);
    }
}