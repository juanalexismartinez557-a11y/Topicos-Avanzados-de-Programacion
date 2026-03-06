#include "CSVReader.h"
#include <fstream>
#include <sstream>
#include <iostream>

vector<Estudiante> leerCSV(string rutaArchivo)
{
    vector<Estudiante> lista;
    ifstream archivo(rutaArchivo);

    if (!archivo.is_open())
    {
        cout << "No se pudo abrir el archivo" << endl;
        cout << "Intentando abrir: " << rutaArchivo << endl;
        return lista;
    }

    string linea;
    getline(archivo, linea);

    while (getline(archivo, linea))
    {
        stringstream ss(linea);

        string nombre, apPat, apMat, matricula, curp;

        getline(ss, nombre, ',');
        getline(ss, apPat, ',');
        getline(ss, apMat, ',');
        getline(ss, matricula, ',');
        getline(ss, curp, ',');

        Estudiante e;

        e.nombre = nombre;
        e.apellidoPaterno = apPat;
        e.apellidoMaterno = apMat;
        e.matricula = matricula;
        e.curp = curp;

        lista.push_back(e);
    }

    archivo.close();
    return lista;
}