#include "EAITank.h"
#include "EGameManager.h"
#include "EPlayerController.h"
#include "ESceneManager.h"

namespace E3D
{
	EAITank::EAITank(const EString &name, const EString &meshName, EGameManager *gameMgr)
		:ETank(name,meshName,gameMgr)
	{
		mFireFrequency = 15;
		mSpeed *= 0.75f;
		setBulletType(BULLET_BALL);
		mTankType = TANK_AI;
	}

	void EAITank::onHited()
	{
		mCurrentLive += 26;
	}

	void EAITank::fire()
	{
		ETank::fire();
	}

	void EAITank::updateAI()
	{
		EVector3D lenght = getPosition() - mGameMgr->getPlayerController()->getPosition();
		if (lenght.squaredLength() < 1000.0f)
		{
			EFloat degree = lenght.angleBetween(mFireDir);
			degree = degree * 180.0f / PI - 180.0f;

			if (lenght.crossProduct(mFireDir).y > 0)//差乘主要计算 怪物和玩家的方向
			{
				degree = -degree;
			}
			if (Abs(degree) > 2.0f)
			{
				updateFireDir(degree);
				mHead->yaw(mHead->getRotateVec().y + degree);
			}
			fire();
		}
		else
		{
			fireAimRight();
		}

		if (!moveUp())
		{
			if (RandomInt() % 2 == 0)
				turnRight();
			else
				turnLeft();
		}
		else
		{
			EInt ran = RandomInt(0, 100);
			if (ran == 50)
			{
				turnRight();
			}
			else if(ran == 25)
			{
				turnLeft();
			}
		}

	}

	void EAITank::update()
	{
		ETank::update();
		updateAI();
	}
}