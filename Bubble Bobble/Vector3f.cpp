#include "Vector3f.h"

Vector3f::Vector3f(){}
Vector3f::Vector3f(float x, float y, float z){
	pos[0] = x; pos[1] = y; pos[2] = z;
}
void Vector3f::setPos(float x, float y, float z) {
	pos[0] = x; pos[1] = y; pos[2] = z;
}

float& Vector3f::operator[](const int i) {
	return pos[i];
}
float Vector3f::operator[](const int i) const {
	return pos[i];
}

Vector3f operator+(const Vector3f& v1, const Vector3f& v2) {
	float x = v1[0] + v2[0];
	float y = v1[1] + v2[1];
	float z = v1[2] + v2[2];
	return Vector3f(x, y, z);
}
Vector3f operator-(const Vector3f& v1, const Vector3f& v2) {
	float x = v1[0] - v2[0];
	float y = v1[1] - v2[1];
	float z = v1[2] - v2[2];
	return Vector3f(x, y, z);
}
Vector3f operator*(const float s, const Vector3f& vec3) {
	float x = s * vec3[0];
	float y = s * vec3[1];
	float z = s * vec3[2];
	return Vector3f(x, y, z);
}
Vector3f operator/(const Vector3f& vec3, const float s) {
	float x = vec3[0] / s;
	float y = vec3[1] / s;
	float z = vec3[2] / s;
	return Vector3f(x, y, z);
}
float dotProduct(const Vector3f& v1, const Vector3f& v2) {
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}