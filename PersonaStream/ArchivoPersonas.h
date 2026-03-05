#pragma once
#include "Persona.h"
#include <vector>

using namespace std;

class ArchivoPersonas {
public:
    static bool archivoVacio();
    static void guardarPersona(Persona p, bool sobrescribir);
    static vector<string> leerPersonas();
};