#include"Bubble.h"
#include<GL/freeglut.h>
#include<ctime>


Bubble::Bubble(){}
Bubble::Bubble(float r, int sl, int st) {
	radius = r; slice = sl; stack = st;
}

void Bubble::setRadius(float r) {
	radius = r;
}
float Bubble::getRadius() const {
	return radius;
}
void Bubble::setSlice(int sl) {
	slice = sl;
}
void Bubble::setStack(int st) {
	stack = st;
}

void Bubble::setCenter(const Vector3f& c) {
	center = c;
}
Vector3f Bubble::getCenter() const {
	return center;
}
void Bubble::setVelocity(const Vector3f& v) {
	velocity = v;
}
Vector3f Bubble::getVelocity() const {
	return velocity;
}
void Bubble::setAcceleration(const Vector3f& a) {
	acceleration = a;
}
Vector3f Bubble::getAcceleration() const {
	return acceleration;
}

void Bubble::setMTL(const Material& m) {
	mtl = m;
}

void Bubble::move() {
	velocity = velocity + acceleration;
	center = center + velocity;
}
void Bubble::draw() const {

	float getambient[4] = { mtl.getAmbient()[0], mtl.getAmbient()[1], mtl.getAmbient()[2], mtl.getAmbient()[3] };
	float getdiffuse[4] = { mtl.getDiffuse()[0],mtl.getDiffuse()[1],mtl.getDiffuse()[2],mtl.getDiffuse()[3] };
	float getspecular[4] = { mtl.getSpecular()[0],mtl.getSpecular()[1],mtl.getSpecular()[2],mtl.getSpecular()[3] };
	float getemission[4] = { mtl.getEmission()[0] ,mtl.getEmission()[1] ,mtl.getEmission()[2] ,mtl.getEmission()[3] };
	float shininess[1] = { mtl.getShininess() };

	glPushMatrix();
	glTranslatef(center[0], center[1],center[2]);	

	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_EMISSION, getemission);
	glMaterialfv(GL_FRONT, GL_AMBIENT,getambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, getdiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, getspecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	glutSolidSphere(radius, slice, stack);

	glPopMatrix();
}


void setRandomMaterial(Bubble& bubble) {

	srand((unsigned int)time(0));
	double emission[4]; emission[3] = 1.0f;
	double ambient[4]; ambient[3] = 1.0f;
	double diffuse[4]; diffuse[3] = 1.0f;
	double specular[4]; specular[3] = 1.0f;
	float shininess[1];

	for (int i = 0; i < 4; i++) {
		emission[i] = (double)rand() / RAND_MAX;
	}
	for (int i = 0; i < 4; i++) {
		diffuse[i] = (double)rand() / RAND_MAX;
	}
	for (int i = 0; i < 4; i++) {
		ambient[i] = (double)rand() / RAND_MAX;
	}
	for (int i = 0; i < 4; i++) {
		specular[i] = (double)rand() / RAND_MAX;
	}
	shininess[0] = rand() % 30 + 1;

	Material mtl;

	mtl.setEmission(emission[0], emission[1], emission[2], emission[3]);
	mtl.setSpecular(specular[0], specular[1], specular[2], specular[3]);
	mtl.setDiffuse(diffuse[0], diffuse[1], diffuse[2], diffuse[3]);
	mtl.setAmbient(ambient[0], ambient[1], ambient[2], ambient[3]);
	mtl.setShininess(shininess[0]);
	bubble.setMTL(mtl);
}

void setRandomVelocity(Bubble& bubble) {

	srand((unsigned int)time(0));
	Vector3f RandomVelocity;
	float randomx = rand() % 20 - 10; float randomy = rand() % 10 + 1; float randomz = 0;
	RandomVelocity.setPos(randomx, randomy, randomz);
	bubble.setVelocity(RandomVelocity);

}

vector<Bubble> Bubble::pop() {
	vector<Bubble>bubs;
	for (int i = 0; i < 10; i++) {
		Bubble bub;
		Vector3f a(0, -5, -3);
		bub.setAcceleration(a);
		setRandomMaterial(bub);
		setRandomVelocity(bub);
		bub.setRadius(4);
		bub.setCenter(center);
		bubs.push_back(bub);
	}
	return bubs;
}
