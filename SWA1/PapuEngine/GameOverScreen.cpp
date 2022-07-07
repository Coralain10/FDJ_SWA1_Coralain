#include "GameOverScreen.h"
#include "ScreenIndices.h"
#include "Error.h"
#include <fstream>
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

	//LEER ARCHIVO CON EL PUNTAJE
	std::ifstream file;
	file.open("Levels/levelScore.txt");
	if (file.fail()) {
		fatalError("failed to opem levelScore");
	}
	file >> puntaje;
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

	background->draw();

	Color color{ 255, 252, 187, 255 };
	char buffer[256];
	sprintf_s(buffer, "Obtuviste %d", puntaje);
	spriteFont->draw(_spriteBatch, buffer, glm::vec2(-100, 50), glm::vec2(1), 0.0f, color);

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
			//glm::vec2 mouseCoords = _camera.convertScreenToWorl(inputManager.getMouseCoords());
			setlocale(LC_CTYPE, "Spanish");
			std::cout << "Para el otro año será :D" << endl;
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
