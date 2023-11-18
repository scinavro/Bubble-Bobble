#include <iostream>
#include <vector>

#include "Constants.h"
#include "Light.h"

#include "Player.h"
#include "Platform.h"

#include "Stage.h"
#include"Wall.h"

#include <GL/freeglut.h>

using namespace std;

Light light(boundaryX, boundaryY, boundaryX / 2, GL_LIGHT0);

clock_t start_t = clock();
clock_t end_t;

Player player(0.0f, -boundaryY + PLAYER_SIZE * 1.5f, 0.0f, PLAYER_SIZE);
Platform ground(0.0f, -boundaryY + PLAYER_SIZE * 0.5f, 0.0f, boundaryX * 2, PLAYER_SIZE);
vector<Bubble> bubbles;
vector<Stage> stages;

bool wallCollision(const vector<Wall>& walls, Player& player) {
	bool wallCollided = false;
	Vector3f center = player.getCenter();

	for (auto wall : walls) {
		if (wall.getTopEdge() >= center[1] - PLAYER_SIZE/2.0 && wall.getBottomEdge() <= center[1] + PLAYER_SIZE / 2.0 &&
			wall.getLeftEdge() <= center[0] + PLAYER_SIZE / 2.0 && wall.getRightEdge() >= center[0] - PLAYER_SIZE / 2.0) {
			wallCollided = true;
			Vector3f newCenter = player.getCenter();
			if (player.getHorizontalVelocity()[0] > 0) {
				newCenter[0] = wall.getLeftEdge() - PLAYER_SIZE / 2.0;
			}
			else if (player.getHorizontalVelocity()[0] < 0) {
				newCenter[0] = wall.getRightEdge() + PLAYER_SIZE / 2.0;
			}
			/*else if (player.getVerticalVelocity()[1] > 0) {
				newCenter[1] = wall.getBottomEdge() - PLAYER_SIZE / 2.0;
			}
			else if (player.getVerticalVelocity()[1] <= 0) {
				newCenter[1] = wall.getTopEdge() + PLAYER_SIZE / 2.0;
			}*/
			player.setCenter(newCenter);
		}
	}

	return wallCollided;
}

bool platformCollision(const vector<Platform>& platforms, Player& player) {
	bool platformCollided = false;
	Vector3f center = player.getCenter();

	for (auto& platform : platforms) {
		if (platform.getTopEdge() >= center[1] - PLAYER_SIZE / 2.0 && platform.getBottomEdge() <= center[1] + PLAYER_SIZE / 2.0 &&
			platform.getLeftEdge() <= center[0] + PLAYER_SIZE / 2.0 && platform.getRightEdge() >= center[0] - PLAYER_SIZE / 2.0) {
			platformCollided = true;
			Vector3f newCenter = player.getCenter();
			newCenter[1] = platform.getTopEdge() + PLAYER_SIZE / 2.0;
			player.setCenter(newCenter);
		}
	}

	return platformCollided;
}


void collisionHandler(const Stage& stage, Player& player) {
	vector<Platform> platforms = stage.getPlatforms();
	vector<Wall> walls = stage.getWalls();
	vector<Monster> monsters = stage.getMonsters();

	if (wallCollision(walls, player)) {
		player.setHorizontalState(Player::HORIZONTAL_STATE::STOP);
	}
	if (player.getVerticalVelocity()[1] <= 0) {
		// platform과 닿아있는 상태 (STOP)
		if (platformCollision(platforms, player)) {
			player.setVerticalState(Player::VERTICAL_STATE::STOP);
		}
		// platform에 닿아있다가 떨어지는 상태 (FALL)
		else {
			if (player.getAcceleration()[1] == 0) {
				player.setVerticalState(Player::VERTICAL_STATE::FALL);
			}
		}
	}
}

void idle() {
	/* Implement */
	end_t = clock();

	if ((float)(end_t - start_t) > 1000 / 30.0f) {
		start_t = end_t;

		player.horizontalmove();
		player.verticalmove();
		for (auto &bub : bubbles) {
			if (bub.getRadius() == 30) {
				Vector3f v(0.0f, 3.0f, 0.0f);
				bub.setVelocity(v);
			}
			bub.move();
			if (bub.getRadius() != 30) {
				bub.setRadius(bub.getRadius() + 2.0f);
			}
		}
		
		collisionHandler(stages[0], player);
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

	for (auto& stage : stages) {
		stage.draw();
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

		case GLUT_KEY_UP:
			if (player.getVerticalState() == Player::VERTICAL_STATE::STOP) {
				Vector3f newVelocity = player.getVerticalVelocity();
				newVelocity[1] = 30.0f;
				player.setVerticalVelocity(newVelocity);
				player.setVerticalState(Player::VERTICAL_STATE::JUMP);
			}
			break;


		default:
			break;
	}
}

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

void initialize() {
	player.setHorizontalState(Player::HORIZONTAL_STATE::STOP);
	player.setVerticalState(Player::VERTICAL_STATE::STOP);

	Stage stage1(0);
	
	vector<Platform> platforms1;
	platforms1.push_back(ground);
	platforms1.push_back(Platform(0, -10, 0, boundaryX, 50));
	platforms1.push_back(Platform(0, -180, 0, boundaryX, 50));
	platforms1.push_back(Platform(0, 160, 0, boundaryX, 50));
	platforms1.push_back(Platform(325, 160, 0, 50, 50));
	platforms1.push_back(Platform(-325, 160, 0, 50, 50));
	platforms1.push_back(Platform(325, -10, 0, 50, 50));
	platforms1.push_back(Platform(-325, -10, 0, 50, 50));
	platforms1.push_back(Platform(325, -180, 0, 50, 50));
	platforms1.push_back(Platform(-325,-180, 0, 50, 50));
	stage1.setPlatforms(platforms1);

	vector<Wall> walls1;
	walls1.push_back(Wall(boundaryX - PLAYER_SIZE / 2.0, 0, 0, PLAYER_SIZE, WINDOW_HEIGHT));
	walls1.push_back(Wall(-boundaryX + PLAYER_SIZE / 2.0, 0,0, PLAYER_SIZE, WINDOW_HEIGHT));
	stage1.setWalls(walls1);

	stages.push_back(stage1);
}

int main(int argc, char** argv) {
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(WINDOW_X, WINDOW_Y);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("(1) Move the player horizontally and (2) shoot bubble");

	initialize();

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
