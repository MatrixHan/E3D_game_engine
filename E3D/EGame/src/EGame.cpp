#include "EGame.h"
#include "ECamera.h"
#include "ELight.h"
#include "EMesh.h"
#include "ESceneManager.h"
#include "EGameManager.h"
#include "EPlayerController.h"

namespace E3D
{
	const static EString map001 = "map001.map";
	const static EString map002 = "map002.map";

	EGame::EGame() :plane(NULL), showHelp(false), scene(NULL),
		player(NULL), gameMgr(NULL), mLogicX(-1), mLogicZ(-1)
	{
		scene = new ESceneManager();
		gameMgr = new EGameManager(scene);
		player = gameMgr->getPlayerController();
		currentObjectNumber = 1;
		visiblePolyons = 0;
		createScene();
	}

	void EGame::createScene()
	{
		ELight *light = scene->createLight(LIGHT_DIRECTION);
		light->diffuse = EColor(255, 255, 255);
		light->direction = EVector4D(-1, -1, -1);
		light->shadowFactor = 0.5f;
		light->power = 1.5f;

		gameMgr->loadMap(map001);
		plane = scene->createMesh("Object2", "Plane_2.mesh");
		plane->setPosition(EVector3D(30,15.0f,30));

		gameMgr->startGame();
	}

	EBool EGame::keyPress(EInt key)
	{
		if (key == 'Y')
		{
			scene->enableLights(!scene->isLightsEnable());
		}
		else if (key == 'H')
		{
			showHelp = !showHelp;
		}
		else if (key == 'C')
		{
			if (gameMgr->getCurrentMapName() == map001)
				gameMgr->changeMap(map002);
			else
				gameMgr->changeMap(map001);

			plane = scene->createMesh("Object2", "Plane_2.mesh");
			player = gameMgr->getPlayerController();
		}
		else
		{
			player->keyPress(key);
		}
		return true;
	}

	EBool EGame::keyRelease(EInt key)
	{
		player->keyRelease(key);
		return true;
	}

	void EGame::update()
	{
		static EFloat degree = 0;
		degree += 10.f;
		plane->yaw(degree + 10.f);
		plane->setPosition(EVector3D(30 * sin(degree*0.01f), 15.0f, 30 * cos(degree*0.01f)));

		gameMgr->update();
		scene->update();

		mLogicX = player->getPosition().x;
		mLogicZ = player->getPosition().z;

		gameMgr->getLogicXZ(mLogicX,mLogicZ, mLogicX, mLogicZ);
	}

	void EGame::onPaint()
	{
		showInfo();
	}

	void EGame::showInfo()
	{
		currentObjectNumber = scene->getVisibleObjectNumber();
		visiblePolyons = scene->getVisiblePolyonNumber();

		if (showHelp)
		{
			scene->drawString("W A S D �ƶ�Tank",10,10);
			scene->drawString("<- ->", 10, 30);
			scene->drawString(" Space ����",10,50);
			scene->drawString("F   �л��߿�/ʵ��ģʽ", 10, 70);
			scene->drawString("Y ����/�رյƹ�", 10, 90);
			scene->drawString("G �л��ӵ�",10,110);
			scene->drawString("C �л�����", 10, 130);

			scene->drawString("��ǰ������:" + IntToString(scene->getVisibleObjectNumber()),650,10,EColor(255,255,255));
			scene->drawString("���е�����:" + IntToString(scene->getTotalPolyonNumber()), 650, 30, EColor(255, 255, 255));
			scene->drawString("�ɼ�������:" + IntToString(scene->getVisiblePolyonNumber()), 650, 50, EColor(255, 255, 255));
		}
		else
		{
			scene->drawString("H ��ʾ����", 10, 10);
		}

		scene->drawString("���ٵ���-" + IntToString(gameMgr->getDestroyEnemyNumber()), 20, 510, EColor(255, 255, 255));
		scene->drawString("ʣ�����-" + IntToString(gameMgr->getLastEnemyNumber()), 20, 530, EColor(0xffffff));
	}

}