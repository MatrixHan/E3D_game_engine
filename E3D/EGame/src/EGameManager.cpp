#include "EGameManager.h"
#include "EBullet.h"
#include "ETank.h"
#include "EPlayerController.h"
#include "ESceneManager.h"
#include "EAITank.h"

namespace E3D
{
	const EString Bullet_Ball = "BallBullet.mesh";
	const EString Bullet_Rocket = "RocketBullet.mesh";

	const EVector3D InitPosition(-20.0f, 1.0f, 15.0f);
	const EVector3D RandomPos[3] = { EVector3D(10,1.5f,10),
									EVector3D(45,1.5f,-5),
									EVector3D(-20,1.5f,45) };
	EGameManager::EGameManager(ESceneManager* scene)
		:mScene(scene), mBlockSize(0.0f), mX(0), mZ(0), mTerrainMesh(NULL), mCurrentEnemyNumber(0),
		mMaxEnemyNumber(0), mVisibleEnemyNumber(3)
	{
		mMainPlayer = new EPlayerController(this);
		mMainPlayer->setPosition(InitPosition);

		EBullet* bullet = new EBullet(NULL, "RocketBullet.mesh", this);
		bullet->setVisible(false);
		bullet = new EBullet(NULL, "BallBullet.mesh", this);
		bullet->setVisible(false);
	}

	EGameManager::~EGameManager()
	{
		SafeDelete(mMainPlayer);
		for (BulletItr itr = mBullets.begin(); itr != mBullets.end(); ++itr)
		{
			SafeDelete(*itr);
		}
		for (TankItr itr = mTanks.begin(); itr != mTanks.end(); ++itr)
		{
			SafeDelete(*itr);
		}
		mBullets.clear();
		mTanks.clear();
	}

	void EGameManager::startGame(EInt maxEnemyNumber /* =10 */)
	{
		for (BulletItr itr = mBullets.begin(); itr != mBullets.end(); ++itr)
			(*itr)->mCurrentLive = (*itr)->mMaxLive + 1;
		for (TankItr itr = mTanks.begin(); itr != mTanks.end(); ++itr)
			(*itr)->mCurrentLive = (*itr)->mMaxLive + 1;

		mMaxEnemyNumber = maxEnemyNumber;
		mCurrentEnemyNumber = 0;
	}

	EBool EGameManager::finishGame()const
	{
		return mCurrentEnemyNumber == mMaxEnemyNumber;
	}

	EBullet* EGameManager::createBullet(ETank * owner)
	{
		EString meshName = (owner->getBulletType() == BULLET_ROCKET ? Bullet_Rocket : Bullet_Ball);
		EBullet *bullet = new EBullet(owner, meshName, this);
		if (meshName == Bullet_Ball)
		{
			bullet->setScale(EVector3D(1.5f, 1.5f, 1.5f)); 
		}
		mBullets.push_back(bullet);
		return bullet;
	}

	void EGameManager::destroyBullet(EBullet* bullet)
	{
		bullet->mCurrentLive = bullet->mMaxLive + 1;
	}

	ETank *EGameManager::createAITank(const EVector3D &pos)
	{
		static EInt ID = 0;
		EString name = "AI#" + IntToString(ID++);
		ETank* tank = new EAITank(name,"Tank1",this);
		tank->setPosition(pos);
		mTanks.push_back(tank);
		return tank;
	}

	void EGameManager::update()
	{
		if (isGameBegin() && !finishGame())
		{
			if ((EInt)mTanks.size() < mVisibleEnemyNumber)
			{
				EInt curNum = (EInt)mTanks.size();
				for (EInt i = 0; i < mVisibleEnemyNumber - curNum; i++)
				{
					if (mCurrentEnemyNumber + (EInt)mTanks.size() < mMaxEnemyNumber)
							createAITank(RandomPos[0,2]);
				}
			}
			for (TankItr itr = mTanks.begin(); itr != mTanks.end();)
			{
				if ((*itr)->isAlive())
				{
					(*itr)->update();
					++itr;
				}
				else
				{
					mCurrentEnemyNumber++;
					SafeDelete(*itr);
					mTanks.erase(itr++);
				}
			}
		}

		for (BulletItr itr = mBullets.begin(); itr != mBullets.end();)
		{
			if ((*itr)->isAlive())
			{
				(*itr)->update();
				++itr;
			}
			else
			{
				SafeDelete(*itr);
				mBullets.erase(itr++);
			}
		}
		mMainPlayer->update();
	}

