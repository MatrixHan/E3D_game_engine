#pragma once

#include "ECommon.h"
#include "EVector.h"
#include <list>

namespace E3D
{//EPOLY  矩阵多边形模型   shade 阴影
#define EPOLY_ATTR_2SIDE  0x0001
#define EPOLY_ATTR_TRNASPARENT 0x0002  //透明度
#define EPOLY_ATTR_SHADE_MODE_PURE 0x0004 //纯色
#define EPOLY_ATTR_SHADE_MODE_CONSTANT 0x0004//经常
#define EPOLY_ATTR_SHADE_MODE_FLAT		0x0008//平坦
#define EPOLY_ATTR_SHADE_MODE_GROUND	0x0010//地面
#define EPOLY_ATTR_SHADE_MODE_PHONG		0x0020//明暗算法一种
#define EPOLY_ATTR_SHADE_MODE_FASTPHONG 0x0020//快速明暗算法
#define EPOLY_ATTR_SHADE_MODE_TEXTURE	0x0040//纹理

#define EPOLY_ATTR_VERTEX_POSITION	0x1000 //顶点法线位置
#define EPOLY_ATTR_VERTEX_NORMAL	0x2000//顶点标量
#define EPOLY_ATTR_VERTEX_UV		0x4000//紫外

#define EPOLY_STATE_ACTIVE			0x0100//活着
#define EPOLY_STATE_CLIPPED			0x0200//剪除
#define EPOLY_STATE_BACKFACE		0x0400//后面 背面

#define EOBJECT_STATE_ACTIVE	0x0001
#define EOBJECT_STATE_VISIBLE	0x0002
#define EOBJECT_STATE_CULLED	0x0004

	enum CULL_TYPE
	{
		CULL_BOX = 0,	//筛选框
		CULL_SPHERE=1  //精选；采集（鲜花等）剔除 范围；球体
	};
	struct EVertex4D;
	typedef std::vector<EVertex4D> EVertex4DArray;
	typedef std::vector<EVector4D> EVector4DArray;
	typedef std::vector<EPolyon4D> EPolyon4DArray;

	struct EVertex4D
	{
		EFloat x, y, z, w;
		EFloat u, v;

		EVertex4D();
		EVertex4D(const EVector4D &v);
		EVertex4D(EFloat xf, EFloat yf, EFloat zf);
		EVertex4D operator *(const EVector4D &right);
		EVertex4D operator -(const EVertex4D &right);
		EVertex4D& operator =(const EVertex4D &right);
		EVertex4D operator +(const EVector4D &right);
		EVertex4D operator +(const EVertex4D &right);
		EVertex4D operator /(EFloat factor);

		EVector4D toVector4D()const;
	};

	struct EPlane3D
	{
		EVector4D point;
		EVector4D normal;
		EPlane3D() {}
		EPlane3D(const EVector4D &p,const EVector4D &nor);
		EPlane3D& operator=(const EPlane3D &right);
	};

	struct EPolyon4D
	{
		EInt state;
		EInt attribute;
		EInt color;

		EVertex4DArray *verlist;
		EInt verIndex[3];

		EPolyon4D();

	};

	struct EPolyonF4D
	{
		EInt state;
		EInt attribute;
		EInt color;

		EVertex4D localList[3]; //3个本地顶点组成
		EVertex4D  transformList[3];//3个世界顶点组成

		struct EMaterial *material;//素材
		EPolyonF4D();
	};
	struct CompEPolyonF4D
	{
		EBool operator()(const EPolyonF4D &polyA, const EPolyonF4D &polyB)//比大小前者大true
		{
			EFloat zA = Max(polyA.transformList[0].z,Max(polyA.transformList[1].z,polyA.transformList[2].z));
			EFloat zB = Max(polyB.transformList[0].z, Max(polyB.transformList[1].z, polyB.transformList[2].z));

			if (Abs(zA - zB) < 0.005f)
			{
				zA = (polyA.transformList[0].z + polyA.transformList[1].z + polyA.transformList[2].z) / 3.0f;
				zB = (polyB.transformList[0].z + polyB.transformList[1].z + polyB.transformList[2].z) / 3.0f;

				if (zA <= zB)
					return false;
				else
					return true;
			}
			else if (zA < zB)
				return false;
			else
				return true;
		}
	};

