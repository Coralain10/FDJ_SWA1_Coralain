#pragma once
#include "Sprite.h"

class Key : public Sprite
{
public:
	Key();
	~Key();

	void init(glm::vec2 position, std::string texturePath);
};

