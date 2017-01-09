#pragma once
#include "ECommon.h"
#include "EVector.h"
#include "EMatrix.h"
#include "ECore.h"

namespace E3D
{
	enum CAMERA_TYPE
	{
		CAMERA_MODEL_ELUA = 0x0001, //欧拉相机  三角欧拉算法
		CAMERA_MODEL_UVN  =0x0002   //UVN 相机   3D矩阵算法  分别代表3个向量
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


		EFloat		view_dist;//视角距离
		EFloat		fov;//视野
		EFloat		clip_z_near;//近裁剪
		EFloat		clip_z_far;//远裁剪

		EPlane3D	clip_plane_R;//right
		EPlane3D	clip_plane_L;//left
		EPlane3D	clip_plane_T;//top
		EPlane3D	clip_plane_B;//board

		EFloat		viewplane_width;//观察平面
		EFloat		viewplane_height;//观察平面
		EFloat		viewport_width; //观察孔宽
		EFloat		viewport_height;//观察孔高
		EFloat		viewport_center_X;//观察孔中心X位置
		EFloat		viewport_center_Y;//观察孔中心Y位置

		EFloat		aspect_ratio;//屏幕宽高比

		EMatrix44	mWorldToCamera;
		EMatrix44	mCameraToPerspective; //摄像机转到视角位置
		EMatrix44	mPerspectiveToScreen;


		EFrustum(CAMERA_TYPE mod, const EVector4D &pos, const EVector4D &dir,
			const EVector4D &target, EFloat nearZ, EFloat farZ, EFloat ffov,
			EFloat viewportWidth, EFloat viewportHeight);
	};
}