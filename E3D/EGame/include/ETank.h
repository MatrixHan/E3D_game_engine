#pragma once

#include "EObject.h"
#include "ESceneManager.h"
#include <list>

namespace E3D
{
	enum BulletType
	{
		BULLET_BALL,
		BULLET_ROCKET,
	};

	enum TankType
	{
		TANK_AI,
		TANK_PALYER,
	};

	class EBullet;
	class ECamera;
	class EGameManager;

	class ETank :public EObject
	{
		typedef std::list<EBullet*>::iterator BulletItr;
	public:
		virtual ~ETank();

		void move(const EVector3D &mov);
		EBool moveUp();
		EBool moveDown();
		
		void turnRight();
		void turnLeft();

		void fireAimLeft();
		void fireAimRight();

		EVector3D getPosition() const { return mBody->getPosition(); }
		void setPosition(const EVector3D &pos);

		void yaw(EFloat degree);

		void setBulletType(BulletType bullType) { mBulletType = bullType; }
		BulletType getBulletType()const { return mBulletType; }
		TankType getTankType() { return mTankType;}

		EBool	isVisible() const { return mBody->isVisible(); }

		void setVisible(EBool visible);
		
		EBool	intersect(const EVector3D &point);

		virtual void onHited();

		virtual void fire();
		virtual void update();
		EVector3D getCameraStep()const { return mMoveVec; }

	protected:
		friend class EGameManager;
		friend class EPlayerController;
		ETank(const EString &name, const EString &meshName, EGameManager *gameMgr);

		void updateFireDir(EFloat degree);
			 
	protected:
		EMesh			*mHead;
		EMesh			*mBody;
		EVector3D		mMoveVec;
		EVector3D		mFireDir;
		EFloat			mSpeed;
		EFloat			mFireFrequency;

		EInt			mLastFire;
		EFloat			mColOffset;

		ESceneManager	*mSceneManager;
		EGameManager	*mGameMgr;
		BulletType		mBulletType;
		TankType		mTankType;

	};
}
