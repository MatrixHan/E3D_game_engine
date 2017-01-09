#pragma once
#include "ECommon.h"
#include "EVector.h"

namespace E3D
{

	enum LIGHT_TYPE
	{
		LIGHT_AMBIENT=0,//������
		LIGHT_DIRECTION = 1,//�����
		LIGHT_POINT=2       //���
	};

	struct ELight
	{
		EInt id;
		EBool lighton;//�Ƿ�򿪵ƹ�
		LIGHT_TYPE lightType;
		EFloat   power;//��ǿ��
		EFloat	 shadowFactor;//������

		EColor	 ambient;//����color
		EColor	 diffuse;//
		EColor	 specular;//

		EVector4D position;//����
		EVector4D direction;//����

		EVector4D transPosition;//�ƹ� �����λ��
		EVector4D transDirection;//�ƹ� ��������� 

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