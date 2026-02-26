#include <iostream>
#include <chrono>
#include <ctime>
#include <cstdlib>

using namespace std;
using namespace std::chrono;

// SEARCH
#include "busquedaSecuencial.h"
#include "busquedaBinaria.h"

// SORT
#include "ordenarBurbuja.h"
#include "ordenarSeleccion.h"
#include "ordenarInsercion.h"
#include "quickSort.h"
#include "mergeSort.h"

// VIEW
#include "mostrarMenu.h"
#include "mostrarArreglo.h"
#include "pedirValor.h"
#include "mostrarMenuOrdenamiento.h"

// RANDOM
#include "menuGeneracion.h"
#include "submenuComplejidad.h"
#include "generarNumeros.h"

int main()
{
    srand(time(0)); // ✔ Semilla inicial UNA sola vez

    int opcion;
    int metodo;

    int arreglo[100000];
    int n = 0;

    int posicion;
    int valor;
    int comparaciones = 0;
    int intercambios = 0;

    bool mostrarProceso;

    // CONFIGURACION INICIAL
    cout << "=== CONFIGURACION INICIAL ===\n";

    int opGen = menuGeneracion();
    bool repetir = (opGen == 1);

    int tipo = submenuComplejidad();

    generarNumeros(arreglo, n, repetir, tipo);

    if (n <= 0)
    {
        cout << "Error al generar datos. Finalizando.\n";
        return 0;
    }

    cout << "\nNumeros generados:\n";
    mostrarArreglo(arreglo, n);

    cout << "\n¿Deseas ver el proceso de los algoritmos? (1=Si, 0=No): ";
    cin >> mostrarProceso;

    // MENU PRINCIPAL
    do
    {
        mostrarMenu();
        cin >> opcion;

        switch (opcion)
        {
        case 1: // Busqueda Secuencial
        {
            mostrarArreglo(arreglo, n);
            valor = pedirValor();

            auto inicio = high_resolution_clock::now();

            posicion = busquedaSecuencial(arreglo, n, valor, mostrarProceso);

            auto fin = high_resolution_clock::now();
            duration<double, milli> tiempo = fin - inicio;

            if (posicion != -1)
                cout << "Valor encontrado en posicion: " << posicion << endl;
            else
                cout << "Valor no encontrado.\n";

            cout << "Tiempo: " << tiempo.count() << " ms\n";
            break;
        }

        case 2: // Busqueda Binaria
        {
            auto inicioOrden = high_resolution_clock::now();
            ordenarBurbuja(arreglo, n, mostrarProceso);
            auto finOrden = high_resolution_clock::now();

            duration<double, milli> tiempoOrden = finOrden - inicioOrden;
            cout << "Tiempo Burbuja: " << tiempoOrden.count() << " ms\n";

            mostrarArreglo(arreglo, n);

            valor = pedirValor();

            auto inicioBusq = high_resolution_clock::now();
            posicion = busquedaBinaria(arreglo, n, valor, mostrarProceso);
            auto finBusq = high_resolution_clock::now();

            duration<double, milli> tiempoBusq = finBusq - inicioBusq;

            if (posicion != -1)
                cout << "Valor encontrado en posicion: " << posicion << endl;
            else
                cout << "Valor no encontrado.\n";

            cout << "Tiempo Busqueda Binaria: " << tiempoBusq.count() << " ms\n";
            break;
        }

        case 3: // Ordenar arreglo
        {
            metodo = mostrarMenuOrdenamiento();
            comparaciones = 0;
            intercambios = 0;

            auto inicio = high_resolution_clock::now();

            if (metodo == 1)
                ordenarBurbuja(arreglo, n, mostrarProceso);
            else if (metodo == 2)
                ordenarSeleccion(arreglo, n, mostrarProceso);
            else if (metodo == 3)
                ordenarInsercion(arreglo, n, mostrarProceso);
            else if (metodo == 4)
            {
                quickSort(arreglo, 0, n - 1, comparaciones, intercambios, mostrarProceso);
                cout << "Comparaciones: " << comparaciones << endl;
                cout << "Intercambios: " << intercambios << endl;
            }
            else if (metodo == 5)
            {
                mergeSort(arreglo, 0, n - 1, comparaciones, mostrarProceso);
                cout << "Comparaciones: " << comparaciones << endl;
            }
            else
                cout << "Metodo invalido.\n";

            auto fin = high_resolution_clock::now();
            duration<double, milli> tiempo = fin - inicio;

            cout << "\nTiempo: " << tiempo.count() << " ms\n";
            mostrarArreglo(arreglo, n);
            break;
        }

        case 4:
            cout << "Saliendo...\n";
            break;

        default:
            cout << "Opcion invalida.\n";
        }

    } while (opcion != 4);

    return 0;
}