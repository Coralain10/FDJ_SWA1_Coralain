#pragma once

#include <SDL\SDL.h>
#include "IGameScreen.h"
#include "Camera2D.h"
#include "GLS_Program.h"
#include "Window.h"
#include "GLTexture.h"
#include "Portal.h"
#include "SpriteBacth.h"
#include "SpriteFont.h"
#include "Level.h"
#include "Zombie.h"
#include "Player.h"
#include "Human.h"
#include "Background.h"
#include "Key.h"
#include "Door.h"
#include "Button.h"

enum class LevelState { WON, LOST, FINISHED, PLAYING, PAUSE };

class GamePlayScreen : public IGameScreen
{
private:
	//std::chrono::steady_clock::time_point startTime;
	unsigned long timer; //std::chrono::duration<double> timer;
	int puntaje;
	GLS_Program _program;
	Camera2D _camera;
	Window* _window = nullptr;
	SpriteBacth _spriteBatch;
	GLTexture _texture;
	InputManager _inputManager;
	SpriteFont* _spriteFont;
	vector<Level*> _levels;
	vector<Human*>  _humans;
	vector<Zombie*> _zombies;
	Background* background;
	Button* backButton;
	Player* _player;
	Key* _key;
	Door* _door;
	Portal* _portal;
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
	void drawAgents();
	void drawBackground();
	void drawUI();
};

