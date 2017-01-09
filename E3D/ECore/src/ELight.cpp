#include "ELight.h"


namespace E3D
{
	ELight::ELight(EInt lightId, LIGHT_TYPE type):id(lightId),lightType(type),lighton(true),
		ambient(255,255,255),diffuse(255,255,255),specular(255,255,255),position(0,0,0)
		,direction(0,0,1),kc(1.0f),kl(1.0f),kq(0.0f),spot_inner(45.0f),spot_outer(60.0f),
		power(1.0f),shadowFactor(0.05f)
	{
	
	}

	std::vector<ELight*> *GLight = NULL;

	EInt CreateLight(LIGHT_TYPE light_type)
	{
		if (GLight == NULL)
			GLight = new std::vector<ELight*>();
		if ((EInt)GLight->size() > MAX_LIGHT)
			return -1;
		EInt id = (EInt)GLight->size();
		GLight->push_back(new ELight(id,light_type));

		return id;
	}

	ELight* GetLight(EInt id)
	{
		if (GLight == NULL || (EInt)GLight->size() > MAX_LIGHT 
			|| id <0 || id>(EInt)GLight->size() - 1)
		{
			return NULL;
		}
		else {
			return GLight->at(id);
		}
	}

	EInt  GetLightSize()
	{
		return GLight->size();
	}

	void DestroyAllLights()
	{
		for (LightItr itr = GLight->begin(); itr != GLight->end(); ++itr)
		{
			SafeDelete((*itr));
		}
		GLight->clear();
		SafeDelete(GLight);
	}



}