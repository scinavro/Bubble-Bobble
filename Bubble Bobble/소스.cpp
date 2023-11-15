#include <iostream>
#include <vector>

#include "Constants.h"
#include "Light.h"

#include "Dragon.h"
#include "Platform.h"

#include <GL/freeglut.h>

using namespace std;

Light light(boundaryX, boundaryY, boundaryX / 2, GL_LIGHT0);

clock_t start_t = clock();
clock_t end_t;

Player player(0.0f, -boundaryY + PLAYER_SIZE * 1.5f, 0.0f, PLAYER_SIZE);
Platform ground(0.0f, -boundaryY + PLAYER_SIZE * 0.5f, 0.0f, boundaryX * 2, PLAYER_SIZE);
vector<Bubble> bubbles;

void idle() {
	/* Implement */
	end_t = clock();

	if ((float)(end_t - start_t) > 1000 / 30.0f) {

		start_t = end_t;
		if (player.isMoving()) {
			player.move();
		}
		for (auto &bub : bubbles) {
			bub.move();
		}

	}

	glutPostRedisplay();
	
}

void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-boundaryX, boundaryX, -boundaryY, boundaryY, -100.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Draw 2D
	ground.draw();
	player.draw();

	// Draw 3D
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(light.getID());

	light.setAmbient(0.5f, 0.5f, 0.5f, 1.0f);
	light.setDiffuse(0.7f, 0.7f, 0.7f, 1.0f);
	light.setSpecular(1.0f, 1.0f, 1.0f, 1.0f);

	light.draw();

	/* Implement: Draw bubbles */

	for (auto& bub : bubbles) {
		bub.draw();
	}

	glDisable(light.getID());
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glutSwapBuffers();
}

void keyboardDown(unsigned char key, int x, int y) {
	/* Implement */
	if (key == ' ') {
		bubbles.push_back(player.shootBubble());
	}
	else if (key == GLUT_KEY_UP) {
		player.setVerticalState(Player::VERTICAL_STATE::JUMP);
		player.jump();
	}
}

void specialKeyDown(int key, int x, int y) {
	/* Implement */
	switch (key) {
		case GLUT_KEY_LEFT:
			player.setFace(Player::FACE::LEFT);
			player.setHorizontalState(Player::HORIZONTAL_STATE::MOVE);
			break;

		case GLUT_KEY_RIGHT:
			player.setFace(Player::FACE::RIGHT);
			player.setHorizontalState(Player::HORIZONTAL_STATE::MOVE);
			break;

		default:
			break;
	}
}
`
void specialKeyUp(int key, int x, int y) {
	/* Implement */

	switch (key) {
	case GLUT_KEY_LEFT:
		player.setHorizontalState(Player::HORIZONTAL_STATE::STOP);
		break;

	case GLUT_KEY_RIGHT:
		player.setHorizontalState(Player::HORIZONTAL_STATE::STOP);
		break;

	default:
		break;
	}
}

int main(int argc, char** argv) {
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(WINDOW_X, WINDOW_Y);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("(1) Move the player horizontally and (2) shoot bubble");

	// register callbacks
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboardDown);
	glutSpecialFunc(specialKeyDown);
	glutSpecialUpFunc(specialKeyUp);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}
