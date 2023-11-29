#pragma once

#include "Vector3f.h"
#include "Texture.h"

class Platform
{
public:
	Platform();
	Platform(float x, float y, float z, float w, float h);

	float getTopEdge() const;
	float getBottomEdge() const;
	float getLeftEdge() const;
	float getRightEdge() const;

	void draw();

private:
	Vector3f center;
	Texture texture;
	float width, height;
};

