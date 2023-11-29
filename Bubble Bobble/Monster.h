#pragma once
#include"Vector3f.h"
#include "Platform.h"
#include "Texture.h"
#include <vector>
using namespace std;

class Monster {
	
public:
	enum FACE { LEFT, RIGHT, DOWN };
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
	void draw();

	void setMonsterFaceDown();
	void setMonsterFaceLeft();

	FACE getMonsterFace();

	void setMonsterlifeTrapped();
	STATUS getMonsterStatus();

	void setMonsterLifeDead();
	void setMonsterLifeLive();

	void setMonsterOnPlatform();
	void setMonsterNotOnPlatform();
	bool getMonsterOnPlatform();

	vector<Vector3f> getvertex();

	void setMonsterId(int);
	int getMonsterId();
	float getMonsterSize();

private:
	bool onPlatform;
	int monsterId;
	Platform platform;
	Vector3f center;
	Vector3f velocity;
	Texture texture;
	float size;
	FACE face;
	STATUS status;
};