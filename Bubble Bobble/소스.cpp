#include <iostream>
#include <vector>
#include<cmath>
#include<chrono>
#include<thread>

#include "Constants.h"
#include "Light.h"

#include "player.h"
#include "Platform.h"

#include "Stage.h"
#include"Wall.h"

#include"Monster.h"

#include"Texture.h"

#include <GL/freeglut.h>

using namespace std;

Light light(boundaryX, boundaryY, -boundaryX / 2, GL_LIGHT0);

clock_t start_t = clock();
clock_t end_t;

Player* player;
Player* player_2;
vector<Bubble> bubbles;
vector<Bubble> bubbles_2;
vector<vector<Bubble>> smallbubbles;
vector<Stage> stages;
Texture endImage;
Texture startImage;
Texture backgroundImage;
int currentStage = -1;

void initialize() {
	player = new Player(-200.0f, -boundaryY + PLAYER_SIZE * 1.5f, 0.0f, PLAYER_SIZE);
	player_2 = new Player(200.0f, -boundaryY + PLAYER_SIZE * 1.5f, 0.0f, PLAYER_SIZE);
	startImage.initializeTexture("GameStart.png");
	endImage.initializeTexture("GameOver.png");
	backgroundImage.initializeTexture("Background.png");
	player->setHorizontalState(Player::HORIZONTAL_STATE::STOP);
	player->setVerticalState(Player::VERTICAL_STATE::STOP);
	player_2->setHorizontalState(Player::HORIZONTAL_STATE::STOP);
	player_2->setVerticalState(Player::VERTICAL_STATE::STOP);

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
	platforms1.push_back(Platform(-325, -180, 0, 50, 50));
	stage1.setPlatforms(platforms1);

	vector<Wall> walls1;
	walls1.push_back(Wall(boundaryX - PLAYER_SIZE / 2.0, 0, 0, PLAYER_SIZE, WINDOW_HEIGHT));
	walls1.push_back(Wall(-boundaryX + PLAYER_SIZE / 2.0, 0, 0, PLAYER_SIZE, WINDOW_HEIGHT));
	stage1.setWalls(walls1);

	vector<Monster> monsters1;
	Monster m1(50); m1.setPlatform(p1); m1.setMonsterId(0);
	monsters1.push_back(m1);
	stage1.setMonsters(monsters1);
	Monster m2(50); m2.setPlatform(p2); m2.setMonsterId(1);
	monsters1.push_back(m2);
	stage1.setMonsters(monsters1);
	Monster m3(50); m3.setPlatform(p3); m3.setMonsterId(2);
	monsters1.push_back(m3);
	stage1.setMonsters(monsters1);

	stages.push_back(stage1);

	Stage stage2(1);

	vector<Platform> platforms2;
	Platform ground3(0.0f, -boundaryY + PLAYER_SIZE * 0.5f, 0.0f, boundaryX * 2, PLAYER_SIZE);
	platforms2.push_back(ground3);
	Platform p7(225, -75, 0, 250, 50);
	Platform p8(-225, -75, 0, 250, 50);
	Platform p5(0, -180, 0, boundaryX, 50);
	Platform p6(0, 160, 0, boundaryX, 50);
	Platform p9(-boundaryX + PLAYER_SIZE * 0.5f, -75, 0, 50, 50);
	Platform p10(+boundaryX - PLAYER_SIZE * 0.5f, -75, 0, 50, 50);
	platforms2.push_back(Platform(p9));
	platforms2.push_back(Platform(p10));
	platforms2.push_back(Platform(p7));
	platforms2.push_back(Platform(p8));
	platforms2.push_back(Platform(p5));
	platforms2.push_back(Platform(p6));
	stage2.setPlatforms(platforms2);

	vector<Wall> walls2;
	walls2.push_back(Wall(-boundaryX + PLAYER_SIZE * 0.5f, -225.0f, 0.0f, PLAYER_SIZE, 250.0f));
	walls2.push_back(Wall(-boundaryX + PLAYER_SIZE * 0.5f, 225.0f, 0.0f, PLAYER_SIZE, 350.0f));
	walls2.push_back(Wall(+boundaryX - PLAYER_SIZE * 0.5f, -225.0f, 0.0f, PLAYER_SIZE, 250.0f));
	walls2.push_back(Wall(+boundaryX - PLAYER_SIZE * 0.5f, 225.0f, 0.0f, PLAYER_SIZE, 350.0f));
	stage2.setWalls(walls2);

	vector<Monster> monsters2;
	/*Monster m4(50); m4.setPlatform(p4); m4.setMonsterId(3);
	monsters2.push_back(m4);*/
	stage2.setMonsters(monsters2);
	Monster m5(50); m5.setPlatform(p5); m5.setMonsterId(0);
	monsters2.push_back(m5);
	stage2.setMonsters(monsters2);
	Monster m6(50); m6.setPlatform(p6); m6.setMonsterId(1);
	monsters2.push_back(m6);
	stage2.setMonsters(monsters2);

	stages.push_back(stage2);

}

