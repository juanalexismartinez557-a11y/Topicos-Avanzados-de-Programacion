#pragma once
#include "ArchivoPersonas.h"

namespace PersonaForms {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class FormMostrar : public Form {

    private:
        TextBox^ txtContenido;

    public:

        FormMostrar() {

            this->Text = "Contenido del archivo";
            this->Width = 600;
            this->Height = 400;

            txtContenido = gcnew TextBox();
            txtContenido->Multiline = true;
            txtContenido->Dock = DockStyle::Fill;
            txtContenido->ScrollBars = ScrollBars::Vertical;

            this->Controls->Add(txtContenido);

            cargarDatos();
        }

        void cargarDatos() {

            vector<string> datos = ArchivoPersonas::leerPersonas();

            for (string linea : datos) {
                txtContenido->AppendText(gcnew String(linea.c_str()));
                txtContenido->AppendText(Environment::NewLine);
            }
        }
    };
}