#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unordered_set>
using namespace std;

#include "generarNumeros.h"

void generarNumeros(int arreglo[], int& n, bool repetir, int tipo)
{
    srand(time(0));

    int m;
    int total = 0;

    if (tipo == 1)
    {
        cout << "Ingrese n: ";
        cin >> n;
        total = n;
    }
    else if (tipo == 2)
    {
        cout << "Ingrese n: ";
        cin >> n;
        total = n * n;
    }
    else if (tipo == 3)
    {
        cout << "Ingrese n: ";
        cin >> n;
        cout << "Ingrese m: ";
        cin >> m;
        total = n * m;
    }
    else
    {
        cout << "Opcion invalida.\n";
        n = 0;
        return;
    }

    if (total > 100000)
    {
        cout << "Error: excede el tamaño maximo permitido (100000).\n";
        n = 0;
        return;
    }

    unordered_set<int> usados;

    for (int i = 0; i < total; i++)
    {
        int num = rand() % 100000;

        if (!repetir)
        {
            while (usados.count(num))
                num = rand() % 100000;

            usados.insert(num);
        }

        arreglo[i] = num;
    }

    n = total;
}