#pragma once
#include "ECommon.h"
#include <Windows.h>

namespace E3D
{
	class EInputListener;
	class ECanvas;

	class EGameWindow
	{
	public:
		static EGameWindow *GWindow;

		void startLoop();

		EGameWindow(const EString& windowTitle,HINSTANCE instance);
		~EGameWindow();

		void showWindow(EBool show);
		void updateWindow();

		void quitApplication();
		HWND getHWND()const { return mHwnd; }
		HINSTANCE getInstance() { return mHinstance; }

		void addInputListener(EInputListener *listener);
		void removeInputListener(EInputListener *listener);

		void setCanvasListener(ECanvas *canvasListener);
	protected:
		static LRESULT WinProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

		virtual void onPaint(HDC hdc);
		virtual void onUpdate();
		virtual void onKeyDown(EInt msg);
		virtual void onKeyRelease(EInt msg);
		virtual void onMousePress(bool rightPress);
		virtual void onMouseMove(EInt x, EInt y);
		virtual void onMouseWheel(EInt delta);
	protected:
		bool registerWindow();
		bool createWindow();
	protected:
		HWND mHwnd;
		EString mWindowTitle;
		HINSTANCE mHinstance;
		std::vector<EInputListener*> mInputListeners;
		ECanvas						*mCanvasListener;
		EBool						 mQuit;
		typedef std::vector<EInputListener*>::iterator InputItr;


	};

}