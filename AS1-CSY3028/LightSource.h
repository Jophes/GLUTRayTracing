#pragma once

#include "Vec3.h"

class LightSource {
public:
	// Object Properties
	Vec3 pos, colour;
	double intensity;

	// Constructor
	LightSource(Vec3 position = Vec3(), Vec3 colour = Vec3(1, 1, 1), double _intensity = 1);

	// Object methods
	Vec3 GetLightCoeff();

protected:
	// Object Properties
	Vec3 lightCoeff;
};

