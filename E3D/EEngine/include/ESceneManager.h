#pragma once

#include "ECommon.h"
#include "EMesh.h"
#include "ELight.h"
#include "ECore.h"
#include "ECamera.h"
#include <map>

namespace E3D
{
	class ESceneManager
	{
		typedef std::map<EString, EMesh *>::iterator MeshItr;
	public:
		ESceneManager();
		~ESceneManager();
		void drawString(const EString &str, EInt x, EInt y, const EColor &c = EColor(255, 255, 255));

		EMesh * createMesh(const EString &name, const EString &meshName);
		EMesh*  getMesh(const EString &name);
		void destroyMesh(const EString &name);
		void clearMesh();

		void enableLights(EBool enable);
		EBool isLightsEnable() const { return mLightEnable; }

		ELight* createLight(LIGHT_TYPE lightType);
		ELight* getLight(EInt id);


		ECamera* getCamera() { return mCamera; }
		EInt    getTotalObjectNumber()const { return mMeshes.size(); }
		EInt getVisibleObjectNumber() const { return mVisibleObjectNumber; }
		EInt getVisiblePolyonNumber() const { return mVisiblePolyonNumber; }
		EInt getTotalPolyonNumber() const { return mTotalPolyonNumber; }

		EMesh* createTerrain(const EString& rawFileName, const EString &heightMapFileName, 
			EFloat uTitle = 1, EFloat vTitle = 1, EFloat blockSize = 5.0f);
		EMesh* getTerrain() { return mTerrainMesh; }

		void update();
	protected:
		std::map<EString, EMesh*> mMeshes;
		std::map<EString, EMesh*> mUsedMesh;
		ERenderList4D			*mRenderList;
		EMesh					*mTerrainMesh;
		ECamera					*mCamera;
		EBool					mLightEnable;
		EInt					mVisibleObjectNumber;
		EInt					mVisiblePolyonNumber;
		EInt					mTotalPolyonNumber;
	private:
	};
}