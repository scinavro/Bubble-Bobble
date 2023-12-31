#pragma once

#include "Bubble.h"
#include "Texture.h"
#include<vector>
using namespace std;

class Player
{
public:
	enum FACE { LEFT, RIGHT };
	enum class HORIZONTAL_STATE { STOP, MOVE };
	enum class VERTICAL_STATE { STOP, JUMP, FALL };

	Player(float x, float y, float z, float size, const char* name);

	int getPlayerLife();

	void PlayerLifeDeduced();

	Texture getTexture();

	void setCenter(const Vector3f& c);
	Vector3f getCenter() const;

	void setHorizontalVelocity(const Vector3f& v);
	Vector3f getHorizontalVelocity() const;

	void setVerticalVelocity(const Vector3f& v);
	Vector3f getVerticalVelocity() const;

	void setAcceleration(const Vector3f& a);
	Vector3f getAcceleration()const;

	void setFace(FACE f);
	void setHorizontalState(HORIZONTAL_STATE hState);
	void setVerticalState(VERTICAL_STATE vState);
	Bubble shootBubble(int version);

	void horizontalmove();
	void verticalmove();

	HORIZONTAL_STATE getHorizontalState();
	VERTICAL_STATE getVerticalState();

	void draw();

	float getSize();

	vector<Vector3f> getvertex();

private:
	int playerLife;
	Vector3f center;
	Vector3f HorizontalVelocity;
	Vector3f VerticalVelocity;
	Vector3f acceleration;
	Vector3f current_center;
	float size;
	FACE face;
	HORIZONTAL_STATE horizontalState;
	VERTICAL_STATE verticalState;
	Texture texture;
};

