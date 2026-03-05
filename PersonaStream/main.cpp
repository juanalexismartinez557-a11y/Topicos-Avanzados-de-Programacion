#include "FormPrincipal.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace PersonaForms;

[STAThreadAttribute]

int main(array<String^>^ args) {

    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    Application::Run(gcnew FormPrincipal());

    return 0;
}