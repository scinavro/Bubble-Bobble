#pragma once
#include"Monster.h"
#include"Platform.h"
#include"Wall.h"
#include<vector>

using namespace std;

class Stage {
public:
	Stage(int ID);
	void setPlatforms(const vector<Platform>& platforms);
	void setWalls(const vector<Wall>& walls);
	void setMonsters(const vector<Monster>& monsters);

	vector<Platform> getPlatforms() const;
	vector<Wall> getWalls() const;
	vector<Monster>& monstersControl();

	void eraseMonster(int i);

	void setstageFinished();
	bool getstageFinished();

	void draw() const;

private:
	int stageID;
	vector<Platform> Platforms;
	vector<Wall> Walls;
	vector<Monster>Monsters;
	bool isFinished;
};