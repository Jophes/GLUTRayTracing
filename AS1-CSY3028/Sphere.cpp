#include "Sphere.h"
#include <cmath>

#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "glut.h"

// Constructors
Sphere::Sphere() {
	pos = Vec3();
	rad = 1.0;
}

Sphere::Sphere(Vec3 position, double radius, Vec3 amb, Vec3 spec, Vec3 diff) {
	pos = position;
	rad = radius;
	mat = new Material(amb, spec, diff);
}

Sphere::Sphere(Vec3 position, double radius, Material *material) {
	pos = position;
	rad = radius;
	mat = material;
}

// Object methods
RayData Sphere::Intersect(Ray r) {
	Vec3 dir = r.end - r.start, dirCen = r.start - pos;
	double dpA = dir.DotProduct(dirCen), dpB = dir.DotProduct(dir), dpC = dirCen.DotProduct(dirCen) - pow(rad, 2);
	double discriminant = pow(dpA, 2) - dpB * dpC;
	if (discriminant < 0) {
		return RayData();
	}
	else {
		double dist;
		if (discriminant == 0) dist = -dpA / dpB;
		else {
			double d1 = (-dpA + sqrt(discriminant)) / dpB, d2 = (-dpA - sqrt(discriminant)) / dpB;
			dist = (d1 > d2 ? d2 : d1);
		}
		return RayData(r.start + dir * dist, dist);
	}
}

void Sphere::DrawBasic() {
	glTranslated(pos.x, pos.y, pos.z);
	glutSolidSphere(rad, 32, 32);
}