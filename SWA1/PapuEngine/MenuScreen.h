#pragma once
#include "IGameScreen.h"
#include "GLS_Program.h"
#include "Window.h"
#include "SpriteBacth.h"
#include "Background.h"
#include "SpriteFont.h"
#include "Camera2D.h"
#include "InputManager.h"

class MenuScreen : public IGameScreen
{
protected:
	int _screenIndex = 0;
private:
	GLS_Program _program;
	Window* _window = nullptr;
	SpriteBacth _spriteBatch;
	Background* background;
	Camera2D _camera;
	InputManager _inputManager;
	void checkInput(); 
	SpriteFont* spriteFont;
public:
	MenuScreen(Window* window);
	~MenuScreen();
	virtual void build() override;
	virtual void destroy() override;
	virtual void onExit() override;
	virtual void onEntry() override;
	virtual void draw()override;
	virtual void update()override;
	virtual int getNextScreen() const override;
	virtual int getPreviousScreen() const override;

};