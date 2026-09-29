#pragma once

#include "Vector3.h"

struct Spherical {
	float radius;
	float theta;
	float phi;
};

// 球面座標 → 直交座標
Vector3 ToCartesian(const Spherical& spherical);

// 直交座標 → 球面座標
Spherical ToSpherical(const Vector3& cartesian);