bool blockedByWall;

bool wallCollision(const vector<Wall>& walls, Player* player) {
	bool wallCollided = false;
	Vector3f center = player->getCenter();
	blockedByWall = false;

	for (auto wall : walls) {
		if (wall.getTopEdge() > center[1] - PLAYER_SIZE / 2.0 && wall.getBottomEdge() < center[1] + PLAYER_SIZE / 2.0 &&
			wall.getLeftEdge() < center[0] + PLAYER_SIZE / 2.0 && wall.getRightEdge() > center[0] - PLAYER_SIZE / 2.0) {
			wallCollided = true;
			Vector3f newCenter = player->getCenter();
			if (player->getHorizontalVelocity()[0] > 0) {
				newCenter[0] = wall.getLeftEdge() - PLAYER_SIZE / 2.0 - 0.001;
			}
			else if (player->getHorizontalVelocity()[0] < 0) {
				newCenter[0] = wall.getRightEdge() + PLAYER_SIZE / 2.0 + 0.001;
			}
			/*else if (player->getVerticalVelocity()[1] > 0) {
				newCenter[1] = wall.getBottomEdge() - PLAYER_SIZE / 2.0;
			}
			else if (player->getVerticalVelocity()[1] <= 0) {
				newCenter[1] = wall.getTopEdge() + PLAYER_SIZE / 2.0;
			}*/
			player->setCenter(newCenter);
			blockedByWall = true;
		}
	}

	return wallCollided;
}

bool platformCollision(const vector<Platform>& platforms, Player* player) {
	bool platformCollided = false;
	Vector3f center = player->getCenter();

	for (auto& platform : platforms) {
		if (platform.getTopEdge() >= center[1] - PLAYER_SIZE / 2.0 && platform.getBottomEdge() <= center[1] + PLAYER_SIZE / 2.0 &&
			platform.getLeftEdge() <= center[0] + PLAYER_SIZE / 2.0 && platform.getRightEdge() >= center[0] - PLAYER_SIZE / 2.0) {
			platformCollided = true;
			Vector3f newCenter = player->getCenter();
			newCenter[1] = platform.getTopEdge() + PLAYER_SIZE / 2.0;
			player->setCenter(newCenter);
		}
	}

	return platformCollided;
}


void collisionHandler(const Stage& stage, Player* player) {
	vector<Platform> platforms = stage.getPlatforms();
	vector<Wall> walls = stage.getWalls();
	//vector<Monster> monsters = stage.monster();

	if (wallCollision(walls, player)) {
		player->setHorizontalState(Player::HORIZONTAL_STATE::STOP);
	}
	if (player->getVerticalVelocity()[1] < 0) {
		// platform과 닿아있는 상태 (STOP)
		if (platformCollision(platforms, player)) {
			player->setVerticalState(Player::VERTICAL_STATE::STOP);
		}
	}
		// platform에 닿아있다가 떨어지는 상태 (FALL)
	if (player->getVerticalVelocity()[1] == 0 && player->getAcceleration()[1] == 0) {
		if (!platformCollision(platforms, player)) {
			player->setVerticalState(Player::VERTICAL_STATE::FALL);
		}
	}

	if (player->getCenter()[1] - player->getSize() / 2.0 <= -boundaryY) {
		player->setCenter(Vector3f(player->getCenter()[0], player->getCenter()[1] + boundaryY * 2, 0));
	}
	if (player->getCenter()[0] - player->getSize() / 2.0 <= -boundaryX || player->getCenter()[0] + player->getSize() / 2.0 >= boundaryX) {
			player->setCenter(Vector3f(-player->getCenter()[0], player->getCenter()[1], 0));
	}
}

