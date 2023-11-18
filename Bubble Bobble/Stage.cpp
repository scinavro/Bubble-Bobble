#include"Stage.h"

Stage::Stage(int ID) : stageID(ID) {}

void Stage::setPlatforms(const vector<Platform>& platforms) {
	Platforms = platforms;
}
void Stage::setWalls(const vector<Wall>& walls) {
	Walls = walls;
}
void Stage::setMonsters(const vector<Monster>& monsters) {
	Monsters = monsters;
}

vector<Platform> Stage::getPlatforms() const {
	return Platforms;
}

vector<Wall> Stage::getWalls() const {
	return Walls;
}

vector<Monster> Stage::getMonsters() const {
	return Monsters;
}

void Stage::setstageFinished() {
	isFinished = true;
}
bool Stage::getstageFinished() {
	return isFinished;
}
void Stage::draw() const {
	for (auto& platform : Platforms) {
		platform.draw();
	}
	for (auto& wall : Walls) {
		wall.draw();
	}
	for (auto& monster : Monsters) {
		monster.draw();
	}
}