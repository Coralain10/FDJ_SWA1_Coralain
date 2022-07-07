#pragma once
#include <glm/glm.hpp>
#include <string>
#include "SpriteBacth.h"
#include "GLTexture.h"

class Button
{
private:
	std::string path;
	int _textureID;
protected:
	int width;
	int height;
	int x;
	int y;
public:
	Button(std::string _path);
	Button(std::string _path, int x, int y);
	Button(std::string _path, int x, int y, int width, int height);
	~Button();
	void setSize(int width, int height);
	void setPosition(int x, int y);
	void draw(SpriteBacth& spriteBatch);
	bool click(glm::vec2 position);
};
