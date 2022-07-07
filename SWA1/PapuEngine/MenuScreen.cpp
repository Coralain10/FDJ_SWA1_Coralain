#include "MenuScreen.h"
#include "ScreenIndices.h"
#include <iostream>


MenuScreen::MenuScreen(Window* window):_window(window)
{
	_screenIndex = SCREEN_INDEX_MENU;
}

MenuScreen::~MenuScreen()
{
}

void MenuScreen::build()
{
	background = new Background("Textures/Fondos/menu.png", _window);
}

void MenuScreen::destroy()
{
	background = nullptr;
}

void MenuScreen::onExit()
{
}

void MenuScreen::onEntry()
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

void MenuScreen::draw()
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
	spriteFont->draw(_spriteBatch, "Examen Final Bica Corazon", glm::vec2(-210, 80), glm::vec2(1), 0.0f, color);
	spriteFont->draw(_spriteBatch, "Carolain Anto Chavez", glm::vec2(-130, 40), glm::vec2(0.8), 0.0f, color);

	_spriteBatch.end();
	_spriteBatch.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();
	_window->swapBuffer();
}

void MenuScreen::update()
{
	draw();
	_camera.update();
	_inputManager.update();
	checkInput();
}

void MenuScreen::checkInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			_currentState = ScreenState::CHANGE_NEXT;
			break;
		case  SDL_KEYUP:
			_inputManager.releaseKey(event.key.keysym.sym);
			break;
		case  SDL_KEYDOWN:
			_inputManager.pressKey(event.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(event.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(event.button.button);
			break;
		case SDL_MOUSEMOTION:
			_inputManager.setMouseCoords(event.motion.x, event.motion.y);
			break;
		}

		if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
			//presione click;
			//glm::vec2 mouseCoords = _camera.convertScreenToWorl(inputManager.getMouseCoords());
			//std::cout << "x" << mouseCoords.x << " | y " << mouseCoords.y << endl;
			//COMO NO SE INDICA QUÉ OBJETO HACER CLIC,
			//HACER CLIC EN CUALQUIER LADO ENVIARÁ AL GAMEPLAY
			_currentState = ScreenState::CHANGE_NEXT;
		}
	}
}

int MenuScreen::getNextScreen() const
{
	return SCREEN_INDEX_GAMEPLAY;
}

int MenuScreen::getPreviousScreen() const
{
	return SCREEN_INDEX_NO_INDEX;
}