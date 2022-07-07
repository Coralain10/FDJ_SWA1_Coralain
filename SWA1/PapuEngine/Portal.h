#pragma once
#include "Sprite.h"

class Portal : public Sprite
{
public:
	Portal();
	~Portal();

	void init(glm::vec2 position, std::string texturePath);
};
