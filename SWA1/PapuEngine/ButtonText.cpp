#include "ButtonText.h"

void ButtonText::start() {
	textColor = { 255, 255, 255, 255 };
	spriteFont = new SpriteFont("Fonts/VT323-Regular.ttf", 28);
	this->setTextPosition();
}

ButtonText::ButtonText(std::string _path, const char* text) :
	Button(_path), text(text)
{
	start();
}

ButtonText::ButtonText(std::string _path, const char* text, int x, int y) :
	Button(_path, x, y), text(text)
{
	start();
}

ButtonText::ButtonText(std::string _path, const char* text, int x, int y, int width, int height) :
	Button(_path, x, y, width, height), text(text)
{
	start();
}

ButtonText::~ButtonText()
{
}

void ButtonText::draw(SpriteBacth& spriteBatch)
{
	Button::draw(spriteBatch);
	//char buffer[256];
	//sprintf_s(buffer, this->text, 100);
	//2nd es posicion
	spriteFont->draw(spriteBatch, text, textPosition, glm::vec2(1), 0.0f, textColor);
}

void ButtonText::setTextColor(GLubyte r, GLubyte g, GLubyte b)
{
	textColor.r = r;
	textColor.g = g;
	textColor.b = b;
}

void ButtonText::setTextPosition()
{
	int textSize = strlen(text) * 28;
	this->textPosition = glm::vec2(x + width - (textSize / 2), int(y + height / 3.5));
}
void ButtonText::setSize(int width, int height)
{
	Button::setSize(width, height);
	this->setTextPosition();
}

void ButtonText::setPosition(int x, int y)
{
	Button::setPosition(x, y);
	this->setTextPosition();
}