	void EGameManager::changeMap(const EString &mapName)
	{
		SafeDelete(mMainPlayer);
		for (BulletItr itr = mBullets.begin(); itr != mBullets.end(); ++itr)
		{
			SafeDelete(*itr);
		}
		for (TankItr itr = mTanks.begin(); itr != mTanks.end(); ++itr)
		{
			SafeDelete(*itr);
		}
		mBullets.clear();
		mTanks.clear();
		mCollisionValue.clear();
		mCollisionMeshs.clear();
		mCurrentEnemyNumber = 0;
		mScene->clearMesh();

		mMainPlayer = new EPlayerController(this);
		mMainPlayer->setPosition(InitPosition);
		loadMap(mapName);
	}

	EString getBlock(const EString& line, char ltip, char rtip)
	{
		EInt beg = line.find(ltip);
		EInt end = line.rfind(rtip);
		return line.substr(beg + 1, end - beg - 1);
	}
	EVector3D getPos(const EString &line)
	{
		EInt xb = line.find("X");
		EInt yb = line.find("Y");
		EInt zb = line.find("Z");
		EInt end = line.find("/");

		EString xs = line.substr(xb + 3, yb - 5 - xb);
		EString ys = line.substr(yb + 3, zb - 5 - yb);
		EString zs = line.substr(zb + 3, end - zb - 5);

		return EVector3D(StringToFloat(xs), StringToFloat(ys), StringToFloat(zs));
	}

	void getXZ(const EString &line, EInt &x, EInt &z, EFloat &blockSize)
	{
		EInt xb = line.find("X");
		EInt zb = line.find("Z");
		EInt sb = line.find("Size");
		EInt end = line.find("/");
		EString xs = line.substr(xb + 3, zb - 5 - xb);
		EString zs = line.substr(zb + 3, sb - 5 - zb);
		EString ss = line.substr(sb + 6, end - sb - 8);

		x = StringToFloat(xs);
		z = StringToFloat(zs);
		blockSize = StringToFloat(ss);
	}

	void getValue(const EString &line, EInt &x, EInt &z, EInt &value)
	{
		EInt xb = line.find("X");
		EInt zb = line.find("Z");
		EInt sb = line.find("Value");
		EInt end = line.find("/");
		EString xs = line.substr(xb + 3, zb - 5 - xb);
		EString zs = line.substr(zb + 3, sb - 5 - zb);
		EString ss = line.substr(sb + 7, end - sb - 9);

		x = StringToFloat(xs);
		z = StringToFloat(zs);
		value = StringToFloat(ss);
	}

