#pragma once

#include "RayTraceData.h"
#include "Renderer.h"
#include "LightSource.h"
#include <vector>

class RayTraceRenderer : public Renderer {
public:
	// Constructor
	RayTraceRenderer();
	RayTraceRenderer(Vec3 *position, Vec2 *size, Vec3 *cameraPos, LightSource *lightSource, Colour *ambient, GameObject **objects, const unsigned int *objCount);

	virtual void Draw();
protected:
	LightSource* light;
private:
	Colour backgroundColour = Colour();

	RayTraceData RayTracer(Ray r, int depth);
	Ray ReflectedRay(Vec3 p, GameObject* sphere);
	Colour Render(Vec3 p, GameObject* sphere);
};

