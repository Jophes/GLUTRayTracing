#include "RayTraceData.h"

// Constructors
RayTraceData::RayTraceData() {
	colour = Colour();
	position = Vec3();
	intersectionExists = false;
}

RayTraceData::RayTraceData(Colour col, Vec3 pos, bool intersection) {
	colour = col;
	position = pos;
	intersectionExists = intersection;
}