	EBool EGameManager::loadMap(const EString &mapName)
	{
		mCurMap = mapName;

		mCollisionMeshs.clear();
		mCollisionValue.clear();

		std::ifstream in;
		in.open(GetPath(mapName).c_str());

		if (in.bad())
		{
			in.close();
			return false;
		}
		char line[256];
		while (in.good())
		{
			EString info;
			in.getline(line, 256);
			info = Trim(line);

			int beg = 0, end = -1;
			if (info.find("Config") != -1)
			{
				EString mapName = getBlock(info, '\"', '\"');

				in.getline(line, 256);
				info = Trim(line);
				EString meshName = getBlock(info, '>', '<') + ".mesh";
				in.getline(line, 256);

				getXZ(line, mX, mZ, mBlockSize);
				mXL = mX*mBlockSize;
				mZL = mZ*mBlockSize;
				mHXL = mXL / 2.0f;
				mHZL = mZL / 2.0f;

				for (EInt i = 0; i <= mZ; i++)
				{
					mCollisionValue.push_back(std::vector<EInt>(mX + 1, 0));
					mCollisionMeshs.push_back(std::vector<EMesh*>(mX + 1, 0));
				}

				in.getline(line, 256);
				mTerrainMesh = mScene->createMesh(mapName, meshName);
				mTerrainMesh->setCullFlag(false);
			}

			in.getline(line, 256);
			info = Trim(line);

			if (info.find("Nodes") != -1)
			{
				in.getline(line, 256);
				info = Trim(line);
				while (info.find("Node") != -1)
				{
					int i = info.find("</Nodes>");
					if(i!=-1)
						break;
					EString nodeName = getBlock(info, '\"', '\"');
					in.getline(line, 256);
					info = Trim(line);
					EString meshName = getBlock(info, '>', '<') + ".mesh";

					in.getline(line, 256);
					info = Trim(line);
					EVector3D pos = getPos(info);
					EMesh * object = mScene->createMesh(nodeName, meshName);
					object->setPosition(pos);

					in.getline(line, 256);
					EInt x, z, value;
					getValue(line, x, z, value);
					if (value >= mCollisionValue[z][x])
					{
						mCollisionValue[z][x] = value;
						mCollisionMeshs[z][x] = object;
					}

					in.getline(line, 256);
					in.getline(line, 256);
					info = Trim(line);
				}
			}
		}
		in.close();
		return true;
	}

	EBool EGameManager::canGo(EFloat x, EFloat z)
	{
		if (x <= -mHXL || x >= mHXL || z <= -mHZL || z >= mHZL)
		{
			return false;
		}
		EInt xoff = (EInt)((x + mHXL) / mBlockSize);
		EInt zoff = (EInt)((z + mHZL) / mBlockSize);

		if (mCollisionValue[xoff][zoff] > 0)
			return false;

		return true;
	}

	void EGameManager::getLogicXZ(EFloat x, EFloat z, EInt &outX, EInt &outZ)
	{
		if (x <= -mHXL || x >= mHXL || z <= -mHZL || z >= mHZL)
		{
			outX = outZ = -1;
		}
		else
		{
			outX = (EInt)((x + mHXL) / mBlockSize);
			outZ = (EInt)((z + mHZL) / mBlockSize);
		}
	}

	EMesh* EGameManager::checkObject(EFloat x, EFloat z)
	{
		if (x <= -mHXL || x >= mHXL || z <= -mHZL || z >= mHZL)
		{
			return mTerrainMesh;
		}
		EInt xoff = (EInt)((x + mHXL) / mBlockSize);
		EInt zoff = (EInt)((z + mHZL) / mBlockSize);

		if (mCollisionValue[xoff][zoff] > 0)
			return mCollisionMeshs[xoff][zoff];
		else
		return NULL;
	}

	ETank* EGameManager::checkTank(EFloat x, EFloat y, EFloat z)
	{
		if (mMainPlayer->getTank()->intersect(EVector3D(x, y, z))){
			return mMainPlayer->getTank();
		}

		for (TankItr itr = mTanks.begin(); itr != mTanks.end(); ++itr)
		{
			if ((*itr)->intersect(EVector3D(x, y, z)))
				return *itr;
		}
		return NULL;
	}

	void EGameManager::playSound(SOUND_TYPE sound, EBool loop /* = false */)
	{
		const static EString Background = "Background.wav";
		const static EString Fire = "Fire.wav";
		const static EString Explode	= "Explosion.wav";

		EInt flag = SND_ASYNC;

		if (loop)
			flag |= SND_LOOP;
		EString soundName = Background;
		switch (sound)
		{
		case SOUND_BACKGROUND:
			soundName = Background;
			break;
		case SOUND_FIRE:
			soundName = Fire;
			break;
		case SOUND_EXPLODE:
			soundName = Explode;
			break;
		};
		::sndPlaySound(GetPath(soundName).c_str(),flag);
	}
}