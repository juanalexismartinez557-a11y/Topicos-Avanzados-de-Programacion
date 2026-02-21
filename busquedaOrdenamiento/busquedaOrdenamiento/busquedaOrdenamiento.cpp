#include <iostream>
using namespace std;

#include "search.h"
#include "sort.h"
#include "view.h"
#include "numerosRandom.h"

int main()
{
    int opcion;
    int metodo;
    int arreglo[1000];   // capacidad maxima
    int n = 0;
    int posicion;
    int valor;
    int comparaciones = 0;
    int intercambios = 0;

	// menu principal
    do
    {

        // Generacion inicial de numeros

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

        mostrarMenu();
        cin >> opcion;

        switch (opcion)
        {
        case 1: // BUSQUEDA SECUENCIAL
            mostrarArreglo(arreglo, n);
            valor = pedirValor();
            posicion = busquedaSecuencial(arreglo, n, valor);

            if (posicion != -1)
                cout << "Valor encontrado en posicion: " << posicion << endl;
            else
                cout << "Valor no encontrado.\n";
            break;

        case 2: // BUSQUEDA BINARIA
            cout << "\nOrdenando arreglo...\n";
            ordenarBurbuja(arreglo, n);
            mostrarArreglo(arreglo, n);

            valor = pedirValor();
            posicion = busquedaBinaria(arreglo, n, valor);

            if (posicion != -1)
                cout << "Valor encontrado en posicion: " << posicion << endl;
            else
                cout << "Valor no encontrado.\n";
            break;

        case 3: // ORDENAMIENTO
            metodo = mostrarMenuOrdenamiento();

            comparaciones = 0;
            intercambios = 0;

            if (metodo == 1)
                ordenarBurbuja(arreglo, n);
            else if (metodo == 2)
                ordenarSeleccion(arreglo, n);
            else if (metodo == 3)
                ordenarInsercion(arreglo, n);
            else if (metodo == 4)
            {
                quickSort(arreglo, 0, n - 1, comparaciones, intercambios);
                cout << "Comparaciones: " << comparaciones << endl;
                cout << "Intercambios: " << intercambios << endl;
            }
            else if (metodo == 5)
            {
                mergeSort(arreglo, 0, n - 1, comparaciones);
                cout << "Comparaciones: " << comparaciones << endl;
            }
            else
            {
                cout << "Metodo invalido.\n";
                break;
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