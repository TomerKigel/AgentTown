#include "AI_Elements/agent.h"
#include "Graphics_Engine//GameEngine.h"
#include "Framework/Framework.h"
#include <windows.h>

int main()
{
	ShowWindow(GetConsoleWindow(), SW_RESTORE); //SW_HIDE or SW_RESTORE
	Framework fw;
	fw.start();
}

