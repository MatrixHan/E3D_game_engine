#pragma once

#include "ECommon.h"
#include <map>
#include "EGraphics.h"

namespace E3D
{
	//�ز���Ⱦ
	struct EMaterial
	{
		EString name;
		EColor  ambient; //��Ӱɫ
		EColor  diffuse;//��ɢɫ
		EColor  specular;//�����

		EBitmap *bitmap;

		EMaterial();
		~EMaterial();
		
		inline bool useTexture() { return bitmap && bitmap->isValid(); }
		EColor getPixel(EFloat u, EFloat v);
	};

	typedef std::map<EString, EMaterial*>::iterator MaterialIter;
	extern  std::map<EString, EMaterial*> *GMaterials;
		
	extern  EMaterial *GetMaterial(const EString& name);//��ȡ����
	extern  bool SetMaterial(const EString& name, EMaterial *material);//�������
	extern  bool DestoryMaterial(const EString& name);//���ٲ���
	extern  void DestoryAllMaterials();//�������в���

	extern  void ParseMaterialScript(const EString &stringname);//�����ű�
}