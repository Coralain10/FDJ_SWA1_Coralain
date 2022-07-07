#include "GamePlayScreen.h"
#include "Game.h"

#include "ImageLoader.h"
#include <iostream>
#include "ResourceManager.h"
#include "PapuEngine.h"
#include <random>
#include <ctime>
#include "ScreenIndices.h"



GamePlayScreen::GamePlayScreen(Window* window):
	_window(window)
{
	_currenLevel = 0;
	_screenIndex = SCREEN_INDEX_GAMEPLAY;
	levelState = LevelState::PLAYING;
}


GamePlayScreen::~GamePlayScreen()
{
}


void GamePlayScreen::build() {
	background = new Background("Textures/Fondos/game.png", _window);
	_levels.push_back( new Level("Levels/level1.txt") );

	_player = new Player();
	_player->init(2.0f, _levels[_currenLevel]->getPlayerPosition(), &_inputManager, &_camera, "Textures/Personajes/player.png");
	_humans.push_back(_player);

	_spriteBatch.init();

	std::mt19937 randomEngine(time(nullptr));
	std::uniform_int_distribution<int>randPosX(
		2, _levels[_currenLevel]->getWidth() - 3);
	std::uniform_int_distribution<int>randPosY(
		2, _levels[_currenLevel]->getHeight() - 3);

	for (int i = 0; i < _levels[_currenLevel]->getNumHumans(); i++)
	{
		_humans.push_back(new Human());
		glm::vec2 pos(randPosX(randomEngine) * TILE_WIDTH,
			randPosY(randomEngine) * TILE_WIDTH);
		_humans.back()->init(0.4f, pos, "Textures/Personajes/amarillo.png");
		_humans.back()->setUvRect(0.0f, 0.5f, 1.0f, 0.25f);
	}

	const std::vector<glm::vec2>& zombiePosition =
		_levels[_currenLevel]->getZombiesPosition();

	for (size_t i = 0; i < zombiePosition.size(); i++)
	{
		_zombies.push_back(new Zombie());
		_zombies.back()->init(0.4f, zombiePosition[i], "Textures/Personajes/verde.png");
		_zombies.back()->setUvRect(0.0f, 0.75f, 1.0f, 0.25f);
	}
}
void GamePlayScreen::destroy() {
}
void GamePlayScreen::onExit() {
}
void GamePlayScreen::onEntry() {
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();

	_camera.init(_window->getScreenWidth(), _window->getScreenHeight());
	_window->setGLColor(0.195f, 0.273, 0.215); //50, 70, 55  1.0f, 1.0f, 0.0f
	_spriteFont = new SpriteFont("Fonts/JosefinSans-Regular.ttf", 24);
}

void GamePlayScreen::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_program.use();

	glActiveTexture(GL_TEXTURE0);

	GLuint pLocation = _program.getUniformLocation("P");

	glm::mat4 cameraMatrix = _camera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);

	_spriteBatch.begin();

	background->draw();
	_levels[_currenLevel]->draw();
	_player->draw(_spriteBatch);
	//for (Human* h : _humans) h->draw(_spriteBatch);
	drawUI();

	_spriteBatch.end();
	_spriteBatch.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();
	_window->swapBuffer();
}

void GamePlayScreen::drawUI() {
	background->setPosition(_camera.getPosition() + glm::vec2(-_window->getScreenWidth() / 2 -4, -_window->getScreenHeight() / 2 -4));
	Color color{ 255, 252, 187, 255 };
	char buffer[256];

	//auto elapsed = (std::chrono::high_resolution_clock::now() - startTime).count();
	//timer = unsigned long((elapsed / 10000000) / 30); //frequency = 30
	//sprintf_s(buffer, "Tiempo: %d", timer);
	//_spriteFont->draw(_spriteBatch, buffer,
	//	_camera.getPosition() + glm::vec2(-_window->getScreenWidth() / 2 + 24, _window->getScreenHeight() / 2 - 48),
	//	glm::vec2(1), 0.0f, color);

	sprintf_s(buffer, "Puntaje: %d", puntaje);
	_spriteFont->draw(_spriteBatch, buffer,
		_camera.getPosition() + glm::vec2(_window->getScreenWidth() / 2 - 192, _window->getScreenHeight() / 2 - 48),
		glm::vec2(1), 0.0f, color);
}

void GamePlayScreen::drawAgents() {
	_levels[_currenLevel]->draw();

	if (!_player->hasKey()) _key->draw(_spriteBatch);
	_door->draw(_spriteBatch);//if (!_door->isOpen()) 

	for (size_t i = 0; i < _humans.size(); i++)
	{
		_humans[i]->draw(_spriteBatch);

	}

	for (size_t i = 0; i < _zombies.size(); i++)
	{
		_zombies[i]->draw(_spriteBatch);
	}
}

void GamePlayScreen::update() {
	checkInput();
	draw();
	_camera.update();
	updateAgents();
	_inputManager.update();
	if (levelState == LevelState::PLAYING) _camera.setPosition(_player->getPosition());
	else _camera.setPosition(glm::vec2(0.0f, 0.0f));
}

void GamePlayScreen::updateAgents() {

	for (size_t i = 0; i < _humans.size(); i++)
	{

		_humans[i]->update(_levels[_currenLevel]->getLevelData(),
			_humans, _zombies);
	}

	for (size_t i = 0; i < _zombies.size(); i++)
	{
		_zombies[i]->update(_levels[_currenLevel]->getLevelData(),
			_humans, _zombies);

		if (_zombies[i]->collideWithAgent(_player)) levelState = LevelState::LOST;

		for (size_t j = 1; j < _humans.size(); j++)
		{
			if (_zombies[i]->collideWithAgent(_humans[j])) {
				_zombies.push_back(new Zombie);
				_zombies.back()->init(0.4f, _humans[j]->getPosition(), "Textures/Personajes/verde.png");
				_zombies.back()->setUvRect(0.0f, 0.75f, 1.0f, 0.25f);

				delete _humans[j];
				_humans[j] = _humans.back();
				_humans.pop_back();
			}
		}
	}
}

void GamePlayScreen::checkInput() {
	SDL_Event event;
	const float CAMERA_SPEED = 20.0f;
	const float SCALE_SPEED = 0.1f;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			_currentState = ScreenState::EXIT_APPLICATION;
			break;
		case SDL_MOUSEMOTION:
			_inputManager.setMouseCoords(event.motion.x, event.motion.y);
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
		}

		//if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
		//	//presione click;
		//	glm::vec2 mouseCoords = _camera.convertScreenToWorl(_inputManager.getMouseCoords());
		//	if (backButton->click(mouseCoords)) {
		//		_currentState = ScreenState::CHANGE_NEXT;
		//	}
		//}
	}
}

int GamePlayScreen::getNextScreen() const{ 
	return SCREEN_INDEX_GAME_OVER;

};

int GamePlayScreen::getPreviousScreen() const {
	return SCREEN_INDEX_MENU;
}
