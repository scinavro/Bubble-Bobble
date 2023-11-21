#include <iostream>
#include <vector>
#include<cmath>

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

Player player(-200.0f, -boundaryY + PLAYER_SIZE * 1.5f, 0.0f, PLAYER_SIZE);
vector<Bubble> bubbles;
vector<Stage> stages;

bool blockedByWall;

bool wallCollision(const vector<Wall>& walls, Player& player) {
	bool wallCollided = false;
	Vector3f center = player.getCenter();
	blockedByWall = false;

	for (auto wall : walls) {
		if (wall.getTopEdge() > center[1] - PLAYER_SIZE/2.0 && wall.getBottomEdge() < center[1] + PLAYER_SIZE / 2.0 &&
			wall.getLeftEdge() < center[0] + PLAYER_SIZE / 2.0 && wall.getRightEdge() > center[0] - PLAYER_SIZE / 2.0) {
			wallCollided = true;
			Vector3f newCenter = player.getCenter();
			if (player.getHorizontalVelocity()[0] > 0) {
				newCenter[0] = wall.getLeftEdge() - PLAYER_SIZE / 2.0 - 0.001;
			}
			else if (player.getHorizontalVelocity()[0] < 0) {
				newCenter[0] = wall.getRightEdge() + PLAYER_SIZE / 2.0 + 0.001;
			}
			/*else if (player.getVerticalVelocity()[1] > 0) {
				newCenter[1] = wall.getBottomEdge() - PLAYER_SIZE / 2.0;
			}
			else if (player.getVerticalVelocity()[1] <= 0) {
				newCenter[1] = wall.getTopEdge() + PLAYER_SIZE / 2.0;
			}*/
			player.setCenter(newCenter);
			blockedByWall = true;
		}
	}

	return wallCollided;
}

bool platformCollision(const vector<Platform>& platforms, Player& player) {
	bool platformCollided = false;
	Vector3f center = player.getCenter();

	for (auto& platform : platforms) {
		if (platform.getTopEdge() > center[1] - PLAYER_SIZE / 2.0 && platform.getBottomEdge() < center[1] + PLAYER_SIZE / 2.0 &&
			platform.getLeftEdge() < center[0] + PLAYER_SIZE / 2.0 && platform.getRightEdge() > center[0] - PLAYER_SIZE / 2.0) {
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
	if (player.getCenter()[1] - player.getSize()/2.0 <= -boundaryY) {
		player.setCenter(Vector3f(player.getCenter()[0], player.getCenter()[1] + boundaryY * 2, 0));
	}
}

bool MonsterBubbleCollision(vector<Vector3f>vertexes, Bubble bubble) {
	bool bubblemonstercollided = false;
	for (auto& vertex : vertexes) {
		float distance = sqrt(pow(bubble.getCenter()[0] - vertex[0], 2) + pow(bubble.getCenter()[1] - vertex[1], 2));
		if (distance <= bubble.getRadius()) {
			bubblemonstercollided = true;
			break;
		}
	}
	return bubblemonstercollided;
}

void MonsterDeathHanler(const Stage& stage, vector<Bubble> bubbles) {
	for (auto& monster : stage.getMonsters()) {
		for (auto& bubble : bubbles) {
			if (MonsterBubbleCollision(monster.getvertex(), bubble)) {
				monster.setMonsterlifedead();
				break;
			}
		}
	}
}

bool BubbleCollidedWall(Bubble &bubble) {
	bool BubbleCollided = false;
	Vector3f center = bubble.getCenter();
	for (auto wall : stages[0].getWalls()) {
		if ((center[0]-bubble.getRadius()<=wall.getRightEdge()&&center[0]-bubble.getRadius()>=wall.getLeftEdge())|| (center[0] + bubble.getRadius() >= wall.getLeftEdge() && center[0] + bubble.getRadius() <= wall.getRightEdge())) {
			BubbleCollided = true;
			Vector3f newCenter = bubble.getCenter();
			if (bubble.getVelocity()[0] > 0) {
				newCenter[0] = wall.getLeftEdge() - 30;
			}
			else if (bubble.getVelocity()[0] < 0) {
				newCenter[0] = wall.getRightEdge() + 30;
			}
			bubble.setCenter(newCenter);
		}
	}
	return BubbleCollided;
}

void idle() {
	/* Implement */
	end_t = clock();

	if ((float)(end_t - start_t) > 1000 / 60.0f) {
		start_t = end_t;
		player.horizontalmove();
		player.verticalmove();
		for (auto &bub : bubbles) {
			bub.move();
			if (bub.getRadius() >= 30) { 
				bub.setRadius(30);
				Vector3f v(0.0f, 3.0f, 0.0f);
				bub.setVelocity(v);
			}
			else {
				float BubbleSizeVelocity = 2.0f;
				if(BubbleCollidedWall(bub)) {
					Vector3f v(0.0f, 0.0f, 0.0f);
					bub.setVelocity(v);
					BubbleSizeVelocity = 7.0f;
				}
				else {
					BubbleSizeVelocity = 2.0f;
				}
				bub.setRadius(bub.getRadius() + BubbleSizeVelocity);
			}
		}
		for (auto& stage : stages) {
			for (auto& monster : stage.getMonsters()) {
				if (monster.getMonsterLife()) {
					monster.move();
				}
				else {
					// monster erase 해결하기
				}
				
			}
		}


		MonsterDeathHanler(stages[0], bubbles); 

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
			if (!blockedByWall)
				player.setHorizontalState(Player::HORIZONTAL_STATE::MOVE);
			break;

		case GLUT_KEY_RIGHT:
			player.setFace(Player::FACE::RIGHT);
			if (!blockedByWall)
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
	Platform ground1(-225.0f, -boundaryY + PLAYER_SIZE * 0.5f, 0.0f, 350.0f, PLAYER_SIZE);
	Platform ground2(225.0f, -boundaryY + PLAYER_SIZE * 0.5f, 0.0f, 350.0f, PLAYER_SIZE);
	platforms1.push_back(ground1);
	platforms1.push_back(ground2);
	Platform p1(0, -10, 0, boundaryX, 50);
	Platform p2(0, -180, 0, boundaryX, 50);
	Platform p3(0, 160, 0, boundaryX, 50);
	platforms1.push_back(Platform(p1));
	platforms1.push_back(Platform(p2));
	platforms1.push_back(Platform(p3));
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

	vector<Monster> monsters1;
	Monster m1(0, 210, 0, 50); m1.setPlatform(p1);
	monsters1.push_back(m1);
	stage1.setMonsters(monsters1);

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
