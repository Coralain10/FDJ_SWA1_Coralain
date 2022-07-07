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
public:

	Background(std::string _path, Window* window);
	~Background();
	void draw(SpriteBacth& spriteBatch);
};

