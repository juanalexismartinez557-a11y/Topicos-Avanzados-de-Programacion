#pragma once
#include "Persona.h"
#include <vector>

bool archivoTieneDatos();
void guardarPersona(Persona p, bool sobrescribir);
std::vector<std::string> leerPersonas();