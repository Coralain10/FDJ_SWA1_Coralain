#include "GamePlayScreen.h"
#include "Game.h"

#include "ImageLoader.h"
#include <iostream>
#include "ResourceManager.h"
#include "PapuEngine.h"
#include <random>
#include "ScreenIndices.h"



GamePlayScreen::GamePlayScreen(Window* window):
	_window(window)
{
	_currenLevel = 0;
	_screenIndex = SCREEN_INDEX_GAMEPLAY;
	levelState = LevelState::PLAYING;
	times_checked = 0;
}


GamePlayScreen::~GamePlayScreen()
{
}


void GamePlayScreen::build() {
	background = new Background("Textures/Fondos/game.png", _window);
	_levels.push_back( new Level("Levels/level1.txt") );

	_player = new Player();
	_player->init(4.0f, _levels[_currenLevel]->getPlayerPosition(), &_inputManager, &_camera, "Textures/Personajes/player.png");

	_spriteBatch.init();
}
void GamePlayScreen::destroy() {
	background = nullptr;
	for (int i = _humans.size() - 1; i >= 0; i--) _humans[i] = nullptr;
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

	startTime = std::clock();
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
	for (Human* h : _humans) h->draw(_spriteBatch);
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

	timer = (std::clock() - startTime) / (double)CLOCKS_PER_SEC;
	sprintf_s(buffer, "%ds", unsigned int(timer));
	_spriteFont->draw(_spriteBatch, buffer,
		_camera.getPosition() + glm::vec2(-_window->getScreenWidth() / 2 + 24, _window->getScreenHeight() / 2 - 48),
		glm::vec2(1), 0.0f, color);

	sprintf_s(buffer, "Puntaje: %d", puntaje);
	_spriteFont->draw(_spriteBatch, buffer,
		_camera.getPosition() + glm::vec2(_window->getScreenWidth() / 2 - 192, _window->getScreenHeight() / 2 - 48),
		glm::vec2(1), 0.0f, color);
}

void GamePlayScreen::spamEnemy()
{
	std::mt19937 randomEngine(time(nullptr));
	std::uniform_int_distribution<int>randPosX(
		2, _levels[_currenLevel]->getWidth() - 3);
	std::uniform_int_distribution<int>randPosY(
		2, _levels[_currenLevel]->getHeight() - 3);

	//rango de error 0.005
	if (timer < unsigned int(timer) + 0.005 && unsigned int(timer) % 2 == 0) {
		Human* h = new Human();
		glm::vec2 pos(randPosX(randomEngine) * TILE_WIDTH,
			randPosY(randomEngine) * TILE_WIDTH);
		std::string color = "";
		switch (rand() % 3)
		{
			case 0: color = "Textures/Personajes/amarillo.png"; break;
			case 1: color = "Textures/Personajes/rojo.png"; break;
			case 2: color = "Textures/Personajes/verde.png"; break;
			default: cout << "fuera" << endl; break;
		}
		h->init(0.4f, pos, color);
		_humans.push_back(h);
		times_checked += 1;
		//sin el margen de error, en 8 segundos entró 486 veces
	}
	//entra varias veces a este if, intento reducir ello
}

void GamePlayScreen::update() {
	checkInput();
	draw();
	_camera.update();
	updateAgents();
	//_inputManager.update();// ya hace este update en el Game::run
	spamEnemy();
	_camera.setPosition(_player->getPosition());
}

void GamePlayScreen::updateAgents() {
	_player->update(_levels[_currenLevel]->getLevelData(), _humans);

	for (size_t i = 0; i < _humans.size(); i++)
	{
		if (_humans[i]->collideWithAgent(_player)) levelState = LevelState::LOST;
		_humans[i]->update(_levels[_currenLevel]->getLevelData(), _humans);
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
	}
}

int GamePlayScreen::getNextScreen() const{ 
	return SCREEN_INDEX_GAME_OVER;

};

int GamePlayScreen::getPreviousScreen() const {
	return SCREEN_INDEX_MENU;
}
