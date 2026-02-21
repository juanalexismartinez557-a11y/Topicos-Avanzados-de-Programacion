#include <iostream>
using namespace std;

#include "search.h"
#include "sort.h"
#include "view.h"
#include "numerosRandom.h"   // ← nuevo

int main()
{
    int opcion;
    int metodo;

    // Arreglo principal (capacidad máxima)
    int arreglo[1000];
    int n = 0;

    int posicion;
    int valor;
    int comparaciones = 0;
    int intercambios = 0;

    bool mostrarProceso;

	// aqui se muestra el menu de generacion de numeros y se generan los datos

    cout << "=== CONFIGURACION INICIAL ===\n";

    int opGen = menuGeneracion();   // repetidos o no
    bool repetir = (opGen == 1);

    int tipo = submenuComplejidad(); // n, n*n, n*m

    generarNumeros(arreglo, n, repetir, tipo);

    if (n <= 0)
    {
        cout << "Error al generar datos. Finalizando.\n";
        return 0;
    }

    cout << "\nNumeros generados:\n";
    mostrarArreglo(arreglo, n);

	// aqui pregunta si se desea mostrar el proceso de los algoritmos o no
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
            mostrarArreglo(arreglo, n);
            valor = pedirValor();
            posicion = busquedaSecuencial(arreglo, n, valor, mostrarProceso);

            if (posicion != -1)
                cout << "Valor encontrado en posicion: " << posicion << endl;
            else
                cout << "Valor no encontrado.\n";
            break;

        case 2: // Busqueda Binaria
            cout << "\nOrdenando arreglo con Burbuja...\n";
            ordenarBurbuja(arreglo, n, mostrarProceso);

            mostrarArreglo(arreglo, n);

            valor = pedirValor();
            posicion = busquedaBinaria(arreglo, n, valor, mostrarProceso);

            if (posicion != -1)
                cout << "Valor encontrado en posicion: " << posicion << endl;
            else
                cout << "Valor no encontrado.\n";
            break;

        case 3: // Ordenar arreglo
            metodo = mostrarMenuOrdenamiento();

            comparaciones = 0;
            intercambios = 0;

            if (metodo == 1)
            {
                ordenarBurbuja(arreglo, n, mostrarProceso);
            }
            else if (metodo == 2)
            {
                ordenarSeleccion(arreglo, n, mostrarProceso);
            }
            else if (metodo == 3)
            {
                ordenarInsercion(arreglo, n, mostrarProceso);
            }
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
            {
                cout << "Metodo invalido.\n";
            }

            cout << "\nArreglo ordenado:\n";
            mostrarArreglo(arreglo, n);
            break;

        case 4:
            cout << "Saliendo...\n";
            break;

        default:
            cout << "Opcion invalida.\n";
        }

    } while (opcion != 4);

    return 0;
}