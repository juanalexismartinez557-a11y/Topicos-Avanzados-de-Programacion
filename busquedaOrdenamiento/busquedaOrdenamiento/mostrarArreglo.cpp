#include <iostream>
using namespace std;

#include "mostrarArreglo.h"

void mostrarArreglo(int arreglo[], int n)
{
    cout << "\nArreglo: ";
    for (int i = 0; i < n; i++)
        cout << arreglo[i] << " ";

    cout << endl;
}