#pragma once
#include<GL/freeglut.h>
#include <FreeImage.h>
#include "Vector3f.h"
class Texture {
public:
	Texture(){}
	void texture();

	void setcenter(Vector3f & c);
	Vector3f getcenter();
	void setSize(float s);

	FIBITMAP* createBitMap(char const* filename);
	void generateTexture();
	void initializeTexture(char const* filename);

	GLuint getTextureID()const;

	GLuint textureID;
	GLubyte* textureData;


	int imagewidth, imageheight;
	float size;
private:
	Vector3f center;

};