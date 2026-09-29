#pragma once

#include "Matrix4x4.h"
#include "Spherical.h"
#include "Vector3.h"

class SphericalCamera {
public:

	void Initialize();

	void Update();

	void DrawImGui();

private:

	void UpdateCameraMatrix();

private:

	// 注視点
	Vector3 target_ = {};

	// 球面座標
	Spherical spherical_ = {};

	// カメラ位置
	Vector3 position_ = {};

	// カメラ行列
	Matrix4x4 cameraMatrix_ = {};
};