bool MonsterBubbleCollision(Monster monster, Bubble bubble) {
	bool bubblemonstercollided = false;
	
	float distance = sqrt(pow(monster.getCenter()[0] - bubble.getCenter()[0], 2) + pow(monster.getCenter()[1] - bubble.getCenter()[1], 2));
	if (distance <= PLAYER_SIZE/2) {
		bubblemonstercollided = true;
	}
	
	return bubblemonstercollided;
}

void MonsterDeathHanler(Stage& stage, vector<Bubble> &bubbles) {
	for (auto& monster : stage.monstersControl()) {
		for (auto& bubble : bubbles) {
			if (bubble.getRadius() < 30) {
				if (MonsterBubbleCollision(monster, bubble)) {
					monster.setMonsterlifeTrapped();
					bubble.setBubbleTrapping();
					bubble.setRadius(30);
					bubble.setVelocity(Vector3f(0, 3.3, 0));
					bubble.setAcceleration(Vector3f(0, -0.05, 0));
					bubble.setMonsterId(monster.getMonsterId());
					break;
				}
			}
		}
	}
}

bool PlayerBubbleCollision(vector<Vector3f>vertexes, Bubble bubble) {
	bool playerBubbleCollided = false;
	if (bubble.getRadius() == 30) {
		for (auto& vertex : vertexes) {
			float distance = sqrt(pow(bubble.getCenter()[0] - vertex[0], 2) + pow(bubble.getCenter()[1] - vertex[1], 2));
			if (distance <= bubble.getRadius()) {
				playerBubbleCollided = true;
				break;
			}
		}
	}
	return playerBubbleCollided;
}

void BubblePopEffect(Bubble bubble) {
	vector<Bubble> bubblepop;
	Vector3f currentCenter = bubble.getCenter();
	Bubble b1(4, 20, 20); b1.setCenter(currentCenter); b1.setVelocity(Vector3f(6, 6, 0)); b1.setAcceleration(Vector3f(0, -1, -2)); bubblepop.push_back(b1); 
	Bubble b2(4, 20, 20); b2.setCenter(currentCenter); b2.setVelocity(Vector3f(6, 4, 0)); b2.setAcceleration(Vector3f(0, -1, -2)); bubblepop.push_back(b2);
	Bubble b3(4, 20, 20); b3.setCenter(currentCenter); b3.setVelocity(Vector3f(-6, 6, 0)); b3.setAcceleration(Vector3f(0, -1, -2)); bubblepop.push_back(b3); 
	Bubble b4(4, 20, 20); b4.setCenter(currentCenter); b4.setVelocity(Vector3f(-6, 4, 0)); b4.setAcceleration(Vector3f(0, -1, -2)); bubblepop.push_back(b4); 
	smallbubbles.push_back(bubblepop);
}

void PlayerBubblePop(Player *player, vector<Bubble>& bubbles) {
	for (int i = 0; i < bubbles.size();) {

		if (PlayerBubbleCollision(player->getvertex(), bubbles[i])) {
			if (bubbles[i].getStatus() == Bubble::STATUS::TRAPPING) {
				// MONSTER SET DEAD
				stages[currentStage].killMonster(bubbles[i].getMonsterId());
			}
			BubblePopEffect(bubbles[i]);
			bubbles.erase(bubbles.begin() + i);
		}
		else {
			i++;
		}
	}

}

bool PlayerMonsterCollision(vector<Vector3f>vertexes, Player* player) {
	bool playerMonsterCollided = false;
	for (auto& vertex : vertexes) {
		if (vertex[0] <= player->getCenter()[0] + player->getSize() / 2.0 && vertex[0] >= player->getCenter()[0] - player->getSize() / 2.0 && vertex[1] <= player->getCenter()[1] + player->getSize() / 2.0 && vertex[1] >= player->getCenter()[1] - player->getSize() / 2.0) {
			playerMonsterCollided = true;
			break;
		}
	}
	return playerMonsterCollided;
}

void PlayerDeathHanler(Stage& stage, Player* player) {
	for (auto& monster : stage.monstersControl()) {
		if (monster.getMonsterStatus() == Monster::STATUS::LIVE) {
			if (PlayerMonsterCollision(monster.getvertex(), player)) {
				player->PlayerLifeDeduced();
				Vector3f newCenter(-200.0f, -boundaryY + PLAYER_SIZE * 1.5f, 0.0f);
				player->setCenter(newCenter);
				break;
			}
		}
	}
}

