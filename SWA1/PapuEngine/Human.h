#pragma once
#include "Agent.h"

enum ColorClasses { ENEMY_YELLOW, ENEMY_RED, ENEMY_GREEN };

class Human : public Agent
{

protected:
	glm::vec2 _direction;
public:
	ColorClasses _colorType;
	Human();
	~Human();
	void init(float speed, glm::vec2 position, std::string texturePath, ColorClasses colorType);

	void update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans);
};

