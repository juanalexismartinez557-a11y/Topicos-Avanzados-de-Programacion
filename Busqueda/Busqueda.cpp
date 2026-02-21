#include <iostream>
using namespace std;

// Función de búsqueda binaria
int busquedaBinaria(int arr[], int n, int objetivo) {
    int inicio = 0, fin = n - 1;
    while (inicio <= fin) {
        int medio = inicio + (fin - inicio) / 2;
        if (arr[medio] == objetivo) {
            return medio; // Elemento encontrado
        }
        else if (arr[medio] < objetivo) {
            inicio = medio + 1; // Buscar en la mitad derecha
        }
        else {
            fin = medio - 1; // Buscar en la mitad izquierda
        }
    }
    return -1; // Elemento no encontrado
}

int main() {
    // Arreglo ordenado
    int arr[] = { 10, 12, 15, 25, 50, 100 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int objetivo = 17;

    int resultado = busquedaBinaria(arr, n, objetivo);

    if (resultado != -1) {
        cout << "Elemento encontrado en la posición: " << resultado << endl;
    }
    else {
        cout << "Elemento no encontrado." << endl;
    }

    return 0;
}