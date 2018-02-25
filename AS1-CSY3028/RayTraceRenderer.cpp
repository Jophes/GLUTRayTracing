#include "RayTraceRenderer.h"

#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "glut.h"

#include <iostream>


// Constructor
RayTraceRenderer::RayTraceRenderer() {
}

RayTraceRenderer::RayTraceRenderer(Vec3 *position, Vec2 *size, Vec3 *cameraPos, LightSource *lightSource, Colour *ambient, GameObject **objects, const unsigned int *objCount) {
	winPos = position;
	winSize = size;
	eyePos = cameraPos;
	light = lightSource;
	ambientLight = ambient;
	gameObjects = objects;
	objectCount = objCount;
}

// Object methods
// Private
Colour RayTraceRenderer::Render(Vec3 p, GameObject* sphere) {
	Vec3 normal = (p - sphere->pos).Normalise(), L = (light->pos - p).Normalise();
	double LdotN = L.DotProduct(normal);
	Colour colour = (sphere->mat->ambient * (*ambientLight));
	if (LdotN >= 0) {
		colour.Set(colour + sphere->mat->GetDiffuseCol(&p, &sphere->pos) * light->GetLightCoeff() * LdotN + sphere->mat->specular * pow(((L + ((*eyePos - p).Normalise())) * 0.5).DotProduct(normal), 250));
	}
	colour.Recheck();
	return colour;
}

Ray RayTraceRenderer::ReflectedRay(Vec3 p, GameObject* sphere) {
	Vec3 normal = (p - sphere->pos).Normalise(), r = (*eyePos - p).Normalise();
	return Ray(p, normal * 2.0 * r.DotProduct(normal) - r + p);
}

RayTraceData RayTraceRenderer::RayTracer(Ray r, int depth) {
	RayTraceData returnTraceData = RayTraceData();
	unsigned int closestObject;
	bool intersectionExists = false;
	double shortestDistance = INFINITY;

	if (depth <= 5) {
		RayData hitData;
		for (unsigned int k = 0; k < *objectCount; k++) {
			hitData = (*(gameObjects+k))->Intersect(r); 
			if (hitData.hit) {
				intersectionExists = true;
				if (hitData.distance < shortestDistance) {
					shortestDistance = hitData.distance;
					returnTraceData.position.Set(hitData.hitPos);
					closestObject = k;
				}
			}
		}
		if (intersectionExists) {
			GameObject *obj = *(gameObjects + closestObject);
			returnTraceData.colour.Set(Render(returnTraceData.position, obj) + RayTracer(ReflectedRay(returnTraceData.position, obj), depth + 1).colour * obj->mat->reflects);
			returnTraceData.intersectionExists = true;
		}
	}
	return returnTraceData;
}

// Overrideable
void RayTraceRenderer::Draw() {
	Vec3 pixel = Vec3(winPos->x, winPos->y, winPos->z);
	Ray ray = Ray(*eyePos, pixel);
	RayTraceData tracedData;

	glBegin(GL_POINTS);
	for (unsigned int i = 0; i < vertCount; i++) {
		for (unsigned int j = 0; j < horiCount; j++) {
			ray.end = pixel;
			tracedData = RayTracer(ray, 0);
			if (tracedData.intersectionExists) {
				DrawPoint(&tracedData.position, &tracedData.colour);
			}
			pixel.x += dx;
		}
		pixel.x = winPos->x;
		pixel.y -= dy;
	}
	glEnd();
}