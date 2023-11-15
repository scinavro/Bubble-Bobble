#pragma once

#include "Bubble.h"

class Player
{
public:
	enum FACE { LEFT, RIGHT };
	enum HORIZONTAL_STATE { STOP, MOVE };
	enum VERTICAL_STATE {STOP_2, JUMP, FALL};

	Player(float x, float y, float z, float size);

	void setCenter(const Vector3f& c);
	Vector3f getCenter() const;
	void setCurrentCenter(Vector3f& c);
	Vector3f getCurrentCenter();

	void setVelocity(const Vector3f& v);
	Vector3f getVelocity() const;

	void setAcceleration(const Vector3f& a);
	Vector3f getAcceleration()const;

	void setFace(FACE f);
	void setHorizontalState(HORIZONTAL_STATE hState);
	void setVerticalState(VERTICAL_STATE vState);
	Bubble shootBubble();

	void jump();

	bool isMoving() const;

	bool isDragonInAir() const;

	void move();
	void draw() const;

private:
	bool isdragoninair;
	Vector3f center;
	Vector3f velocity;
	Vector3f acceleration;
	Vector3f current_center;
	float size;
	FACE face;
	HORIZONTAL_STATE horizontalState;
	VERTICAL_STATE verticalState;
};

