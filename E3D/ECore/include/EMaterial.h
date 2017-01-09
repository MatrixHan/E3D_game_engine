#pragma once

#include "ECommon.h"
#include <map>
#include "EGraphics.h"

namespace E3D
{
	//素材渲染
	struct EMaterial
	{
		EString name;
		EColor  ambient; //阴影色
		EColor  diffuse;//扩散色
		EColor  specular;//反射光

		EBitmap *bitmap;

		EMaterial();
		~EMaterial();
		
		inline bool useTexture() { return bitmap && bitmap->isValid(); }
		EColor getPixel(EFloat u, EFloat v);
	};

	typedef std::map<EString, EMaterial*>::iterator MaterialIter;
	extern  std::map<EString, EMaterial*> *GMaterials;
		
	extern  EMaterial *GetMaterial(const EString& name);//获取材质
	extern  bool SetMaterial(const EString& name, EMaterial *material);//保存材质
	extern  bool DestoryMaterial(const EString& name);//销毁材质
	extern  void DestoryAllMaterials();//销毁所有材质

	extern  void ParseMaterialScript(const EString &stringname);//解析脚本
}