#pragma once
#include <string>
#include <vector>
#include "SpriteBacth.h"

using namespace std;

const int TILE_WIDTH = 64;
class Level
{

private:
	vector<string> _levelData;
	int _numHumans;
	void parseLevel();
public:

	int getNumHumans() const {
		return _numHumans;
	}
	glm::vec2 _playerPosition;
	std::vector<glm::vec2> _zombiesPosition;
	glm::vec2 getPlayerPosition() const { 
		return _playerPosition; 
	};

	const std::vector<std::string>& getLevelData() {
		return _levelData;
	}
	int getWidth() const {
		return _levelData[0].size();
	}
	int getHeight() const {
		return _levelData.size();
	}
	std::vector<glm::vec2> getZombiesPosition()const {
		return _zombiesPosition;
	};

	void setDot(glm::vec2 pos) {
		_levelData[pos.y / TILE_WIDTH][pos.x / TILE_WIDTH] = '.';
	}

	Level(const std::string& fileName);
	void draw();
	SpriteBacth _spriteBatch;
	~Level();
};

