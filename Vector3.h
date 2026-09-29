#pragma once

struct Vector3 {
	float x;
	float y;
	float z;
};

// ベクトルの減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2);

// ベクトルの正規化
Vector3 Normalize(const Vector3& v);

// 外積
Vector3 Cross(const Vector3& v1, const Vector3& v2);