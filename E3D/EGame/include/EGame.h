#pragma once

#include "ECanvas.h"
#include "EInputListener.h"

namespace E3D
{
	class EGame:public ECanvas ,public EInputListener
	{
	public:
		EGame();
		
		virtual EBool keyPress(EInt key);
		virtual EBool keyRelease(EInt key);

		virtual EBool mouseButtonDown(EInt mouseButton) { return true; }
		virtual EBool mouseButtonRelease(EInt mouseButton) { return true; }
		virtual EBool mouseMove(EInt x, EInt y) { return true; }
		virtual EBool mouseWheel(EInt delta) { return true; }

		virtual void onPaint();
		virtual void update();
	protected:
		class ECamera	*camera;
		class EMesh		*plane;
		class ESceneManager *scene;
		class EPlayerController *player;
		class EGameManager		*gameMgr;
		virtual void createScene();
		void showInfo();
	protected:
		EInt				currentObjectNumber;
		EInt				visiblePolyons;
		EBool				showHelp;
		EInt				mLogicX, mLogicZ;
	private:

	};
}