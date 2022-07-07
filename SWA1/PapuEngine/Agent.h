#pragma once
#include <glm\glm.hpp>
#include <string>
#include "SpriteBacth.h"
#include "GLTexture.h"
#include "Sprite.h"


class Zombie;
class Human;

const float AGENT_WIDTH = 64.0f;
const float AGENT_RADIUS = AGENT_WIDTH / 2.0f;

class Agent : public Sprite
{
protected:
	float _speed;
	void checkTilePosition(const std::vector<std::string>& levelData, 
		std::vector<glm::vec2>& collideTilePosition,float x, float y );
	void collideWithTile(glm::vec2 tilePos);

public:
	Agent();
	virtual void update(const std::vector<std::string>& levelData,
						std::vector<Human*>& humans,
						std::vector<Zombie*>& zombies) = 0;
	bool collideWithLevel(const std::vector<std::string>& levelData);
	virtual ~Agent();
	bool collideWithAgent(Agent* agent);
};

