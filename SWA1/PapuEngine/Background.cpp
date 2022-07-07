#include "Background.h"
#include "ResourceManager.h"

Background::Background(std::string _path, Window* window) : path(_path)
{
	_textureID = ResourceManager::getTexture(path).id;
	this->width = window->getScreenWidth();
	this->height = window->getScreenHeight();
	this->x = - int(width / 2);
	this->y = - int(height / 2);
}

Background::~Background()
{
}

void Background::draw(SpriteBacth& spriteBatch)
{
	Color color;
	color.r = 255;
	color.b = 255;
	color.g = 255;
	color.a = 255;
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(x, y, width, height);
	spriteBatch.draw(destRect, uvRect, _textureID, 0.0f, color);
}
