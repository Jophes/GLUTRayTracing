#pragma once

#include "Colour.h"
#include "Vec3.h"

class RayTraceData {
public:
	// Properties
	Colour colour;
	Vec3 position;
	bool intersectionExists;

	// Constructors
	RayTraceData();
	RayTraceData(Colour col, Vec3 pos, bool intersection = true);
};

