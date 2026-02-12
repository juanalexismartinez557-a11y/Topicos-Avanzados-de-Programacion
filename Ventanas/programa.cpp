#include "MyForm1.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace OpenCVWinForms;

[STAThread]
int main(array<String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew MyForm1());
    return 0;
}
