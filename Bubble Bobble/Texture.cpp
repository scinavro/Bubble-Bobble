#include"Texture.h"
#include <FreeImage.h>
#include<iostream>

using namespace std;

void Texture::setcenter(Vector3f& c) {
	center = c;
}

void Texture::setWidthHeight(float w, float h) {
	width = w;
	height = h;
}

Vector3f Texture::getcenter(){
	return center;
}
void Texture::setSize(float s) {
	size = s;
}

FIBITMAP* Texture::createBitMap(char const* filename){
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename, 0);
	if (format == -1) {
		exit(-1);
	}
	else if (format == FIF_UNKNOWN) {
		format = FreeImage_GetFIFFromFilename(filename);
		if (!FreeImage_FIFSupportsReading(format)) {
			cout << "Detected image format cannot be read!" << endl;
			exit(-1);
		}
	}
	FIBITMAP* bitmap = FreeImage_Load(format, filename);
	int bitsPerPixel = FreeImage_GetBPP(bitmap);
	cout << "Source image has" << bitsPerPixel << " bits per pixel." << endl;

	FIBITMAP* bitmap32;
	if (bitsPerPixel == 32) {
		cout << "Skipping conversion" << endl;
		bitmap32 = bitmap;
	}
	else {
		cout << "Converting to 32-bits." << endl;
		bitmap32 = FreeImage_ConvertTo32Bits(bitmap);
	}

	return bitmap32;
}

void Texture::texture() {
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glColor4f(1.0, 1.0, 1.0, 1.0); // reset gl color

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBegin(GL_QUADS);
	if (size > 0.1) { // 정사각형
		glTexCoord2f(0.0f, 0.0f); glVertex2f(center[0] - size / 2, center[1] - size / 2);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(center[0] - size / 2, center[1] + size / 2);
		glTexCoord2f(1.0f, 1.0f); glVertex2f(center[0] + size / 2, center[1] + size / 2);
		glTexCoord2f(1.0f, 0.0f); glVertex2f(center[0] + size / 2, center[1] - size / 2);
	}
	else { // 직사각형
		glTexCoord2f(0.0f, 0.0f); glVertex2f(center[0] - width / 2, center[1] - height / 2);
		glTexCoord2f(0.0f, height / imageheight); glVertex2f(center[0] - width / 2, center[1] + height / 2);
		glTexCoord2f(width / imagewidth, height / imageheight); glVertex2f(center[0] + width / 2, center[1] + height / 2);
		glTexCoord2f(width / imagewidth, 0.0f); glVertex2f(center[0] + width / 2, center[1] - height / 2);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void Texture::texturePlayer(int face) {
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glColor4f(1.0, 1.0, 1.0, 1.0); // reset gl color
	glBegin(GL_QUADS);
	if (face == 1) {
		glTexCoord2f(0.0f, 0.0f); glVertex2f(center[0] - size / 2, center[1] - size / 2);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(center[0] - size / 2, center[1] + size / 2);
		glTexCoord2f(1.0f, 1.0f); glVertex2f(center[0] + size / 2, center[1] + size / 2);
		glTexCoord2f(1.0f, 0.0f); glVertex2f(center[0] + size / 2, center[1] - size / 2);
	}
	else {
		glTexCoord2f(0.0f, 0.0f); glVertex2f(center[0] + size / 2, center[1] - size / 2);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(center[0] + size / 2, center[1] + size / 2);
		glTexCoord2f(1.0f, 1.0f); glVertex2f(center[0] - size / 2, center[1] + size / 2);
		glTexCoord2f(1.0f, 0.0f); glVertex2f(center[0] - size / 2, center[1] - size / 2);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void Texture::generateTexture(){
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imagewidth, imageheight, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, textureData);
}

void Texture::initializeTexture(char const* filename){
	FIBITMAP* bitmap32 = createBitMap(filename);
	imagewidth = FreeImage_GetWidth(bitmap32);
	imageheight = FreeImage_GetHeight(bitmap32);
	textureData = FreeImage_GetBits(bitmap32);

	generateTexture();
}

GLuint Texture::getTextureID()const{
	return textureID;
}