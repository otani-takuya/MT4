#include "SphericalCamera.h"

#include <imgui.h>
#include <numbers>

// ========================================
// 初期化
// ========================================
void SphericalCamera::Initialize() {

	// 注視点
	target_ = {
		0.0f,
		0.0f,
		0.0f
	};

	// 球面座標
	spherical_ = {
		6.0f,
		0.0f,
		-std::numbers::pi_v<float> / 2.0f
	};

	// 球面座標 → 直交座標
	position_ = ToCartesian(spherical_);

	// カメラ行列を作成
	UpdateCameraMatrix();
}

// ========================================
// 更新
// ========================================
void SphericalCamera::Update() {

	// 球面座標 → 直交座標
	position_ = ToCartesian(spherical_);

	// カメラ行列を更新
	UpdateCameraMatrix();
}

// ========================================
// カメラ行列を作成
// ========================================
void SphericalCamera::UpdateCameraMatrix() {

	// カメラから注視点への前方向
	Vector3 forward =
		Normalize(Subtract(target_, position_));

	// ワールド空間の上方向
	const Vector3 worldUp = {
		0.0f,
		1.0f,
		0.0f
	};

	// カメラの右方向
	Vector3 right =
		Normalize(Cross(worldUp, forward));

	// カメラの上方向
	Vector3 up =
		Normalize(Cross(forward, right));

	// カメラ行列
	cameraMatrix_ = {
		right.x,     right.y,     right.z,     0.0f,
		up.x,        up.y,        up.z,        0.0f,
		forward.x,   forward.y,   forward.z,   0.0f,
		position_.x, position_.y, position_.z, 1.0f
	};
}

// ========================================
// ImGui
// ========================================
void SphericalCamera::DrawImGui() {

	ImGui::Begin("Spherical Coordinates");

	// 注視点
	ImGui::Text(
		"Target: (%.3f, %.3f, %.3f)",
		target_.x,
		target_.y,
		target_.z
	);

	ImGui::Separator();

	// 球面座標を操作
	ImGui::DragFloat(
		"Radius",
		&spherical_.radius,
		0.01f,
		0.1f,
		100.0f
	);

	ImGui::DragFloat(
		"Theta",
		&spherical_.theta,
		0.01f,
		-std::numbers::pi_v<float> / 2.0f + 0.01f,
		std::numbers::pi_v<float> / 2.0f - 0.01f
	);

	ImGui::DragFloat(
		"Phi",
		&spherical_.phi,
		0.01f,
		-std::numbers::pi_v<float>,
		std::numbers::pi_v<float>
	);

	ImGui::Separator();

	// 球面座標
	ImGui::Text(
		"Spherical: r = %.3f, theta = %.3f rad, phi = %.3f rad",
		spherical_.radius,
		spherical_.theta,
		spherical_.phi
	);

	// 直交座標
	ImGui::Text(
		"Cartesian: x = %.3f, y = %.3f, z = %.3f",
		position_.x,
		position_.y,
		position_.z
	);

	ImGui::Separator();

	// カメラ行列
	ImGui::Text("Camera matrix:");

	for (int row = 0; row < 4; ++row) {

		ImGui::Text(
			"%8.3f  %8.3f  %8.3f  %8.3f",
			cameraMatrix_.m[row][0],
			cameraMatrix_.m[row][1],
			cameraMatrix_.m[row][2],
			cameraMatrix_.m[row][3]
		);
	}

	ImGui::End();
}