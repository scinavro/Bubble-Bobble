#pragma once
#include<vector>
#include "Material.h"
using namespace std;

class Bubble {
public:
	enum class STATUS{NORMAL, TRAPPING};

	Bubble();
	Bubble(float r, int sl, int st);

	void setRadius(float r);
	float getRadius() const;
	void setSlice(int sl);
	void setStack(int st);

	void setCenter(const Vector3f& c);
	Vector3f getCenter() const;
	void setVelocity(const Vector3f& v);
	Vector3f getVelocity() const;
	void setAcceleration(const Vector3f& a);
	Vector3f getAcceleration() const;

	STATUS getStatus();
	void setBubbleTrapping();
	
	void setMTL(const Material& m);

	void move();
	void draw() const;

	void setRandomMaterial();

	void setMonsterId(int);
	int getMonsterId();

	vector<Bubble> pop();

private:

	int trappingMonsterId;
	float radius;
	int slice;
	int stack;

	Vector3f center;
	Vector3f velocity;
	Vector3f acceleration;
	Material mtl;

	STATUS status;
};
