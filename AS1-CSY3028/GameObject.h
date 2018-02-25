#pragma once

#include "Vec3.h"
#include "Material.h"
#include "Ray.h"

struct RayData {
	// Struct properties
	bool hit;
	Vec3 hitPos;
	double distance;

	// Constructors
	RayData() {
		hit = false;
	};
	RayData(Vec3 pos, double dist) {
		hitPos = pos;
		distance = dist;
		hit = dist > 0.0;
	};
	RayData(Vec3 pos, double dist, bool _hit) {
		hitPos = pos;
		distance = dist;
		hit = _hit;
	};
};

class GameObject {
public:
	// Object properties
	Vec3 pos;
	Material *mat;

	// Constructors
	GameObject();
	GameObject(Vec3 position, Vec3 amb = Vec3(0.3, 0.3, 0.3), Vec3 spec = Vec3(1, 1, 1), Vec3 diff = Vec3(1, 1, 1));
	GameObject(Vec3 position, Material *material);

	// Object methods
	virtual RayData Intersect(Ray r);
	virtual void DrawBasic();

protected:
	// Object properties
	bool internalMaterial = true;
};
