#pragma once

#include <vector>
#include <string>
#include "Estudiante.h"
#include "CSVReader.h"
#include "Ordenamiento.h"

#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>

namespace ProyectoCSV {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class Form1 : public System::Windows::Forms::Form
    {
    public:
        Form1(void)
        {
            InitializeComponent();

            // Inicializar el vector
            lista = new std::vector<Estudiante>();
        }

    private:

        DataGridView^ tabla;
        Button^ botonCargar;
        Button^ botonOrdenar;

        // vector como puntero (necesario en C++/CLI)
        std::vector<Estudiante>* lista;

        void InitializeComponent(void)
        {
            this->tabla = gcnew DataGridView();
            this->botonCargar = gcnew Button();
            this->botonOrdenar = gcnew Button();

            // TABLA
            this->tabla->Location = Point(20, 20);
            this->tabla->Size = System::Drawing::Size(600, 300);
            this->tabla->ColumnCount = 5;

            this->tabla->Columns[0]->Name = "Nombre";
            this->tabla->Columns[1]->Name = "Apellido Paterno";
            this->tabla->Columns[2]->Name = "Apellido Materno";
            this->tabla->Columns[3]->Name = "Matricula";
            this->tabla->Columns[4]->Name = "CURP";

            // BOTON CARGAR
            this->botonCargar->Text = "Cargar CSV";
            this->botonCargar->Location = Point(20, 340);
            this->botonCargar->Click += gcnew EventHandler(this, &Form1::cargarCSV);

            // BOTON ORDENAR
            this->botonOrdenar->Text = "Ordenar por Nombre";
            this->botonOrdenar->Location = Point(150, 340);
            this->botonOrdenar->Click += gcnew EventHandler(this, &Form1::ordenarDatos);

            // AGREGAR CONTROLES
            this->Controls->Add(this->tabla);
            this->Controls->Add(this->botonCargar);
            this->Controls->Add(this->botonOrdenar);

            this->Text = "Lectura de CSV";
            this->Size = System::Drawing::Size(700, 450);
        }

        void mostrarTabla()
        {
            tabla->Rows->Clear();

            for (auto& e : *lista)
            {
                tabla->Rows->Add(
                    gcnew String(e.nombre.c_str()),
                    gcnew String(e.apellidoPaterno.c_str()),
                    gcnew String(e.apellidoMaterno.c_str()),
                    gcnew String(e.matricula.c_str()),
                    gcnew String(e.curp.c_str())
                );
            }
        }

        System::Void cargarCSV(System::Object^ sender, System::EventArgs^ e)
        {
            std::string ruta = "Estudiantes.csv";

            *lista = leerCSV(ruta);

            mostrarTabla();
        }

        System::Void ordenarDatos(System::Object^ sender, System::EventArgs^ e)
        {
            ordenar(*lista, 1); // ordenar por nombre

            mostrarTabla();
        }
    };
}