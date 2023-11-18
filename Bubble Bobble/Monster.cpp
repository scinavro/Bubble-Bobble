#include"Monster.h"
#include<GL/freeglut.h>

Monster::Monster(float x, float y, float z, float size) {
	center[0] = x; center[1] = y; center[2] = z; this->size = size; velocity[0] = 2.5f;
}
void Monster::setCenter(const Vector3f & c) {
	center = c;
}
Vector3f Monster::getCenter() const {
	return center;
}
void Monster::setVelocity(const Vector3f & v) {
	velocity = v;
}
Vector3f Monster::getVelocity() const {
	return velocity;
}

void Monster::setFace(FACE f) {
	if (f == FACE::LEFT) {
		face = FACE::LEFT;
	}
	else if (f == FACE::RIGHT) {
		face = FACE::RIGHT;
	}
}

void Monster::move() {
	if (face == FACE::LEFT) {
		center = center - velocity;
	}
	else if (face == FACE::RIGHT) {
		center = center + velocity;
	}
}

void Monster::draw() const {
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex3f(center[0] + size / 2, center[1] + size / 2, center[2]);
	glVertex3f(center[0] - size / 2, center[1] + size / 2, center[2]);
	glVertex3f(center[0] - size / 2, center[1] - size / 2, center[2]);
	glVertex3f(center[0] + size / 2, center[1] - size / 2, center[2]);
	glEnd();
}