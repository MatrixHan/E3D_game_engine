#pragma once
#include "ECommon.h"
#include "EVector.h"
#include "EMatrix.h"
#include "ECore.h"

namespace E3D
{
	enum CAMERA_TYPE
	{
		CAMERA_MODEL_ELUA = 0x0001, //ŷ�����  ����ŷ���㷨
		CAMERA_MODEL_UVN  =0x0002   //UVN ���   3D�����㷨  �ֱ����3������
	};

	struct EFrustum
	{
		EInt state;
		EInt attribute;
		CAMERA_TYPE camMode;

		EVector4D	position;
		EVector4D   direction;

		EVector4D	camUp;
		EVector4D	camRight;
		EVector4D	camLook;
		EVector4D	camTarget;


		EFloat		view_dist;//�ӽǾ���
		EFloat		fov;//��Ұ
		EFloat		clip_z_near;//���ü�
		EFloat		clip_z_far;//Զ�ü�

		EPlane3D	clip_plane_R;//right
		EPlane3D	clip_plane_L;//left
		EPlane3D	clip_plane_T;//top
		EPlane3D	clip_plane_B;//board

		EFloat		viewplane_width;//�۲�ƽ��
		EFloat		viewplane_height;//�۲�ƽ��
		EFloat		viewport_width; //�۲�׿�
		EFloat		viewport_height;//�۲�׸�
		EFloat		viewport_center_X;//�۲������Xλ��
		EFloat		viewport_center_Y;//�۲������Yλ��

		EFloat		aspect_ratio;//��Ļ��߱�

		EMatrix44	mWorldToCamera;
		EMatrix44	mCameraToPerspective; //�����ת���ӽ�λ��
		EMatrix44	mPerspectiveToScreen;


		EFrustum(CAMERA_TYPE mod, const EVector4D &pos, const EVector4D &dir,
			const EVector4D &target, EFloat nearZ, EFloat farZ, EFloat ffov,
			EFloat viewportWidth, EFloat viewportHeight);
	};
}