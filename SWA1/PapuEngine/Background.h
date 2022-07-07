#pragma once
#include <glm/glm.hpp>
#include <string>
#include "SpriteBacth.h"
#include "GLTexture.h"
#include "Window.h"

class Background
{
private:
	std::string path;
	int _textureID;
	int width;
	int height;
	int x;
	int y;
	SpriteBacth _spriteBatch;
public:

	Background(std::string _path, Window* window);
	~Background();
	void draw();
	void setPosition(glm::vec2 position) {
		x = position.x;
		y = position.y;
	};
};

