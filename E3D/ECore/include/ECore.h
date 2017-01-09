#pragma once

#include "ECommon.h"
#include "EVector.h"
#include <list>

namespace E3D
{//EPOLY  ��������ģ��   shade ��Ӱ
#define EPOLY_ATTR_2SIDE  0x0001
#define EPOLY_ATTR_TRNASPARENT 0x0002  //͸����
#define EPOLY_ATTR_SHADE_MODE_PURE 0x0004 //��ɫ
#define EPOLY_ATTR_SHADE_MODE_CONSTANT 0x0004//����
#define EPOLY_ATTR_SHADE_MODE_FLAT		0x0008//ƽ̹
#define EPOLY_ATTR_SHADE_MODE_GROUND	0x0010//����
#define EPOLY_ATTR_SHADE_MODE_PHONG		0x0020//�����㷨һ��
#define EPOLY_ATTR_SHADE_MODE_FASTPHONG 0x0020//���������㷨
#define EPOLY_ATTR_SHADE_MODE_TEXTURE	0x0040//����

#define EPOLY_ATTR_VERTEX_POSITION	0x1000 //���㷨��λ��
#define EPOLY_ATTR_VERTEX_NORMAL	0x2000//�������
#define EPOLY_ATTR_VERTEX_UV		0x4000//����

#define EPOLY_STATE_ACTIVE			0x0100//����
#define EPOLY_STATE_CLIPPED			0x0200//����
#define EPOLY_STATE_BACKFACE		0x0400//���� ����

#define EOBJECT_STATE_ACTIVE	0x0001
#define EOBJECT_STATE_VISIBLE	0x0002
#define EOBJECT_STATE_CULLED	0x0004

	enum CULL_TYPE
	{
		CULL_BOX = 0,	//ɸѡ��
		CULL_SPHERE=1  //��ѡ���ɼ����ʻ��ȣ��޳� ��Χ������
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

		EVertex4D localList[3]; //3�����ض������
		EVertex4D  transformList[3];//3�����綥�����

		struct EMaterial *material;//�ز�
		EPolyonF4D();
	};
	struct CompEPolyonF4D
	{
		EBool operator()(const EPolyonF4D &polyA, const EPolyonF4D &polyB)//�ȴ�Сǰ�ߴ�true
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
		EString name;		// ��������
		EInt	state;		// ����״̬
		EInt			attribute;		// ��������
		EFloat			avgRadius;		// �����ƽ���뾶, ������ײ���
		EFloat			maxRadius;		// ��������뾶

		EBool	needCull;//1��Ҫ�ü�
		EString	materialName;//1�ز�����
		EVector4D minBoundingBox;//1��С��Χ��
		EVector4D maxBoundingBox;//1����Χ��

		EVector4D worldPosition;//1��������
		EVector4D scale;//1����

		EVector4D direction;// ����ķ�������, ��������¼�Ӹ������ת�Ƕ�

		EInt	vertexNumber;//�������
		EVertex4DArray	localList;
		EVertex4DArray	transformList;

		EInt			polyonNumber;//1����θ���
		EPolyon4DArray	polyonList;	//1���������
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

	// ���ƴ������renderlist
	void Draw_RenderList4D_Teture_Solid(ERenderList4D * renderList);


}
