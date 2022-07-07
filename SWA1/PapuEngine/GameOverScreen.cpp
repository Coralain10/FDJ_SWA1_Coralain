#include "GameOverScreen.h"
#include "ScreenIndices.h"
#include <iostream>

GameOverScreen::GameOverScreen(Window* window) :_window(window)
{
	_screenIndex = SCREEN_INDEX_GAME_OVER;
}

GameOverScreen::~GameOverScreen()
{
}

void GameOverScreen::build()
{
	//background = new Background("Textures/Fondos/gam-over.png",_window);
	background = new Background("Textures/Fondos/menu.png", _window);
}

void GameOverScreen::destroy()
{
}

void GameOverScreen::onExit()
{
}

void GameOverScreen::onEntry()
{
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
	_spriteBatch.init();
	_camera.init(_window->getScreenWidth(),
		_window->getScreenHeight());
	spriteFont = new SpriteFont("Fonts/JosefinSans-Regular.ttf", 32);
}

void GameOverScreen::draw()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_program.use();

	glActiveTexture(GL_TEXTURE0);

	GLuint pLocation =
		_program.getUniformLocation("P");

	glm::mat4 cameraMatrix = _camera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);

	_spriteBatch.begin();

	background->draw(_spriteBatch);
	char buffer[256];
	sprintf_s(buffer, "HOLA %d", 100);
	Color color;
	color.r = 255;
	color.g = 0;
	color.b = 0;
	color.a = 255;
	spriteFont->draw(_spriteBatch, buffer, glm::vec2(-100, 50), glm::vec2(1), 0.0f, color);

	sprintf_s(buffer, "HOLA 2 %d", 100);
	spriteFont->draw(_spriteBatch, buffer, glm::vec2(-200, 150), glm::vec2(1), 0.0f, color);
	_spriteBatch.end();
	_spriteBatch.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();
	_window->swapBuffer();
}

void GameOverScreen::update()
{
	draw();
	_camera.update();
	inputManager.update();
	checkInput();
}

void GameOverScreen::checkInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			inputManager.pressKey(event.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			inputManager.releaseKey(event.button.button);
			break;
		case SDL_MOUSEMOTION:
			inputManager.setMouseCoords(event.motion.x, event.motion.y);
			break;
		}

		if (inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
			//presione click;
			glm::vec2 mouseCoords = _camera.convertScreenToWorl(inputManager.getMouseCoords());
			std::cout << "x" << mouseCoords.x << " | y " << mouseCoords.y << endl;
		}
	}
}

int GameOverScreen::getNextScreen() const
{
	return SCREEN_INDEX_NO_INDEX;
}

int GameOverScreen::getPreviousScreen() const
{
	return SCREEN_INDEX_MENU;
}
