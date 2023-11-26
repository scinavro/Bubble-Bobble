#pragma once
#include"Vector3f.h"
#include "Platform.h"
#include<vector>
using namespace std;

class Monster {
	
public:
	enum class FACE { LEFT, RIGHT };
	enum class STATUS { LIVE, TRAP, DEAD };
	Monster(float size);
	void setCenter(const Vector3f& c);
	Vector3f getCenter() const;

	void setVelocity(const Vector3f& v);
	Vector3f getVelocity() const;

	void setPlatform(const Platform& p);
	Platform getPlatform()const;

	void move();
	void setFace(FACE f);
	void draw() const;

	void setMonsterlifeTrapped();
	STATUS getMonsterStatus();

	void setMonsterLifeDead();

	vector<Vector3f> getvertex();

	void setMonsterId(int);
	int getMonsterId();

private:
	int monsterId;
	Platform platform;
	Vector3f center;
	Vector3f velocity;
	float size;
	FACE face;
	STATUS status;
};