#include "Level.h"
#include <fstream>
#include "ResourceManager.h"
#include "Error.h"


Level::Level(const std::string& fileName)
{
	std::ifstream file;
	file.open(fileName);
	if (file.fail()) {
		fatalError("failed to opem " + fileName);
	}
	std::string tmp;

	file >> tmp >> _numHumans;

	std::getline(file, tmp);
	while (std::getline(file, tmp)) {
		_levelData.push_back(tmp);
	}
	parseLevel();

}

void Level::draw() {
	_spriteBatch.renderBatch();
}


void Level::parseLevel() {
	_spriteBatch.init();
	_spriteBatch.begin();

	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	Color color{ 255, 255, 255, 255 };

	for (int y = 0; y < _levelData.size(); y++)
	{
		for (int x = 0; x < _levelData[y].size(); x++)
		{
			char tile = _levelData[y][x];
			glm::vec4 destRect(x*TILE_WIDTH, y*TILE_WIDTH,
							   TILE_WIDTH, TILE_WIDTH);
			switch (tile)
			{
			case 'R': _spriteBatch.draw(destRect, uvRect,
				ResourceManager::getTexture("Textures/LevelMap/red_bricks.png").id,
				0.0f, color); //red bricks
			case 'B':
				_spriteBatch.draw(destRect, uvRect,
					ResourceManager::getTexture("Textures/LevelMap/red_bricks.png").id,
					0.0f,color); //red bricks
				break;
			case 'G':
				_spriteBatch.draw(destRect, uvRect,
					ResourceManager::getTexture("Textures/LevelMap/glass.png").id,
					0.0f, color); //glass
				break;
			case 'L':
				_spriteBatch.draw(destRect, uvRect,
					ResourceManager::getTexture("Textures/LevelMap/light_bricks.png").id,
					0.0f, color); //light bricks
				break;
			case '@':
				_levelData[y][x] = '.';
				_playerPosition.x = x*TILE_WIDTH;
				_playerPosition.y = y*TILE_WIDTH;
				break;
			case 'Z':
				_levelData[y][x] = '.';
				_zombiesPosition.emplace_back(x*TILE_WIDTH, y*TILE_WIDTH);
				break;
			case '.':
				break;
			default:
				break;
			}
		}
	}
	_spriteBatch.end();
}


Level::~Level()
{
}
