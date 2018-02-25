#pragma once

#include "Vec3.h"

class Ray {
public:
	// Struct Properties
	Vec3 start;
	Vec3 end;

	// Struct constructor
	Ray(Vec3 _start = Vec3(), Vec3 _end = Vec3()) {
		start = _start;
		end = _end;
	}
};