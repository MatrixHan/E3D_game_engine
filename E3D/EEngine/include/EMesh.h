#pragma once

#include "ECommon.h"
#include "ECore.h"
#include "EMaterial.h"
#include "EObject.h"

namespace E3D
{
	enum COLLSION_TYPE
	{
		COLLSION_COLLSION,
		COLLSION_IGNORE,
	};

	class EMesh :public EObject
	{
	public:
		~EMesh();
		void setScale(const EVector3D &scale);
		void setPosition(const EVector3D &pos);
		EVector3D getPosition() const;
		void move(const EVector3D &mov);

		EBool intersect(const EVector3D &point);
		void setVisible(EBool visible) 
		{
			mIsVisible = visible;
		}
		EBool isVisible() const { return mIsVisible; }

		void setCullFlag(EBool needCull) { mObject->needCull = needCull; }

		void yaw(EFloat yDegree);
		void roll(EFloat rDegree);
		void pitch(EFloat pDegree);

		void setCollsionType(COLLSION_TYPE type) { mCollsionType = type; }
		COLLSION_TYPE getCollsionType() const { return mCollsionType; }

		EMaterial *getMaterial(EInt index = 0);
		void setMaterial(EInt index, EString matName);

		EObject4D* getObject() const { return mObject; }
		EInt getPolyonNumber() const { return mPolyonNumber; }
		EInt getVertexNumber() const { return mVertexNumber; }
		EInt getSubmeshNumber() const { return mSubmeshNumber; }

		EVector3D getRotateVec() const { return mRotate; }

		EMesh *clone();
	protected:
		friend class ESceneManager;
		EMesh();
		EMesh(const EString &name,const EString &meshName);
		EObject4D *mObject;

		EInt mPolyonNumber;
		EInt mVertexNumber;
		EInt mSubmeshNumber;
		EVector3D mRotate;
		EBool mIsVisible;
		COLLSION_TYPE mCollsionType;

	};
}
