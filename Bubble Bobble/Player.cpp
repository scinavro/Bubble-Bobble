#include "Player.h"
#include<GL/freeglut.h>

Player::Player(float x, float y, float z, float size){
	center[0] = x; center[1] = y; center[2] = z; this->size = size; face = FACE::LEFT; 
}

void Player::setCenter(const Vector3f& c) {
	center = c;
}
Vector3f Player::getCenter() const {
	return center;
}
void Player::setHorizontalVelocity(const Vector3f& v) {
	horizontalvelocity = v;
}
Vector3f Player::getHorizontalVelocity() const {
	return horizontalvelocity;
}
void Player::setVerticalVelocity(const Vector3f& v) {
	verticalvelocity = v;
}
Vector3f Player::getVerticalVelocity() const {
	return verticalvelocity;
}
void Player::setAcceleration(const Vector3f& a) {
	acceleration = a;
}
Vector3f Player::getAcceleration() const {
	return acceleration;
}

void Player::setFace(FACE f) {
	if (f == FACE::LEFT) {
		face = FACE::LEFT;
	}
	else if (f == FACE::RIGHT) {
		face = FACE::RIGHT;
	}
}
void Player::setHorizontalState(HORIZONTAL_STATE hState) {
	if (hState == HORIZONTAL_STATE::STOP) {
		horizontalState = HORIZONTAL_STATE::STOP;
	}
	else {
		horizontalState = HORIZONTAL_STATE::MOVE;
	}
}
void Player::setVerticalState(VERTICAL_STATE vState) {
	if (vState == VERTICAL_STATE::JUMP) {
		verticalState = VERTICAL_STATE::JUMP;
	}
	else if (vState == VERTICAL_STATE::FALL) {
		verticalState = VERTICAL_STATE::FALL;
	}
	else {
		verticalState = VERTICAL_STATE::STOP;
	}
}
Bubble Player::shootBubble() {
	Bubble bub(2, 20, 20);
	Vector3f bubblevelocity;
	bubblevelocity.setPos(15.0f, 0.0f, 0.0f);
	bub.setCenter(center);
	if (face == FACE::LEFT) {
		bub.setVelocity(-1 * bubblevelocity);
	}
	else if (face == FACE::RIGHT) {
		bub.setVelocity(bubblevelocity);
	}


	Material mtl1;
	mtl1.setEmission(0.1f, 0.1f, 0.1f, 1.0f);
	mtl1.setAmbient(0.4f, 0.4f, 0.1f, 1.0f);
	mtl1.setDiffuse(0.7f, 0.7f, 0.7f, 1.0f);
	mtl1.setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
	mtl1.setShininess(10.0f);

	bub.setMTL(mtl1);

	return bub;
}


Player::HORIZONTAL_STATE Player::getHorizontalState(){
	if (horizontalState == HORIZONTAL_STATE::MOVE) {
		return HORIZONTAL_STATE::MOVE;
	}
	else {
		return HORIZONTAL_STATE::STOP;
	}
}
Player::VERTICAL_STATE Player::getVerticalState() {
	if (verticalState == VERTICAL_STATE::JUMP) {
		return VERTICAL_STATE::JUMP;
	}
	else if (verticalState == VERTICAL_STATE::FALL) {
		return VERTICAL_STATE::FALL;
	}
	else {
		return VERTICAL_STATE::STOP;
	}
}


void Player::horizontalmove() {

	Vector3f horizontalvelocity;

	if (horizontalState == HORIZONTAL_STATE::MOVE) {
		if (face == FACE::RIGHT) {
			//velocity[0] = 5.0f;
			horizontalvelocity.setPos(5.0f, 0.0f, 0.0f);
		}
		else if (face == FACE::LEFT) {
			//velocity[0] = -5.0f;
			horizontalvelocity.setPos(-5.0f, 0.0f, 0.0f);
		}
		center = center + horizontalvelocity;
	}
	else{
		horizontalvelocity[0] = 0.0f;
	}
	
}
void Player::verticalmove() {
	if (verticalState == VERTICAL_STATE::JUMP) {
		acceleration[1] = -2.0f;
		verticalvelocity = verticalvelocity + acceleration;
		center = center + verticalvelocity;
	}
	else if (verticalState == VERTICAL_STATE::FALL) {
		verticalvelocity[1] = -20.0f;
		center = center + verticalvelocity;
	}
	else {
		verticalvelocity[1] = 0.0f;
		acceleration[1] = 0.0f;
	}
}
void Player::draw() const {
	

	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex3f(center[0] + size / 2, center[1] + size / 2, center[2]);
	glVertex3f(center[0] - size / 2, center[1] + size / 2, center[2]);
	glVertex3f(center[0] - size / 2, center[1] - size / 2, center[2]);
	glVertex3f(center[0] + size / 2, center[1] - size / 2, center[2]);
	glEnd();

	if (face ==FACE:: RIGHT) {
		glColor3f(0.0f, 0.0f, 1.0f);
		glPointSize(10.0f);
		glBegin(GL_POINTS);
		glVertex2f(center[0] + size / 2, center[1]);
		glEnd();

	}
	else if (face == FACE::LEFT) {
		glColor3f(0.0f, 0.0f, 1.0f);
		glPointSize(10.0f);
		glBegin(GL_POINTS);
		glVertex2f(center[0] - size / 2, center[1]);
		glEnd();
	}
}