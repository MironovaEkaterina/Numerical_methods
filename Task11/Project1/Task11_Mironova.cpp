#include "Task11_Mironova.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace Project1;
[STAThread]

int main(array < System::String^> ^ args){
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew Task11_Mironova());
	return 0;
}

