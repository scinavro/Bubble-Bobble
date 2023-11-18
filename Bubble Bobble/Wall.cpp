#include<GL/freeglut.h>
#include"Wall.h"

Wall::Wall(float x, float y, float z, float w, float h) {
	center[0] = x; center[1] = y; center[2] = z; width = w; height = h;
}

float Wall::getTopEdge() const {
	return center[1] + height / 2.0f;
}

float Wall::getBottomEdge() const {
	return center[1] - height / 2.0f;
}

float Wall::getLeftEdge() const{
	return center[0] - width / 2.0f;
}

float Wall::getRightEdge() const {
	return center[0] + width / 2.0f;
}

void Wall::draw() const {
	glColor3f(0.3f, 0.4f, 0.3f);
	glBegin(GL_QUADS);
	glVertex3f(center[0] - width / 2, center[1] - height / 2, center[2]);
	glVertex3f(center[0] + width / 2, center[1] - height / 2, center[2]);
	glVertex3f(center[0] + width / 2, center[1] + height / 2, center[2]);
	glVertex3f(center[0] - width / 2, center[1] + height / 2, center[2]);
	glEnd();
}
