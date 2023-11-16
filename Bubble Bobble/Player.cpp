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
void Player::setVelocity(const Vector3f& v) {
	velocity = v;
}
Vector3f Player::getVelocity() const {
	return velocity;
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
	bubblevelocity.setPos(7.0f, 0.0f, 0.0f);
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

	if (horizontalState == HORIZONTAL_STATE::MOVE) {
		velocity[0] = 1.5f;
		if (face == FACE::RIGHT) {
			center = center + velocity;
		}
		else if (face == FACE::LEFT) {
			center = center - velocity;
		}
	}
	else{
		velocity[0] = 0.0f;
	}
	
}
void Player::verticalmove() {
	if (verticalState == VERTICAL_STATE::JUMP) {
		if (firstvelocitycount == 0) {
			float firstvelocity = 30.0f;
			velocity[1] = firstvelocity;
			firstvelocitycount += 1;
		}
		acceleration[1] = -2.0f;
		velocity = velocity + acceleration;
		center = center + velocity;
	}
	else if (verticalState == VERTICAL_STATE::FALL) {
		velocity[1] = -0.8f;
		center = center + velocity;
	}
	else {
		firstvelocitycount = 0;
		velocity[1] = 0.0f;
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