#include "ArchivoPersonas.h"
#include <fstream>

using namespace std;

bool archivoTieneDatos() { // Función para verificar si el archivo ya contiene datos

    ifstream verificar("personas.txt");

    if (!verificar.is_open())
        return false;

    bool tieneDatos = verificar.peek() != ifstream::traits_type::eof();

    verificar.close();

    return tieneDatos;
}

void guardarPersona(Persona p, bool sobrescribir) { // Función para guardar los datos de una persona en el archivo, con opción de sobrescribir

    ofstream archivo;

    if (sobrescribir)
        archivo.open("personas.txt", ios::trunc);
    else
        archivo.open("personas.txt", ios::app);

    if (archivo.is_open()) {

        archivo << p.nombres << ","
            << p.apellidoPaterno << ","
            << p.apellidoMaterno << ","
            << p.fechaNacimiento << ","
            << p.curp << ","
            << p.domicilio << endl;

        archivo.close();
    }
}

vector<string> leerPersonas() { // Función para leer los datos de las personas almacenadas en el archivo y devolverlos como un vector de strings

    vector<string> datos;

    ifstream lectura("personas.txt");
    string linea;

    while (getline(lectura, linea)) {
        datos.push_back(linea);
    }

    lectura.close();

    return datos;
}