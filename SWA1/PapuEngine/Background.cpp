#include "Background.h"
#include "ResourceManager.h"

Background::Background(std::string _path, Window* window) : path(_path)
{
	_textureID = ResourceManager::getTexture(path).id;
	this->width = window->getScreenWidth() + 8;
	this->height = window->getScreenHeight() + 8;
	this->x = - int(width / 2) - 4;
	this->y = - int(height / 2) - 4;
}

Background::~Background()
{
}

void Background::draw()
{
	_spriteBatch.init();
	_spriteBatch.begin();
	Color color{ 255,255,255,255 };
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(x, y, width, height);
	_spriteBatch.draw(destRect, uvRect, _textureID, 0.0f, color);
	_spriteBatch.end();
	_spriteBatch.renderBatch();
}
