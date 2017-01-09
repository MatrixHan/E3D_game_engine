#include "EGraphics.h"
#include "EWindow.h"
#include "EMeshUtil.h"
#include "EUtil.h"
#include "EGame.h"
#include "../resource.h"

using namespace E3D;

int WINAPI WinMain(HINSTANCE hInstance,      // handle to current instance
	HINSTANCE hPrevInstance,  // handle to previous instance
	LPSTR lpCmdLine,          // command line
	int nCmdShow              // show state
)
{
	InitLog("E3D.log");
	EGraphics::initGraphics(hInstance);
	Log("Graphics Init");
	EGameWindow::GWindow = new EGameWindow("E3D(3DTank)", hInstance);
	EGameWindow::GWindow->showWindow(true);

	HWND hwnd = EGameWindow::GWindow->getHWND();
	LONG iconID = (LONG)LoadIcon(::GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON_TANKWAR));
	//::SetClassLongPtr(hwnd, GCL_HICON, iconID);

	EGame *game = new EGame;
	EGameWindow::GWindow->setCanvasListener(game);
	EGameWindow::GWindow->addInputListener(game);
	EGameWindow::GWindow->startLoop();
	Log("Shutdown Graphics...");
	EGraphics::shutdownGraphics();
	CloseLog();
	return 0;
}