bool BubbleCollidedWall(Bubble& bubble, Stage& stage) {
	bool BubbleCollided = false;
	Vector3f center = bubble.getCenter();
	for (auto wall : stage.getWalls()) {
		if ((center[0] - bubble.getRadius() <= wall.getRightEdge() && center[0] - bubble.getRadius() >= wall.getLeftEdge()) || (center[0] + bubble.getRadius() >= wall.getLeftEdge() && center[0] + bubble.getRadius() <= wall.getRightEdge())) {
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

void displayCharacters(void* font, string str, float x, float y) {
	glRasterPos2f(x, y);
	for (int i = 0; i < str.size(); i++) {
		glutBitmapCharacter(font, str[i]);
	}
}

bool checkBubble(int i) {
	bool bubbleExist = false;
	for (auto bubble : bubbles) {
		if (bubble.getMonsterId() == i) {
			bubbleExist = true;
		}
	}
	return bubbleExist;
}

bool checkBubble_2(int i) {
	bool bubbleExist = false;
	for (auto bubble : bubbles_2) {
		if (bubble.getMonsterId() == i) {
			bubbleExist = true;
		}
	}
	return bubbleExist;
}

void idle() {
	/* Implement */
	end_t = clock();
	if (currentStage < stages.size()) {
		if (player->getPlayerLife() == 0 || player_2->getPlayerLife()==0) {
			exit;
		}
		else {
			if ((float)(end_t - start_t) > 1000 / 60.0f) {
				start_t = end_t;

				player->horizontalmove();
				player->verticalmove();
				player_2->horizontalmove();
				player_2->verticalmove();
				Vector3f monsterCenter;
				for (int i = 0; i < bubbles.size();) {
					bubbles[i].move();
					if (bubbles[i].getStatus() == Bubble::STATUS::TRAPPING) {
						if (bubbles[i].getVelocity()[1] <= 0) {
							monsterCenter.setPos(bubbles[i].getCenter()[0], bubbles[i].getCenter()[1], bubbles[i].getCenter()[2]);
							BubblePopEffect(bubbles[i]);
							bubbles.erase(bubbles.begin() + i);
							break;
						}
					}
					else {
						if (bubbles[i].getRadius() >= 30) {
							bubbles[i].setRadius(30);
							Vector3f v(0.0f, 3.0f, 0.0f);
							bubbles[i].setVelocity(v);
						}
						else {
							float BubbleSizeVelocity = 2.0f;
							if (BubbleCollidedWall(bubbles[i], stages[currentStage])) {
								Vector3f v(0.0f, 0.0f, 0.0f);
								bubbles[i].setVelocity(v);
								BubbleSizeVelocity = 7.0f;
							}
							else {
								BubbleSizeVelocity = 2.0f;
							}
							bubbles[i].setRadius(bubbles[i].getRadius() + BubbleSizeVelocity);
						}
					}
					i++;
				}
				for (int i = 0; i < bubbles_2.size();) {
					bubbles_2[i].move();
					if (bubbles_2[i].getStatus() == Bubble::STATUS::TRAPPING) {
						if (bubbles_2[i].getVelocity()[1] <= 0) {
							monsterCenter.setPos(bubbles_2[i].getCenter()[0], bubbles_2[i].getCenter()[1], bubbles_2[i].getCenter()[2]);
							BubblePopEffect(bubbles_2[i]);
							bubbles_2.erase(bubbles_2.begin() + i);
							break;
						}
					}
					else {
						if (bubbles_2[i].getRadius() >= 30) {
							bubbles_2[i].setRadius(30);
							Vector3f v(0.0f, 3.0f, 0.0f);
							bubbles_2[i].setVelocity(v);
						}
						else {
							float BubbleSizeVelocity = 2.0f;
							if (BubbleCollidedWall(bubbles_2[i], stages[currentStage])) {
								Vector3f v(0.0f, 0.0f, 0.0f);
								bubbles_2[i].setVelocity(v);
								BubbleSizeVelocity = 7.0f;
							}
							else {
								BubbleSizeVelocity = 2.0f;
							}
							bubbles_2[i].setRadius(bubbles_2[i].getRadius() + BubbleSizeVelocity);
						}
					}
					i++;
				}
				for (auto& bub : smallbubbles) {
					for (auto& bubpop : bub) {
						bubpop.move();
						if (bubpop.getAcceleration()[2] == -6) {
							smallbubbles.erase(smallbubbles.begin());
						}
					}
				}
				for (auto& monster : stages[currentStage].monstersControl()) {
					if (monster.getMonsterStatus() == Monster::STATUS::LIVE) {
						monster.move();
						if (!monster.getMonsterOnPlatform()) {
							if (monster.getCenter()[1] <= monster.getPlatform().getTopEdge() + monster.getMonsterSize()/2.0) {
								Vector3f newCenter(monster.getCenter()[0], monster.getPlatform().getTopEdge()+monster.getMonsterSize()/2.0, 0);
								monster.setCenter(newCenter);
								monster.setMonsterFaceLeft();
								monster.setMonsterOnPlatform();
							}
						}
					}
					else if ((monster.getMonsterStatus() == Monster::STATUS::DEAD)) {
						stages[currentStage].eraseMonster(monster.getMonsterId());
					}
					else if (monster.getMonsterStatus() == Monster::STATUS::TRAP) {
						if (!checkBubble(monster.getMonsterId())&& !checkBubble_2(monster.getMonsterId())) {
							monster.setMonsterLifeLive();
							monster.setCenter(monsterCenter);
							monster.setMonsterFaceDown();
							monster.setMonsterNotOnPlatform();
						}
					}
					
				}

				MonsterDeathHanler(stages[currentStage], bubbles);
				MonsterDeathHanler(stages[currentStage], bubbles_2);

				PlayerBubblePop(player, bubbles);
				PlayerDeathHanler(stages[currentStage], player);
				collisionHandler(stages[currentStage], player);

				PlayerBubblePop(player_2, bubbles_2);
				PlayerDeathHanler(stages[currentStage], player_2);
				collisionHandler(stages[currentStage], player_2);


			}
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

	if (currentStage == -1) {
		Vector3f center(0, 0, 0);
		startImage.setcenter(center);
		startImage.setSize(800);
		startImage.texture();
	}

	if (currentStage > -1 && currentStage < 2) {
		Vector3f center(0, 0, 0);
		backgroundImage.setcenter(center);
		backgroundImage.setSize(800);
		backgroundImage.texture();
	}

	if (currentStage == 2) {
		Vector3f center(0, 0, 0);
		endImage.setcenter(center);
		endImage.setSize(400);
		endImage.texture();
		delete player;
		delete player_2;
		
	}

	if (currentStage < stages.size()) {
		if (player->getPlayerLife() == 0) {
			glColor3f(1.0f, 1.0f, 1.0f);
			displayCharacters(GLUT_BITMAP_8_BY_13, "PLAYER DEAD ------ GAME END", -100.0f, 100.0f);
		}
		else if (player->getPlayerLife() == 1) {
			glColor3f(1.0f, 0.0f, 0.0f);
			displayCharacters(GLUT_BITMAP_8_BY_13, "PLAYER LIFE : 1", -330.0f, 380.0f);
		}
		else if (player->getPlayerLife() == 2) {
			glColor3f(1.0f, 0.0f, 0.0f);
			displayCharacters(GLUT_BITMAP_8_BY_13, "PLAYER LIFE : 2", -330.0f, 380.0f);
		}
		else if (player->getPlayerLife() == 3) {
			glColor3f(1.0f, 0.0f, 0.0f);
			displayCharacters(GLUT_BITMAP_8_BY_13, "PLAYER LIFE : 3", -330.0f, 380.0f);
		}

		if (player_2->getPlayerLife() == 0) {
			glColor3f(1.0f, 1.0f, 1.0f);
			displayCharacters(GLUT_BITMAP_8_BY_13, "PLAYER 2 DEAD ------ GAME END", -100.0f, 100.0f);
		}
		else if (player_2->getPlayerLife() == 1) {
			glColor3f(1.0f, 0.0f, 0.0f);
			displayCharacters(GLUT_BITMAP_8_BY_13, "PLAYER 2 LIFE : 1", 200.0f, 380.0f);
		}
		else if (player_2->getPlayerLife() == 2) {
			glColor3f(1.0f, 0.0f, 0.0f);
			displayCharacters(GLUT_BITMAP_8_BY_13, "PLAYER 2 LIFE : 2", 200.0f, 380.0f);
		}
		else if (player_2->getPlayerLife() == 3) {
			glColor3f(1.0f, 0.0f, 0.0f);
			displayCharacters(GLUT_BITMAP_8_BY_13, "PLAYER 2 LIFE : 3", 200.0f, 380.0f);
		}

		if (currentStage < stages.size()) {
			if (stages[currentStage].monstersControl().size() == 0) {
				currentStage += 1;
				Vector3f center(-200.0f, -boundaryY + PLAYER_SIZE * 1.5f, 0.0f);
				player->setCenter(center);
				Vector3f center_2(200.0f, -boundaryY + PLAYER_SIZE * 1.5f, 0.0f);
				player_2->setCenter(center_2);
			}
		}


		// Draw 2D
		player->draw();
		player_2->draw();
		
		// Draw 3D
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glEnable(light.getID());

		light.setAmbient(1.0f, 1.0f, 1.0f, 1.0f);
		light.setDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
		light.setSpecular(1.0f, 1.0f, 1.0f, 1.0f);

		light.draw();

		/* Implement: Draw bubbles */

		for (auto& bub : bubbles) {
			bub.draw();
		}
		for (auto& bub : bubbles_2) {
			bub.draw();
		}

		glDisable(light.getID());
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);

		for (auto& bub : smallbubbles) {
			for (auto& bubpop : bub) {
				glColor3f(1, 0, 0);
				bubpop.draw();
			}
		}
		if (currentStage < stages.size()) {
			stages[currentStage].draw();
		}
	}
	

	glutSwapBuffers();
}

void keyboardDown(unsigned char key, int x, int y) {
	/* Implement */
	if (key == ' ') {
		if (currentStage == -1)
			currentStage++;
		else
			bubbles.push_back(player->shootBubble());
	}
	if (key == '2') {
		bubbles_2.push_back(player_2->shootBubble());
	}
	if (key == '1') {
		exit(0);
	}

}

void specialKeyDown(int key, int x, int y) {
	/* Implement */
	switch (key) {
		case GLUT_KEY_LEFT:
			player->setFace(Player::FACE::LEFT);
			if (!blockedByWall)
				player->setHorizontalState(Player::HORIZONTAL_STATE::MOVE);
			break;

		case GLUT_KEY_RIGHT:
			player->setFace(Player::FACE::RIGHT);
			if (!blockedByWall)
				player->setHorizontalState(Player::HORIZONTAL_STATE::MOVE);
			break;

		case GLUT_KEY_UP:
			if (player->getVerticalVelocity()[1] < 1 && player->getVerticalVelocity()[1] > -1) {
				Vector3f newVelocity = player->getVerticalVelocity();
				newVelocity[1] = 30.0f;
				player->setVerticalVelocity(newVelocity);
				player->setVerticalState(Player::VERTICAL_STATE::JUMP);
			}
			break;
		case GLUT_KEY_F1:
			player_2->setFace(Player::FACE::LEFT);
			if (!blockedByWall)
				player_2->setHorizontalState(Player::HORIZONTAL_STATE::MOVE);
			break;

		case GLUT_KEY_F2:
			player_2->setFace(Player::FACE::RIGHT);
			if (!blockedByWall)
				player_2->setHorizontalState(Player::HORIZONTAL_STATE::MOVE);
			break;

		case GLUT_KEY_F3:
			if (player_2->getVerticalVelocity()[1] < 1 && player_2->getVerticalVelocity()[1] > -1) {
				Vector3f newVelocity = player_2->getVerticalVelocity();
				newVelocity[1] = 30.0f;
				player_2->setVerticalVelocity(newVelocity);
				player_2->setVerticalState(Player::VERTICAL_STATE::JUMP);
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
		player->setHorizontalState(Player::HORIZONTAL_STATE::STOP);
		break;

	case GLUT_KEY_RIGHT:
		player->setHorizontalState(Player::HORIZONTAL_STATE::STOP);
		break;
	case GLUT_KEY_F1:
		player_2->setHorizontalState(Player::HORIZONTAL_STATE::STOP);
		break;

	case GLUT_KEY_F2:
		player_2->setHorizontalState(Player::HORIZONTAL_STATE::STOP);
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
	glutCreateWindow("Bubble---Bobble");

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
