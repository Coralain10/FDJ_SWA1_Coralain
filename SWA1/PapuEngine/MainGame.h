#pragma once
#include <SDL\SDL.h>
#include <GL\glew.h>
#include "GLS_Program.h"
#include "Window.h"
#include "Camera2D.h"
#include <vector>
#include "SpriteBacth.h"
#include "InputManager.h"
#include "Level.h"
#include "Player.h"
#include "Human.h"
#include "Zombie.h"

enum class GameState
{
	PLAY, EXIT
};


class MainGame
{
private:
	int _witdh;
	int _height;
	float _time;
	Window _window;
	void init();
	void procesInput();
	GLS_Program _program;
	Camera2D _camera;
	SpriteBacth _spriteBacth;
	InputManager _inputManager;
	vector<Level*> _levels;
	vector<Human*>  _humans;
	vector<Zombie*> _zombies;
	Player* _player;
	int _currenLevel;
	void initLevel();
	void updateAgents();
	
public:
	MainGame();
	~MainGame();
	GameState _gameState;
	void initShaders();
	void run();
	void draw();
	void update();
};

