#include "Renderer.h"

#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "glut.h"

#include "GameObject.h"
#include "Sphere.h"

// Constructor
Renderer::Renderer() {
}

Renderer::Renderer(Vec3 *position, Vec2 *size, Vec3 *cameraPos, GameObject **objects, const unsigned int *objCount) {
	winPos = position;
	winSize = size;
	eyePos = cameraPos;
	gameObjects = objects;
	objectCount = objCount;
	Resize();
}

// Object methods

// Overrideable
void Renderer::Resize() {
	dx = 2 / winSize->x;
	dy = 2 / (winSize->y);
	horiCount = (unsigned int)(winSize->x * 1.5);
	vertCount = (unsigned int)(winSize->y * 1.5);
}

void Renderer::Draw() {
	for (unsigned int i = 0; i < *objectCount; i++) {
		(*(gameObjects + i))->DrawBasic();
	}
}

void Renderer::DrawPoint(Vec3* position, Colour* col) {
	glColor3d(col->r, col->g, col->b);
	glVertex3d(position->x, position->y, position->z);
}