#pragma once
#include"Vector3f.h"

class Monster {
	enum class FACE { LEFT, RIGHT };
public:
	Monster(float x, float y, float z, float size);
	void setCenter(const Vector3f& c);
	Vector3f getCenter() const;

	void setVelocity(const Vector3f& v);
	Vector3f getVelocity() const;

	void move();
	void setFace(FACE f);
	void draw();
private:
	Vector3f center;
	Vector3f velocity;
	float size;
	FACE face;
};