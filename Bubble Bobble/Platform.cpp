#include "Vector3f.h"
#include"Platform.h"
#include<GL/freeglut.h>

Platform::Platform(){}
Platform::Platform(float x, float y, float z, float w, float h) {
	center[0] = x; center[1] = y; center[2] = z; width = w; height = h;
	texture.initializeTexture("wall.png");
	texture.setcenter(center);
	texture.setWidthHeight(width, height);
}

float Platform::getTopEdge() const {
	return center[1] + height / 2.0f;
}

float Platform::getBottomEdge() const {
	return center[1] - height / 2.0f;
}

float Platform::getLeftEdge() const {
	return center[0] - width / 2.0f;
}

float Platform::getRightEdge() const {
	return center[0] + width / 2.0f;
}

void Platform::draw() {
	/*glColor3f(0.3f, 0.4f, 0.3f);
	glBegin(GL_QUADS);
	glVertex3f(center[0] - width / 2, center[1] - height / 2, center[2]);
	glVertex3f(center[0] + width / 2, center[1] - height / 2, center[2]);
	glVertex3f(center[0] + width / 2, center[1] + height / 2, center[2]);
	glVertex3f(center[0] - width / 2, center[1] + height / 2, center[2]);
	glEnd();*/

	texture.texture();
}
