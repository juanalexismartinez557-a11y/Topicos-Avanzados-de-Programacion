#pragma once
#include <vector>
#include <string>
#include "Estudiante.h"

using namespace std;

// Declaración de la función que leerá el CSV
vector<Estudiante> leerCSV(string rutaArchivo);