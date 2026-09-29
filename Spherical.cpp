#include "Spherical.h"

#include <cmath>

Vector3 ToCartesian(const Spherical& spherical) {

	Vector3 result{};

	const float cosTheta = std::cos(spherical.theta);

	result.x =
		spherical.radius *
		cosTheta *
		std::cos(spherical.phi);

	result.y =
		spherical.radius *
		std::sin(spherical.theta);

	result.z =
		spherical.radius *
		cosTheta *
		std::sin(spherical.phi);

	return result;
}

Spherical ToSpherical(const Vector3& cartesian) {

	Spherical result{};

	result.radius = std::sqrt(
		cartesian.x * cartesian.x +
		cartesian.y * cartesian.y +
		cartesian.z * cartesian.z
	);

	// 原点の場合は角度を求められないので0にする
	if (result.radius == 0.0f) {
		result.theta = 0.0f;
		result.phi = 0.0f;

		return result;
	}

	result.theta =
		std::asin(cartesian.y / result.radius);

	result.phi =
		std::atan2(cartesian.z, cartesian.x);

	return result;
}