#include "Button.h"
#include "ResourceManager.h"
#include <iostream>

Button::Button(std::string _path) :path(_path),
width(100), height(100), x(0), y(0)
{
	_textureID = ResourceManager::getTexture(path).id;
}

Button::Button(std::string _path, int x, int y) :path(_path),
width(100), height(100), x(x), y(y)
{
	_textureID = ResourceManager::getTexture(path).id;
}

Button::Button(std::string _path, int x, int y, int width, int height) :path(_path),
width(width), height(height), x(x), y(y)
{
	_textureID = ResourceManager::getTexture(path).id;
}

Button::~Button()
{
}

void Button::setSize(int width, int height)
{
	this->width = width;
	this->height = height;
}

void Button::setPosition(int x, int y)
{
	this->x = x;
	this->y = -y;
}

void Button::draw(SpriteBacth& spriteBatch)
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

bool Button::click(glm::vec2 position)
{
	if (position.x >= x && position.x <= x + width) {
		std::cout << "Las x son iguales" << std::endl;
		if (position.y >= y && position.y <= y + height) {
			std::cout << "Las y son iguales" << std::endl;
			return true;
		}
	}
	return false;
}
