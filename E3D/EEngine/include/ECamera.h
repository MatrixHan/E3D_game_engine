#pragma once

#include "EFrustum.h"
#include "EMath.h"

namespace E3D
{
	enum RenderMode
	{
		RENDER_WIRE,
		RENDER_SOLID,
	};

	class ECamera
	{
	public:
		
		~ECamera();

		void update();

		void setZNear(EFloat znear);

		void setZFar(EFloat zfar);

		void setPosition(const EVector3D &pos);

		void setTarget(const EVector3D &target,EBool lookTarget = false);

		void releaseTarget() { mLookTarget = false; }

		void move(const EVector3D &mov);

		void moveRelative(const EVector3D &mov);

		void yaw(EFloat yDegree);
		void pitch(EFloat pDegree);

		void setRenderMode(RenderMode mode) { mRenderMode = mode; }
		RenderMode getRenderMode() const { return mRenderMode; }

		EFrustum *getFrustum() const {
			return mFrustum;
		}

	protected:
		friend class ESceneManager;
		ECamera();
		EFrustum *mFrustum;
		EBool mLookTarget;
		EBool mNeedUpdate;
		RenderMode mRenderMode;
	private:


	};

}
