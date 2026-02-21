#include <iostream>
using namespace std;

#include "search.h"
#include "sort.h"
#include "view.h"

int main()
{
    int opcion;
    int metodo;
    int arreglo[10] = { 33, 5, 90, 12, 41, 8, 77, 20, 50, 62 };
    int n = 10;
    int posicion;
    int valor;
    int comparaciones = 0;
    int intercambios = 0;

    do
    {
        mostrarMenu();
        cin >> opcion;

        switch (opcion)
        {
            case 1:
                mostrarArreglo(arreglo, n);
                valor = pedirValor();
                posicion = busquedaSecuencial(arreglo, n, valor);

                if (posicion != -1)
                {
                    cout << "Valor encontrado en posicion: " << posicion << endl;
                }
                else
                {
                    cout << "Valor no encontrado.\n";
                }
                break;

            case 2:
                cout << "\nOrdenando arreglo...\n";
                ordenarBurbuja(arreglo, n);
                mostrarArreglo(arreglo, n);

                valor = pedirValor();
                posicion = busquedaBinaria(arreglo, n, valor);

                if (posicion != -1)
                {
                    cout << "Valor encontrado en posicion: " << posicion << endl;
                }
                else
                {
                    cout << "Valor no encontrado.\n";
                }   
                break;

            case 3:

                metodo = mostrarMenuOrdenamiento();
                
                
                if (metodo == 1)
                {
                    ordenarBurbuja(arreglo, n);
                }
                else if (metodo == 2)
                {
                    ordenarSeleccion(arreglo, n);
                }
                else if (metodo == 3)
                {
                    ordenarInsercion(arreglo, n);
                }
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
