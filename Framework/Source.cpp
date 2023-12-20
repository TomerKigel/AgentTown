#include "Framework.h"
//#include <windows.h>

int main()
{
	//ShowWindow(GetConsoleWindow(), SW_RESTORE); //SW_HIDE or SW_RESTORE

	cai::Framework fw;
	//adding optional systems
	fw.add_system(cai::Framework::systems::Communications);
	fw.add_system(cai::Framework::systems::Graphics);
	//running the framework with all components
	fw.run_all();
}