	struct EObject4D
	{
		EString name;		// 物体名称
		EInt	state;		// 物体状态
		EInt			attribute;		// 物体属性
		EFloat			avgRadius;		// 物体的平均半径, 用于碰撞检测
		EFloat			maxRadius;		// 物体的最大半径

		EBool	needCull;//1需要裁剪
		EString	materialName;//1素材名称
		EVector4D minBoundingBox;//1最小包围盒
		EVector4D maxBoundingBox;//1最大包围盒

		EVector4D worldPosition;//1世界坐标
		EVector4D scale;//1缩放

		EVector4D direction;// 物体的方向向量, 各分量记录延各轴的旋转角度

		EInt	vertexNumber;//顶点个数
		EVertex4DArray	localList;
		EVertex4DArray	transformList;

		EInt			polyonNumber;//1多边形个数
		EPolyon4DArray	polyonList;	//1多边形数组
		EObject4D*	    nextObject;

		EObject4D();

	};

	struct ERenderList4D
	{
		EInt state;
		EInt attribute;

		std::list<EPolyonF4D>  polyData;
		typedef std::list<EPolyonF4D>::iterator  Itr;
	};

	enum OBJ_TRANSFORM_TYPE
	{
		TRANSFORM_LOCAL=0,
		TRANSFORM_TRANS=1,
		TRANSFORM_LOCAL_TO_TRANS=2
	};

	void Transform_Object4D(EObject4D *object, const EMatrix44 &mat,
		OBJ_TRANSFORM_TYPE transformType);

	void Transform_RenderList4D(ERenderList4D *renderList, const EMatrix44 &mat,
		OBJ_TRANSFORM_TYPE transformType);

	void Insert_Object4D_To_RenderList4D(ERenderList4D *renderList, EObject4D* object,
		OBJ_TRANSFORM_TYPE transformType = TRANSFORM_LOCAL_TO_TRANS,
		bool transformScaleAndPosition=false);

	void Local_To_World_Object4D(EObject4D *object,OBJ_TRANSFORM_TYPE transformType = TRANSFORM_LOCAL_TO_TRANS);

	void Local_To_World_RenderList4D(ERenderList4D *renderList, const EVector4D &pos,
		OBJ_TRANSFORM_TYPE transformType = TRANSFORM_LOCAL_TO_TRANS);

	bool Cull_Object4D(EObject4D *object,EFrustum *camera,CULL_TYPE cullType=CULL_SPHERE);

	bool Remove_Backface(EPolyon4D *poly, EFrustum *camera);
	bool Remove_Backface(EPolyonF4D *poly, EFrustum *camera);

	void Remove_Backface_Object4D(EObject4D *object,EFrustum *camera);

	void Remove_Backface_RenderList4D(ERenderList4D *renderList,EFrustum *camera);

	void Light_PolyonF4D(EPolyonF4D *poly,EFrustum *camera);

	void Light_RenderList4D(ERenderList4D *renderList,EFrustum * camera);

	void World_To_Camera_Object4D(EObject4D *object,EFrustum *camera);
	void World_To_Camera_RenderList4D(ERenderList4D *renderList,EFrustum *camera);

	void Sort_RenderList4D(ERenderList4D *renderList);

	void Camera_To_Perspective_Object4D(EObject4D *object,EFrustum *camera);
	void Camera_To_Perspective_RenderList4D(ERenderList4D * renderList,EFrustum * camera);

	void Perspective_To_Screen_Object4D(EObject4D *object, EFrustum *camera);
	void Perspective_To_Screen_RenderList4D(ERenderList4D *renderList, EFrustum *camera);

	void Clip_RenderList4D(ERenderList4D *renderList,EFrustum *camera);

	void World_To_Screen_RenderList4D(ERenderList4D *renderList, EFrustum *camera);

	void Draw_Object4D_Wire(EObject4D *object);
	void Draw_RenderList4D_Wire(ERenderList4D *renderList);

	void Draw_Object4D_Solid(EObject4D *object);
	void Draw_RenderList4D_Solid(ERenderList4D *renderList);

	// 绘制带纹理的renderlist
	void Draw_RenderList4D_Teture_Solid(ERenderList4D * renderList);


}
