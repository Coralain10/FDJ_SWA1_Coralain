#include "Door.h"

Door::Door() {}
Door::~Door() {}

void Door::init(glm::vec2 position, std::string texturePath) {
	_isOpen = false;
	_position = position;
	_texturePath = texturePath;
	color.set(255, 255, 255, 255);
}