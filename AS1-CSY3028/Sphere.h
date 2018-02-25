#pragma once

#include "GameObject.h"

class Sphere : public GameObject {
public:
	// Object properties
	double rad;// Object properties
	//Vec3 pos;
	//Material *mat;

	// Constructors
	Sphere();
	Sphere(Vec3 position, double radius, Vec3 amb = Vec3(0.3, 0.3, 0.3), Vec3 spec = Vec3(1, 1, 1), Vec3 diff = Vec3(1, 1, 1));
	Sphere(Vec3 position, double radius, Material *material);

	// Object methods
	virtual RayData Intersect(Ray r);
	virtual void DrawBasic();
};
