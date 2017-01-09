#pragma once

#include "ECommon.h"

namespace E3D
{
	class EObject
	{
	public:
		virtual ~EObject() {};
		virtual EString getName() const { return mName; }

		virtual void update() {}

		virtual EBool isAlive() const { return mCurrentLive < mMaxLive; }
	protected:
		EObject():mMaxLive(1),mCurrentLive(0) {}
		EString mName;
		EInt mMaxLive;
		EInt mCurrentLive;
	private:

	};
}