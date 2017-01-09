#pragma once
#include "ECommon.h"
#include <list>
#include <vector>

namespace E3D
{
	enum SOUND_TYPE
	{
			SOUND_BACKGROUND,
			SOUND_FIRE,
			SOUND_EXPLODE,
	};

	class EMesh;
	class EBullet;
	class ETank;
	class EPlayerController;
	class ESceneManager;
	class EGameManager
	{
		typedef std::list<EBullet*>::iterator BulletItr;
		typedef std::list<ETank*>::iterator TankItr;

	public:
		EGameManager(ESceneManager* scene);
		~EGameManager();

		void startGame(EInt maxEnemyNumber =10);
		EBool isGameBegin()const { return mMaxEnemyNumber>0; }
		EBool finishGame()const;

		EInt getDestroyEnemyNumber()const {return mCurrentEnemyNumber;}
		EInt getLastEnemyNumber()const { return mMaxEnemyNumber - mCurrentEnemyNumber; }

		EBullet * createBullet(ETank * owner);
		void destroyBullet(EBullet* bullet);

		ETank * createAITank(const EVector3D &pos);
		EPlayerController *getPlayerController() { return mMainPlayer; }

		void playSound(SOUND_TYPE sound, EBool loop = false);

		ESceneManager* getSceneManager() { return mScene; }
		EBool loadMap(const EString &mapName);
		void changeMap(const EString &mapName);
		EString getCurrentMapName()const { return mCurMap; }

		EFloat getMapWidth()const { return mXL; }
		EFloat getMapHeight()const { return mZL; }

		EBool canGo(EFloat x, EFloat z);
		void getLogicXZ(EFloat x,EFloat z,EInt &outX,EInt &outZ);

		EMesh* checkObject(EFloat x, EFloat z);

		ETank* checkTank(EFloat x, EFloat y, EFloat z);
		void update();
	protected:
		ESceneManager			*mScene;
		std::list<EBullet*>		mBullets;
		std::list<ETank*>		mTanks;
		EPlayerController		*mMainPlayer;

		EString					mCurMap;
		EFloat					mBlockSize;
		EInt					mX, mZ;
		EFloat					mHXL, mHZL;
		EFloat					mXL, mZL;

		std::vector<std::vector<EInt>>   mCollisionValue;
		std::vector<std::vector<EMesh*>> mCollisionMeshs;

		EMesh					*mTerrainMesh;
		EInt					mCurrentEnemyNumber;
		EInt					mMaxEnemyNumber;
		EInt					mVisibleEnemyNumber;

	};
}