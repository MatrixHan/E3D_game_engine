#pragma once

#include "ECommon.h"

namespace E3D
{

	template<class T>
	const T& Min(const T& a, const T& b)
	{
		return (a < b) ? a : b;
	}

	template<class T>
	const T& Max(const T& a, const T& b)
	{
		return (b < a) ? a : b;
	}

	template<typename T>
	const T& Clamp(const T& val,const T& minV,const T& maxV)
	{
		return Min(Max(val, maxV), minV);
	}

	void GetTranslateMatrix44(EMatrix44& mat, EFloat x, EFloat y, EFloat z);

	void GetScaleMatrix44(EMatrix44& mat,EFloat x, EFloat y, EFloat z);
	
	void GetRotateMatrix44X(EMatrix44& mat,EFloat degree);

	void GetRotateMatrix44Y(EMatrix44& mat, EFloat degree);

	void GetRotateMatrix44Z(EMatrix44& mat, EFloat degree);

	void GetRotateMatrix44(EMatrix44& mat,const EVector4D &n,EFloat degree);

	void GetVertex4DAddVector4D(const EVertex4D& v,const EVector4D& p,EVertex4D& result);

	//3d向量 与矩阵相乘
	void GetVector3DMulMatrix44(const EVector3D& vec,const EMatrix44& mat,EVector3D &result);
	//4d向量 与矩阵相乘
	void GetVector4DMulMatrix44(const EVector4D& vec, const EMatrix44& mat, EVector4D &result);
	//4d顶点 与矩阵相乘
	void GetVertex4DMulMatrix44(const EVertex4D& vec, const EMatrix44& mat, EVertex4D &result);
}