#define _USE_MATH_DEFINES
#include <cmath>
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "glut.h"
#include <iostream>

#include "GameObject.h"
#include "Sphere.h"

#include "Renderer.h"
#include "RayCastRenderer.h"
#include "RayTraceRenderer.h"

Vec2 windowSize = Vec2(640, 640);
Vec3 windowPos = Vec3(-1.5, 1.5, 1.5), cameraPos = Vec3(0, 0, 5);
Colour ambientLight = Colour(0.08, 0.08, 0.08);
LightSource light = LightSource(Vec3(0, 0, 1.0), Vec3(1, 1, 1), 1);

Texture brick = Texture("brick.bmp");
Texture sun = Texture("sun.bmp");

Material red = Material(Colour(0.4, 0.05, 0.05), &brick);
Material green = Material(Colour(0.9, 0.9, 0.9), Colour(0.9, 0.9, 0.9), Colour(0, 0.9, 0), Colour(0.5, 0.5, 0.5));
Material blue = Material(Colour(0.3, 0.3, 0.3), Colour(0.9, 0.9, 0.9), Colour(0, 0, 0.9), Colour(0.2, 0.4, 0.8));
Material orange = Material(Colour(0.1, 0.1, 0.1), &sun);

const unsigned int sphereCount = 7;
Sphere sphereSetA[sphereCount]{
	Sphere(Vec3(0, 1.3, 0), 0.5, &red),
	Sphere(Vec3(1, 0.6, 0), 0.5, &green),
	Sphere(Vec3(1, -0.6, 0), 0.5, &blue),
	Sphere(Vec3(0, -1.3, 0), 0.5, &red),
	Sphere(Vec3(-1, -0.6, 0), 0.5, &green),
	Sphere(Vec3(-1, 0.6, 0), 0.5, &blue),
	Sphere(Vec3(0, 0, -1.25), 1, &orange)
};
Sphere sphereSetB[sphereCount]{
	Sphere(Vec3(0, -1.3, 1.3), 0.5, &red),
	Sphere(Vec3(1, -0.4, 0.6), 0.5, &green),
	Sphere(Vec3(1, 0, -0.6), 0.5, &blue),
	Sphere(Vec3(0, 0, -1.3), 0.5, &red),
	Sphere(Vec3(-1, 0, -0.6), 0.5, &green),
	Sphere(Vec3(-1, -0.4, 0.6), 0.5, &blue),
	Sphere(Vec3(0, -1.25, 0), 1, &orange)
};
const unsigned int sphereSetCount = 2;
unsigned int selectedSet = sphereSetCount;
Sphere* sphereSets[sphereSetCount] = { sphereSetA, sphereSetB };

const unsigned int objectCount = sphereCount;
GameObject* objects[objectCount];
Renderer* renderer;
enum RenderType { RayTrace, RayCast, Basic, None };
RenderType currentRendererType = None;

void resize(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45, 1.0 * (w / (h <= 0 ? 1 : h)), 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
	windowSize.Set(w, h);
	renderer->Resize();
}

void draw() {
	glClearColor(0, 0, 0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	renderer->Draw();
	glutSwapBuffers();
}

void updateObjects(unsigned int newSelectedSet, bool attemptRedraw = true) {
	if (selectedSet != newSelectedSet) {
		selectedSet = newSelectedSet;
		for (unsigned int i = 0; i < sphereCount; i++) {
			objects[i] = (sphereSets[selectedSet] + i);
		}
		if (attemptRedraw) {
			glutPostRedisplay();
		}
	}
}

void updateRenderer(RenderType type, bool attemptRedraw = true) {
	if (type != currentRendererType) {
		currentRendererType = type;
		if (renderer != nullptr) {
			delete renderer;
		}
		switch (type) {
		case RayTrace:
			renderer = new RayTraceRenderer(&windowPos, &windowSize, &cameraPos, &light, &ambientLight, objects, &objectCount);
			break;
		case RayCast:
			renderer = new RayCastRenderer(&windowPos, &windowSize, &cameraPos, &light, &ambientLight, objects, &objectCount);
			break;
		case Basic:
		default:
			renderer = new Renderer(&windowPos, &windowSize, &cameraPos, objects, &objectCount);
			break;
		}
		if (attemptRedraw) {
			renderer->Resize();
			glutPostRedisplay();
		}
	}
}

void input(unsigned char key, int x, int y) {
	switch (key)
	{
	case '1':
		updateObjects(0);
		break;
	case '2':
		updateObjects(1);
		break;
	case 'q':
		updateRenderer(RayTrace);
		break;
	case 'w':
		updateRenderer(RayCast);
		break;
	default:
		break;
	}
}

int main(int argc, char **argv) {
	updateObjects(0, false);
	updateRenderer(RayTrace, false);

	// Init Glut
	glutInit(&argc, argv);

	glutInitWindowPosition((int)(glutGet(GLUT_SCREEN_WIDTH) * 0.5 - windowSize.x * 0.5), (int)(glutGet(GLUT_SCREEN_HEIGHT) * 0.5 - windowSize.y * 0.5));
	glutInitWindowSize(windowSize.x, windowSize.y);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("CSY3028 - Graphics 2 - Assignment 1");

	glutReshapeFunc(resize);
	glutDisplayFunc(draw);
	glutKeyboardFunc(input);

	glutMainLoop();

	return EXIT_SUCCESS;
} 