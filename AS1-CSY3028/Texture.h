#pragma once
#include "Vec2.h"
#include "Colour.h"

class Texture
{
public:
	Texture();
	Texture(unsigned char* ps, int w, int h);
	Texture(const char* filename);
	~Texture();

	Colour GetColourAtPos(unsigned int x, unsigned int y);
	Colour GetColourAtPos(Vec2 pos);

	void SetGLColourAtPos(unsigned int x, unsigned int y);
	void SetGLColourAtPos(Vec2 pos);

	unsigned char* pixels;
	unsigned int width, height;
};

