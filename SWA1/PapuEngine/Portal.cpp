#include "Portal.h"

Portal::Portal() { }
Portal::~Portal() { }

void Portal::init(glm::vec2 position, std::string texturePath) {
	_position = position;
	_texturePath = texturePath;
	color.set(255, 255, 255, 255);
}