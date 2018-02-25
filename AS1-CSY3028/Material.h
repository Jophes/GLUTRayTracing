#pragma once

#include "Vec3.h"
#include "Colour.h"
#include "Texture.h"

class Material {
public:
	// Object Properties
	Colour ambient, specular, diffuse, reflects; // Co-efficients for different types of light
	Texture *texture;

	// Constructor
	Material(Vec3 amb = Vec3(0.3, 0.3, 0.3), Vec3 spec = Vec3(1, 1, 1), Vec3 diff = Vec3(1, 1, 1), Vec3 refl = Vec3());
	Material(Colour amb = Colour(0.3, 0.3, 0.3), Colour spec = Colour(1, 1, 1), Colour diff = Colour(1, 1, 1), Colour refl = Colour(0.5, 0.5, 0.5));
	Material(Colour refl, Texture *text, Colour diff = Colour(1, 1, 1), Colour amb = Colour(0.3, 0.3, 0.3), Colour spec = Colour(1, 1, 1));

	Colour GetDiffuseCol();
	Colour GetDiffuseCol(Vec3 *pos, Vec3 *cen);
};

