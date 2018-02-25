#pragma once

#include "Renderer.h"
#include "LightSource.h"

class RayCastRenderer : public Renderer {
public:
	// Constructor
	RayCastRenderer(); 
	RayCastRenderer(Vec3 *position, Vec2 *size, Vec3 *cameraPos, LightSource *lightSource, Colour *ambient, GameObject **objects, const unsigned int *objCount);
	virtual void Draw();
protected:
	LightSource* light;
private:
	void RenderPoint(RayData rayData, GameObject *gameObject);
};

