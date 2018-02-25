#include "RayCastRenderer.h"

#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "glut.h"

#include <iostream>

// Constructor
RayCastRenderer::RayCastRenderer() {
}

RayCastRenderer::RayCastRenderer(Vec3 *position, Vec2 *size, Vec3 *cameraPos, LightSource *lightSource, Colour *ambient, GameObject **objects, const unsigned int *objCount) {
	winPos = position;
	winSize = size;
	eyePos = cameraPos;
	light = lightSource;
	ambientLight = ambient;
	gameObjects = objects;
	objectCount = objCount;
}

// Object methods
// Overrideable
void RayCastRenderer::Draw() {
	Vec3 pixel = Vec3(winPos->x, winPos->y, winPos->z);
	unsigned int closestId = 0;
	RayData data, rayData; 
	Ray ray = Ray(*eyePos, pixel);
	bool assigned = false;

	glBegin(GL_POINTS);
	for (unsigned int y = 0; y < vertCount; y++) {
		for (unsigned int x = 0; x < horiCount; x++) {
			assigned = false;
			ray.end = pixel;
			for (unsigned int i = 0; i < *objectCount; i++) {
				rayData = (*(gameObjects+i))->Intersect(ray);
				if (rayData.hit && (!assigned || data.distance > rayData.distance)) {
					assigned = true;
					data = rayData;
					closestId = i;
				}
			}
			if (assigned && data.hit) {
				RenderPoint(data, *(gameObjects+closestId));
			}
			pixel.x += dx;
		}
		pixel.x = winPos->x;
		pixel.y -= dy;
	}
	glEnd();
}

// Private
void RayCastRenderer::RenderPoint(RayData rayData, GameObject *gameObject) {
	Vec3 intersectNorm = (rayData.hitPos - gameObject->pos).Normalise(), toLight = (light->pos - rayData.hitPos).Normalise();
	double intersectDot = toLight.DotProduct(intersectNorm), hDotN_n = pow(((toLight + (*eyePos - rayData.hitPos).Normalise()) * 0.5).DotProduct(intersectNorm), 250); 
	Colour col = gameObject->mat->ambient * (*ambientLight);
	if (intersectDot >= 0) {
		col = col + gameObject->mat->GetDiffuseCol(&rayData.hitPos, &gameObject->pos) * light->GetLightCoeff() * intersectDot + gameObject->mat->specular * hDotN_n;
	}
	DrawPoint(&rayData.hitPos, &col);
}