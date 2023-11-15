#include "Dragon.h"
#include<GL/freeglut.h>

Player::Player(float x, float y, float z, float size){
	center[0] = x; center[1] = y; center[2] = z; this->size = size; face = LEFT; velocity[0] = 1.5f; acceleration[1] = -0.5f;
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
void Player::setCurrentCenter( Vector3f& c) {
	current_center = c;
}
Vector3f Player::getCurrentCenter()  {
	return current_center;
}

void Player::setFace(FACE f) {
	if (f == LEFT) {
		face = LEFT;
	}
	else if (f == RIGHT) {
		face = RIGHT;
	}
}
void Player::setHorizontalState(HORIZONTAL_STATE hState) {
	if (hState == STOP) {
		horizontalState = STOP;
	}
	else {
		horizontalState = MOVE;
	}
}
void Player::setVerticalState(VERTICAL_STATE vState) {
	if (vState == JUMP) {
		verticalState = JUMP;
	}
	else if (vState == FALL) {
		verticalState = FALL;
	}
	else {
		verticalState = STOP_2;
	}
}
Bubble Player::shootBubble() {
	Bubble bub(20, 20, 20);
	bub.setCenter(center);
	if (face == LEFT) {
		bub.setVelocity(-2 * velocity);
	}
	else if (face == RIGHT) {
		bub.setVelocity(2 * velocity);
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

void Player::jump() {
	setCurrentCenter(center);

}

bool Player::isMoving() const {
	if (horizontalState) {
		return true;
	}
	else {
		return false;
	}
}

bool Player::isDragonInAir() const {
	if (isdragoninair) {
		return true;
	}
	else {
		return false;
	}
}

void Player::move() {

	if (horizontalState == MOVE) {
		if (face == RIGHT) {
			center = center + velocity;
		}
		else if (face == LEFT) {
			center = center - velocity;
		}
	}
	else{
	}

	if (verticalState == JUMP) {
		if (current_center[1] + 70 <= center[1]) {
			center[2] = current_center + 
		}
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

	if (face == RIGHT) {
		glColor3f(0.0f, 0.0f, 1.0f);
		glPointSize(10.0f);
		glBegin(GL_POINTS);
		glVertex2f(center[0] + size / 2, center[1]);
		glEnd();

	}
	else if (face == LEFT) {
		glColor3f(0.0f, 0.0f, 1.0f);
		glPointSize(10.0f);
		glBegin(GL_POINTS);
		glVertex2f(center[0] - size / 2, center[1]);
		glEnd();
	}
}