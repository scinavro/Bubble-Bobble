#pragma once

#include "Vector3f.h"

class Platform
{
public:
	Platform(float x, float y, float z, float w, float h);

	float getTopEdge() const;
	float getBottomEdge() const;
	float getLeftEdge() const;
	float getRightEdge() const;

	void draw() const;

private:
	Vector3f center;

	float width, height;
};

