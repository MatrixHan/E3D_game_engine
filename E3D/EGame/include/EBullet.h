#pragma once

#include "EObject.h"
#include "EGameManager.h"
#include "ESceneManager.h"

namespace E3D
{
	class ETank;
	class EBullet :public EObject
	{
	public:
		virtual ~EBullet();

		void setScale(const EVector3D &scale) { mMesh->setScale(scale); }
		void setPosition(const EVector3D &pos);
		EVector3D getPosition()const { return mMesh->getPosition(); }

		void setDirection(const EVector3D& dir);
		void yaw(EFloat degree);
		void update();
		EBool	isVisible() const { return mMesh->isVisible(); }
		void setVisible(EBool visible) { mMesh->setVisible(visible); }
	protected:
		friend class EGameManager;
		EBullet(ETank *owner, const EString &meshName, EGameManager *scene);
	protected:
		EGameManager  *mGameMgr;
		EMesh			*mMesh;
		EVector3D		mDirection;
		EFloat			mSpeed;
		ETank			*mOwner;
		static EInt		mID;

	};


}