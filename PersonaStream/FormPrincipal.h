#pragma once
#pragma once
#include "Persona.h"
#include "ArchivoPersonas.h"
#include "FormMostrar.h"

namespace PersonaForms {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class FormPrincipal : public Form {

    private:

        TextBox^ txtNombre;
        TextBox^ txtApP;
        TextBox^ txtApM;
        TextBox^ txtFecha;
        TextBox^ txtCurp;
        TextBox^ txtDomicilio;

        Button^ btnGuardar;

    public:

        FormPrincipal() {

            this->Text = "Registro de Persona";
            this->Width = 400;
            this->Height = 400;

            Label^ l1 = gcnew Label();
            l1->Text = "Nombre";
            l1->Top = 20;
            l1->Left = 20;

            txtNombre = gcnew TextBox();
            txtNombre->Top = 40;
            txtNombre->Left = 20;
            txtNombre->Width = 200;

            Label^ l2 = gcnew Label();
            l2->Text = "Apellido Paterno";
            l2->Top = 70;
            l2->Left = 20;

            txtApP = gcnew TextBox();
            txtApP->Top = 90;
            txtApP->Left = 20;

            Label^ l3 = gcnew Label();
            l3->Text = "Apellido Materno";
            l3->Top = 120;
            l3->Left = 20;

            txtApM = gcnew TextBox();
            txtApM->Top = 140;
            txtApM->Left = 20;

            Label^ l4 = gcnew Label();
            l4->Text = "Fecha nacimiento";
            l4->Top = 170;
            l4->Left = 20;

            txtFecha = gcnew TextBox();
            txtFecha->Top = 190;
            txtFecha->Left = 20;

            Label^ l5 = gcnew Label();
            l5->Text = "CURP";
            l5->Top = 220;
            l5->Left = 20;

            txtCurp = gcnew TextBox();
            txtCurp->Top = 240;
            txtCurp->Left = 20;

            Label^ l6 = gcnew Label();
            l6->Text = "Domicilio";
            l6->Top = 270;
            l6->Left = 20;

            txtDomicilio = gcnew TextBox();
            txtDomicilio->Top = 290;
            txtDomicilio->Left = 20;

            btnGuardar = gcnew Button();
            btnGuardar->Text = "Guardar";
            btnGuardar->Top = 320;
            btnGuardar->Left = 20;

            btnGuardar->Click += gcnew EventHandler(this, &FormPrincipal::guardar);

            this->Controls->Add(l1);
            this->Controls->Add(txtNombre);
            this->Controls->Add(l2);
            this->Controls->Add(txtApP);
            this->Controls->Add(l3);
            this->Controls->Add(txtApM);
            this->Controls->Add(l4);
            this->Controls->Add(txtFecha);
            this->Controls->Add(l5);
            this->Controls->Add(txtCurp);
            this->Controls->Add(l6);
            this->Controls->Add(txtDomicilio);
            this->Controls->Add(btnGuardar);
        }

    private:

        void guardar(Object^ sender, EventArgs^ e) {

            Persona p;

            p.nombres = msclr::interop::marshal_as<string>(txtNombre->Text);
            p.apellidoPaterno = msclr::interop::marshal_as<string>(txtApP->Text);
            p.apellidoMaterno = msclr::interop::marshal_as<string>(txtApM->Text);
            p.fechaNacimiento = msclr::interop::marshal_as<string>(txtFecha->Text);
            p.curp = msclr::interop::marshal_as<string>(txtCurp->Text);
            p.domicilio = msclr::interop::marshal_as<string>(txtDomicilio->Text);

            bool sobrescribir = false;

            if (!ArchivoPersonas::archivoVacio()) {

                auto resultado = MessageBox::Show(
                    "El archivo ya tiene datos ¿sobrescribir?",
                    "Confirmar",
                    MessageBoxButtons::YesNo
                );

                if (resultado == System::Windows::Forms::DialogResult::Yes)
                    sobrescribir = true;
            }

            ArchivoPersonas::guardarPersona(p, sobrescribir);

            FormMostrar^ mostrar = gcnew FormMostrar();
            mostrar->Show();
        }
    };
}