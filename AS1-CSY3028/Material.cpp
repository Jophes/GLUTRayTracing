#include "Material.h"
#define _USE_MATH_DEFINES
#include <cmath>

static double pi2deg = (180.0 / M_PI);

// Constructor
Material::Material(Vec3 amb, Vec3 spec, Vec3 diff, Vec3 refl) {
	ambient = Colour(amb);
	specular = Colour(spec);
	diffuse = Colour(diff);
	reflects = Colour(refl);
}

Material::Material(Colour amb, Colour spec, Colour diff, Colour refl) {
	ambient = amb;
	specular = spec;
	diffuse = diff;
	reflects = refl;
}

Material::Material(Colour refl, Texture *text, Colour diff, Colour amb, Colour spec) {
	reflects = refl;
	texture = text;
	diffuse = diff;
	ambient = amb;
	specular = spec;
}

Colour Material::GetDiffuseCol() {
	return diffuse;
}
Colour Material::GetDiffuseCol(Vec3 *pos, Vec3 *cen) {
	if (texture != nullptr) {
		Vec3 dir = Vec3(pos->x - cen->x, pos->z - cen->z, 0);
		double bearing = atan2(dir.y, dir.x), heading = atan2(dir.Magnitude(), pos->y - cen->y);
		if (bearing < 0) bearing += M_PI;

		unsigned int x = (unsigned int)(bearing * pi2deg), y = (unsigned int)(heading * pi2deg);
		if (x < texture->width && y < texture->height) {
			return texture->GetColourAtPos(x, y) * diffuse;
		}
	}
	return diffuse;
}