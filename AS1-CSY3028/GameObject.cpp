#include "GameObject.h"

#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "glut.h"

// Constructors
GameObject::GameObject() {
	pos = Vec3();
}

GameObject::GameObject(Vec3 position, Vec3 amb, Vec3 spec, Vec3 diff) {
	pos = position;
}

GameObject::GameObject(Vec3 position, Material *material) {
	pos = position;
	internalMaterial = false;
	mat = material;
}

// Object methods
RayData GameObject::Intersect(Ray r) {
	return RayData();
}

void GameObject::DrawBasic() {
	return;
}