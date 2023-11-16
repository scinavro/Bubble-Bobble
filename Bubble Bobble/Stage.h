#pragma once
#include"Monster.h"
#include"Platform.h"
#include"Wall.h"
#include<vector>


class Stage {
public:
	Stage();
	void setPlatforms();
	void setWalls();
	void setMonsters();

	void setstageFinished();
	bool getstageFinished();

	void draw();
private:
	vector<Platform> Platforms;
	vector<Wall> Walls;
	vector<Monster>Monsters;
	bool isFinished;
};