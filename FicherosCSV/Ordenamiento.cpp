#include "Ordenamiento.h"
#include <algorithm>

void ordenar(vector<Estudiante>& lista, int campo)
{
    sort(lista.begin(), lista.end(),
        [campo](const Estudiante& a, const Estudiante& b)
        {
            switch (campo)
            {
            case 1: return a.nombre < b.nombre;
            case 2: return a.apellidoPaterno < b.apellidoPaterno;
            case 3: return a.apellidoMaterno < b.apellidoMaterno;
            case 4: return a.matricula < b.matricula;
            case 5: return a.curp < b.curp;
            default: return false;
            }
        });
}