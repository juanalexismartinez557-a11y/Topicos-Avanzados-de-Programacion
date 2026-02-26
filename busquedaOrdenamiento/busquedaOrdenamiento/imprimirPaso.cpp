#include <iostream>
using namespace std;

#include "imprimirPaso.h"

void imprimirPaso(int arreglo[], int n)
{
    for (int i = 0; i < n; i++)
        cout << arreglo[i] << " ";
    cout << endl;
}