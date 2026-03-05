#include "MainForm.h"

using namespace System; // Espacio de nombres para tipos básicos como String
using namespace System::Windows::Forms; // Espacio de nombres para clases relacionadas con la interfaz gráfica de Windows Forms

[STAThread]

int main(array<String^>^ args)
{
	Application::EnableVisualStyles(); // Habilitar estilos visuales para la aplicación
	Application::SetCompatibleTextRenderingDefault(false); // Establecer el modo de renderizado de texto compatible

	PersonasGUI::MainForm form; // Crear una instancia del formulario principal de la aplicación
	Application::Run(% form); // Ejecutar la aplicación con el formulario principal

    return 0;
}