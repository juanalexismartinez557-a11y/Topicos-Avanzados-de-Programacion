// PersonaStream.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream> //libreria para manejar archivos
#include <string>

using namespace std;

struct Persona { // struct donde se guardan los datos de la persona
    string nombres;
    string apellidoPaterno;
    string apellidoMaterno;
    string fechaNacimiento;
    string curp;
    string domicilio;
};

int main() {

    Persona p; // variable de tipo persona 

    char opcion; // variable para saber si se quiere sobrescribir
    bool sobrescribir = false;
    bool pedirDatos = false; // controla si se deben pedir datos al usuario

    ifstream verificar("personas.txt"); // se abre el archivo solo para verificar si ya tiene datos

    if (verificar.peek() == ifstream::traits_type::eof()) {
        // si el archivo esta vacio se deben pedir datos
        pedirDatos = true;
    }
    else {
        cout << "El archivo ya contiene datos." << endl;
        cout << "¿Desea sobrescribirlos? (s/n): ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 's' || opcion == 'S') {
            sobrescribir = true;
            pedirDatos = true; // solo si se quiere sobrescribir se vuelven a pedir datos
        }
    }

    verificar.close(); // se cierra el archivo de verificacion


    if (pedirDatos) { // solo entra aqui si se necesitan nuevos datos

        cout << "Ingrese nombre(s): "; // Para hacerlo mas dinamico se pide el nombre en lugar de tenerlo fijo
        getline(cin, p.nombres); // se van guardando los datos en la variable 

        cout << "Ingrese apellido paterno: ";
        getline(cin, p.apellidoPaterno);

        cout << "Ingrese apellido materno: ";
        getline(cin, p.apellidoMaterno);

        cout << "Ingrese fecha de nacimiento: ";
        getline(cin, p.fechaNacimiento);

        cout << "Ingrese CURP: ";
        getline(cin, p.curp);

        cout << "Ingrese domicilio: ";
        getline(cin, p.domicilio);

        ofstream archivo; // se crea un objeto de tipo ofstream para escribir en el archivo

        if (sobrescribir)
            archivo.open("personas.txt", ios::trunc); // si el usuario eligio sobrescribir se borra el contenido anterior
        else
            archivo.open("personas.txt", ios::app); // se abre el archivo en modo append para agregar los datos al final del archivo

        if (archivo.is_open()) { // se verifica que el archivo se haya abierto correctamente
            archivo << p.nombres << "," // se agregan los datos al archivo separados por comas para facilitar su lectura posteriormente
                << p.apellidoPaterno << ","
                << p.apellidoMaterno << ","
                << p.fechaNacimiento << ","
                << p.curp << ","
                << p.domicilio << endl;

            archivo.close(); // se cierra el archivo para liberar recursos y asegurar que los datos se guarden correctamente
            cout << "\nDatos guardados correctamente." << endl; // mensaje de confirmacion para el usuario
        }
        else {
            cout << "Error al abrir el archivo." << endl; // seguro por si algo esta mal
        }
    }

    // ahora se abre el archivo nuevamente pero en modo lectura para mostrar su contenido
    ifstream lectura("personas.txt");
    string linea;

    cout << "\nContenido actual del archivo:\n" << endl;

    while (getline(lectura, linea)) { // se leen todas las lineas del archivo
        cout << linea << endl; // se imprime cada linea
    }

    lectura.close(); // se cierra el archivo de lectura

    return 0;
}