#include"Monster.h"
#include<iostream>
#include<GL/freeglut.h>

using namespace std;

Monster::Monster(float size) {
	this->size = size; velocity[0] = -5.0f; face = FACE::LEFT; status = STATUS::LIVE; onPlatform = true;
	velocity = { 0, 0, 0 };
	texture.initializeTexture("monster.png");
}

float Monster::getMonsterSize() {
	return size;
}
void Monster::setMonsterOnPlatform() {
	onPlatform = true;
}
void Monster::setMonsterNotOnPlatform() {
	onPlatform = false;
}
bool Monster::getMonsterOnPlatform() {
	return onPlatform;
}

void Monster::setMonsterId(int i) {
	monsterId = i;
}
int Monster::getMonsterId() {
	return monsterId;
}

void Monster::setMonsterFaceDown() {
	face = FACE::DOWN;
}
void Monster::setMonsterFaceLeft() {
	face = FACE::LEFT;
}
Monster::FACE Monster::getMonsterFace() {
	return face;
}

void Monster::setMonsterlifeTrapped(){
	status = STATUS::TRAP;
}
void Monster::setMonsterLifeDead() {
	status = STATUS::DEAD;
}
void Monster::setMonsterLifeLive() {
	status = STATUS::LIVE;
}
Monster::STATUS Monster::getMonsterStatus() {
	return status;
}

void Monster::setPlatform(const Platform& p) {
	platform = p;
	center[0] = (platform.getLeftEdge() + platform.getRightEdge()) / 2.0f;
	center[1] = platform.getTopEdge() + size / 2.0f;
	center[2] = 0;
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
	if (onPlatform) {
		if (face == FACE::LEFT) {
			velocity[0] = -5.0f;
			velocity[1] = 0.0f;
		}
		else if (face == FACE::RIGHT) {
			velocity[0] = 5.0f;
			velocity[1] = 0.0f;
		}
		if (face == FACE::LEFT && center[0] <= platform.getLeftEdge() + size / 2.0) {
			setFace(FACE::RIGHT);
		}
		else if (face == FACE::RIGHT && center[0] >= platform.getRightEdge() - size / 2.0) {
			setFace(FACE::LEFT);
		}
	}
	if (face == FACE::DOWN) {
		velocity[0] = 0.0f;
		velocity[1] = -1.0f;
	}
	center = center + velocity;

}

void Monster::draw(){
	if (status == STATUS::LIVE) {
		texture.setcenter(center);
		texture.setSize(size);
		texture.texturePlayer(face);
	}
}