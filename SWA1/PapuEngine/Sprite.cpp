#include "Sprite.h"
#include "ResourceManager.h"

Sprite::Sprite() {
	uvRect = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
}

Sprite::~Sprite() { }

void Sprite::draw(SpriteBacth& spritebatch) {
	int textureID = ResourceManager::getTexture(_texturePath).id;
	//const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(_position.x, _position.y, SPRITE_WIDTH, SPRITE_WIDTH);
	spritebatch.draw(destRect, uvRect, textureID, 0.0f, color);
}

void Sprite::setUvRect(GLfloat x, GLfloat y, GLfloat width, GLfloat height)
{
	uvRect = glm::vec4(x, y, width, height);
}
