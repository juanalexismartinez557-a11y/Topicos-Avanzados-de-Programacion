#include "ArchivoPersonas.h"
#include <fstream>

bool ArchivoPersonas::archivoVacio() {
    ifstream verificar("personas.txt");

    if (!verificar.is_open())
        return true;

    return verificar.peek() == ifstream::traits_type::eof();
}

void ArchivoPersonas::guardarPersona(Persona p, bool sobrescribir) {

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

vector<string> ArchivoPersonas::leerPersonas() {

    vector<string> lineas;

    ifstream lectura("personas.txt");
    string linea;

    while (getline(lectura, linea)) {
        lineas.push_back(linea);
    }

    lectura.close();

    return lineas;
}