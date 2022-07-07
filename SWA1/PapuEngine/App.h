#pragma once
#include <algorithm>
#include "Game.h"
#include "GamePlayScreen.h"
#include "MenuScreen.h"
#include "GameOverScreen.h"

class App : public Game
{
public:
	App();
	~App();
	virtual void onInit() override;
	virtual void addScreens() override;
	virtual void onExit() override;
private:
	std::unique_ptr<GamePlayScreen> 
					_gamePlayScreen = nullptr;
	std::unique_ptr<MenuScreen>
		_menuScreen = nullptr;
	std::unique_ptr<GameOverScreen>
		_gameOverScreen = nullptr;
};

