#pragma once
#include "ECommon.h"
#include "EVector.h"

namespace E3D
{

	enum LIGHT_TYPE
	{
		LIGHT_AMBIENT=0,//环境光
		LIGHT_DIRECTION = 1,//方向光
		LIGHT_POINT=2       //点光
	};

	struct ELight
	{
		EInt id;
		EBool lighton;//是否打开灯光
		LIGHT_TYPE lightType;
		EFloat   power;//加强度
		EFloat	 shadowFactor;//减弱度

		EColor	 ambient;//环境color
		EColor	 diffuse;//
		EColor	 specular;//

		EVector4D position;//坐标
		EVector4D direction;//方向

		EVector4D transPosition;//灯光 摄像机位置
		EVector4D transDirection;//灯光 摄像机坐标 

		EFloat	kc, kl, kq;

		EFloat  spot_inner;
		EFloat	spot_outer;

		EFloat	pf;

		ELight(EInt lightId, LIGHT_TYPE type);


	};
#define MAX_LIGHT 8

	extern std::vector<ELight*> *GLight;

	typedef std::vector<ELight*>::iterator LightItr;

	extern EInt CreateLight(LIGHT_TYPE light_type);
	extern ELight* GetLight(EInt id);
	extern EInt		GetLightSize();

	extern void DestroyAllLights();
}