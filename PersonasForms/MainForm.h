#pragma once

#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>

#include "ArchivoPersonas.h"
#include <msclr/marshal_cppstd.h>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

namespace PersonasGUI {

    public ref class MainForm : public Form
    {
    public:
        MainForm()
        {
            InitializeComponent();
            verificarArchivo();
        }

    private:

		bool sobrescribirArchivo = false; // Variable para controlar si se deben sobrescribir los datos existentes

		// Controles de la interfaz
        Label^ lblNombre;
        Label^ lblApellidoP;
        Label^ lblApellidoM;
        Label^ lblFecha;
        Label^ lblCurp;
        Label^ lblDomicilio;
		// Campos de texto para ingresar los datos
        TextBox^ txtNombre;
        TextBox^ txtApellidoP;
        TextBox^ txtApellidoM;
        TextBox^ txtFecha;
        TextBox^ txtCurp;
        TextBox^ txtDomicilio;
		// Botones para guardar y mostrar los datos
        Button^ btnGuardar;
        Button^ btnMostrar;
		// Campo de texto para mostrar los datos almacenados
        TextBox^ txtMostrar;

		void InitializeComponent() // Método para inicializar los componentes de la interfaz
        {
            this->Text = "Registro de Personas";
            this->Size = Drawing::Size(600, 500);

            lblNombre = gcnew Label();
            lblNombre->Text = "Nombre(s)";
            lblNombre->Location = Point(20, 20);

            txtNombre = gcnew TextBox();
            txtNombre->Location = Point(150, 20);
            txtNombre->Width = 200;

            lblApellidoP = gcnew Label();
            lblApellidoP->Text = "Apellido paterno";
            lblApellidoP->Location = Point(20, 60);

            txtApellidoP = gcnew TextBox();
            txtApellidoP->Location = Point(150, 60);
            txtApellidoP->Width = 200;

            lblApellidoM = gcnew Label();
            lblApellidoM->Text = "Apellido materno";
            lblApellidoM->Location = Point(20, 100);

            txtApellidoM = gcnew TextBox();
            txtApellidoM->Location = Point(150, 100);
            txtApellidoM->Width = 200;

            lblFecha = gcnew Label();
            lblFecha->Text = "Fecha nacimiento";
            lblFecha->Location = Point(20, 140);

            txtFecha = gcnew TextBox();
            txtFecha->Location = Point(150, 140);
            txtFecha->Width = 200;

            lblCurp = gcnew Label();
            lblCurp->Text = "CURP";
            lblCurp->Location = Point(20, 180);

            txtCurp = gcnew TextBox();
            txtCurp->Location = Point(150, 180);
            txtCurp->Width = 200;

            lblDomicilio = gcnew Label();
            lblDomicilio->Text = "Domicilio";
            lblDomicilio->Location = Point(20, 220);

            txtDomicilio = gcnew TextBox();
            txtDomicilio->Location = Point(150, 220);
            txtDomicilio->Width = 200;

            btnGuardar = gcnew Button();
            btnGuardar->Text = "Guardar persona";
            btnGuardar->Location = Point(20, 270);
            btnGuardar->Click += gcnew EventHandler(this, &MainForm::guardarPersonaGUI);

            btnMostrar = gcnew Button();
            btnMostrar->Text = "Mostrar datos";
            btnMostrar->Location = Point(200, 270);
            btnMostrar->Click += gcnew EventHandler(this, &MainForm::mostrarDatos);

            txtMostrar = gcnew TextBox();
            txtMostrar->Multiline = true;
            txtMostrar->ScrollBars = ScrollBars::Vertical;
            txtMostrar->Location = Point(20, 320);
            txtMostrar->Size = Drawing::Size(540, 120);

            this->Controls->Add(lblNombre);
            this->Controls->Add(txtNombre);

            this->Controls->Add(lblApellidoP);
            this->Controls->Add(txtApellidoP);

            this->Controls->Add(lblApellidoM);
            this->Controls->Add(txtApellidoM);

            this->Controls->Add(lblFecha);
            this->Controls->Add(txtFecha);

            this->Controls->Add(lblCurp);
            this->Controls->Add(txtCurp);

            this->Controls->Add(lblDomicilio);
            this->Controls->Add(txtDomicilio);

            this->Controls->Add(btnGuardar);
            this->Controls->Add(btnMostrar);
            this->Controls->Add(txtMostrar);
        }

		void verificarArchivo() // Método para verificar si el archivo ya contiene datos y controlar la opción de sobrescribir
        {
            if (archivoTieneDatos())
            {
                auto resultado = MessageBox::Show(
                    "El archivo ya contiene datos.\n¿Desea sobrescribirlos?",
                    "Archivo existente",
                    MessageBoxButtons::YesNo,
                    MessageBoxIcon::Question
                );

                if (resultado == System::Windows::Forms::DialogResult::Yes)
                {
                    sobrescribirArchivo = true;
                }
                else
                {
                    sobrescribirArchivo = false;

                    // Desactivar campos de captura
                    txtNombre->Enabled = false;
                    txtApellidoP->Enabled = false;
                    txtApellidoM->Enabled = false;
                    txtFecha->Enabled = false;
                    txtCurp->Enabled = false;
                    txtDomicilio->Enabled = false;

                    btnGuardar->Enabled = false;

                    MessageBox::Show("Solo podrá visualizar los datos almacenados.");
                }
            }
        }

		void guardarPersonaGUI(Object^ sender, EventArgs^ e) // Método para guardar los datos de una persona ingresados en la interfaz, utilizando la función guardarPersona del archivo ArchivoPersonas.h
        {
            Persona p;

            p.nombres = msclr::interop::marshal_as<std::string>(txtNombre->Text);
            p.apellidoPaterno = msclr::interop::marshal_as<std::string>(txtApellidoP->Text);
            p.apellidoMaterno = msclr::interop::marshal_as<std::string>(txtApellidoM->Text);
            p.fechaNacimiento = msclr::interop::marshal_as<std::string>(txtFecha->Text);
            p.curp = msclr::interop::marshal_as<std::string>(txtCurp->Text);
            p.domicilio = msclr::interop::marshal_as<std::string>(txtDomicilio->Text);

            guardarPersona(p, sobrescribirArchivo);

            sobrescribirArchivo = false;

            MessageBox::Show("Datos guardados correctamente");
        }

		void mostrarDatos(Object^ sender, EventArgs^ e) // Método para mostrar los datos almacenados en el archivo, utilizando la función leerPersonas del archivo ArchivoPersonas.h
        {
            txtMostrar->Clear();

            std::vector<std::string> datos = leerPersonas();

            for (auto& linea : datos)
            {
                txtMostrar->AppendText(gcnew String(linea.c_str()));
                txtMostrar->AppendText("\r\n");
            }
        }
    };
}