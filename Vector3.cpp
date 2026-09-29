#include "Vector3.h"

#include <cmath>

// ========================================
// ベクトルの減算
// ========================================
Vector3 Subtract(const Vector3& v1, const Vector3& v2) {

	return {
		v1.x - v2.x,
		v1.y - v2.y,
		v1.z - v2.z
	};
}

// ========================================
// ベクトルの正規化
// ========================================
Vector3 Normalize(const Vector3& v) {

	// ベクトルの長さを求める
	float length = std::sqrt(
		v.x * v.x +
		v.y * v.y +
		v.z * v.z
	);

	// 長さが0の場合
	if (length == 0.0f) {
		return { 0.0f, 0.0f, 0.0f };
	}

	// 長さで割って単位ベクトルにする
	return {
		v.x / length,
		v.y / length,
		v.z / length
	};
}

// ========================================
// 外積
// ========================================
Vector3 Cross(const Vector3& v1, const Vector3& v2) {

	return {
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
	};
}