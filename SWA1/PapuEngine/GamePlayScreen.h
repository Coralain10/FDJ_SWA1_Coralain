#pragma once

#include <SDL\SDL.h>
#include <ctime>
#include "IGameScreen.h"
#include "Camera2D.h"
#include "GLS_Program.h"
#include "Window.h"
#include "GLTexture.h"
#include "SpriteBacth.h"
#include "SpriteFont.h"
#include "Level.h"
#include "Player.h"
#include "Human.h"
#include "Background.h"

enum class LevelState { WON, LOST, FINISHED, PLAYING, PAUSE };

class GamePlayScreen : public IGameScreen
{
private:
	std::clock_t startTime;
	double timer; //Crear una variable Timer que se INCREMENTE cada un segundo, este valor debe ser mostrado en la caja de texto Tiempo
	unsigned int maxTime;
	//int times_checked;
	int puntaje;
	GLS_Program _program;
	Camera2D _camera;
	Window* _window = nullptr;
	SpriteBacth _spriteBatch;
	GLTexture _texture;
	InputManager _inputManager;
	SpriteFont* _spriteFont;
	vector<Level*> _levels;
	vector<Human*>  _enemys;
	Background* background;
	Player* _player;
	LevelState levelState;
	int _currenLevel;
	void updateAgents();

public:
	GamePlayScreen(Window* window);
	~GamePlayScreen();

	virtual void build() override;
	virtual void destroy() override;
	virtual void onExit() override;
	virtual void onEntry() override;
	virtual void draw()override;
	virtual void update()override;
	virtual int getNextScreen() const override;
	virtual int getPreviousScreen() const override;

	void checkInput();
	void drawUI();
	void spamEnemy();
};

