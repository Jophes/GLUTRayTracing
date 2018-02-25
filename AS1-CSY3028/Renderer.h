#pragma once

#include "Vec2.h"
#include "Vec3.h"
#include "Colour.h"
#include "GameObject.h"
#include "Sphere.h"

class Renderer {
public:
	// Object properties

	// Constructor
	Renderer();
	Renderer(Vec3 *position, Vec2 *size, Vec3 *cameraPos, GameObject **objects, const unsigned int *objCount);

	// Object methods
	virtual void Draw();
	virtual void Resize();
protected:
	// Properties
	Vec2 *winSize;
	Vec3 *winPos, *eyePos;
	Colour *ambientLight;
	GameObject **gameObjects;
	const unsigned int *objectCount;
	unsigned int vertCount, horiCount;
	double dx, dy;

	// Object methods
	void DrawPoint(Vec3* position, Colour* col);
};

