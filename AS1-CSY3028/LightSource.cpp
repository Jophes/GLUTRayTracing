#include "LightSource.h"

// Constructor
LightSource::LightSource(Vec3 position, Vec3 _colour, double _intensity) {
	pos = position;
	colour = _colour;
	intensity = _intensity;

	lightCoeff = colour * intensity;
}

// Object methods
Vec3 LightSource::GetLightCoeff() {
	return lightCoeff;
}
