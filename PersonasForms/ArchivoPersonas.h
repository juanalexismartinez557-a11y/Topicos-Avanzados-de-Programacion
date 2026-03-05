#pragma once
#include "Persona.h"
#include <vector>

bool archivoTieneDatos(); // Función para verificar si el archivo ya contiene datos
void guardarPersona(Persona p, bool sobrescribir); // Función para guardar los datos de una persona en el archivo, con opción de sobrescribir
std::vector<std::string> leerPersonas(); // Función para leer los datos de las personas almacenadas en el archivo y devolverlos como un vector de strings