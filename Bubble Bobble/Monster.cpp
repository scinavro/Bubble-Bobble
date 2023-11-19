#include"Monster.h"
#include<GL/freeglut.h>

Monster::Monster(float x, float y, float z, float size) {
	center[0] = x; center[1] = y; center[2] = z; this->size = size; velocity[0] = 5.0f; face = FACE::LEFT; monsterlife = true;
}

void Monster::setMonsterlifedead(){
	monsterlife = false;
}

void Monster::setPlatform(const Platform& p) {
	platform = p;
}
Platform Monster::getPlatform() const {
	return platform;
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

vector<Vector3f> Monster::getvertex() {
	vector<Vector3f> vertex;
	Vector3f v1(center[0] + size / 2, center[1] + size / 2, center[2]); vertex.push_back(v1);
	Vector3f v2(center[0] - size / 2, center[1] + size / 2, center[2]); vertex.push_back(v2);
	Vector3f v3(center[0] - size / 2, center[1] - size / 2, center[2]); vertex.push_back(v3);
	Vector3f v4(center[0] + size / 2, center[1] - size / 2, center[2]); vertex.push_back(v4);

	return vertex;
}

void Monster::move() {
	if (face == FACE::LEFT) {
		center = center - velocity;
	}
	else if (face == FACE::RIGHT) {
		center = center + velocity;
	}
	if (face == FACE::LEFT && center[0] <= platform.getLeftEdge() + size / 2.0) {
		setFace(FACE::RIGHT);
	}
	else if (face == FACE::RIGHT && center[0] >= platform.getRightEdge() - size / 2.0) {
		setFace(FACE::LEFT);
	}

}

void Monster::draw() const {
	if (monsterlife == true) {
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_POLYGON);
		glVertex3f(center[0] + size / 2, center[1] + size / 2, center[2]);
		glVertex3f(center[0] - size / 2, center[1] + size / 2, center[2]);
		glVertex3f(center[0] - size / 2, center[1] - size / 2, center[2]);
		glVertex3f(center[0] + size / 2, center[1] - size / 2, center[2]);
		glEnd();
	}
}