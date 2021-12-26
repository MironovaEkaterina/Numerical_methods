#include "Lab1.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace Lab;
[STAThread]

int main(array < System::String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew Lab1());
	return 0;
}

