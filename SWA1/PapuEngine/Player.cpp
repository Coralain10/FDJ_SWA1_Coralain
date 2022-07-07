#include "Player.h"
#include <SDL\SDL.h>
#include <iostream>


void Player::init(float speed, glm::vec2 position, InputManager* inputManager, Camera2D* camera, std::string texturePath) {
	_speed = speed;
	_walk = _speed;
	_sprint = _speed * 1.5;
	_position = position;
	_camera = camera;
	_inputManager = inputManager;
	_texturePath = texturePath;
	_hasKey = false;
	//color.set(0, 0, 185, 255);
	color.set(255, 255, 255, 255);
}
void Player::update(const std::vector<std::string>& levelData,
	std::vector<Human*>& humans) {
	if (_inputManager->isKeyDown(SDLK_w)) {
		_position.y += _speed;
	}
	if (_inputManager->isKeyDown(SDLK_s)) {
		_position.y -= _speed;
	}
	if (_inputManager->isKeyDown(SDLK_a)) {
		_position.x -= _speed;
	}
	if (_inputManager->isKeyDown(SDLK_d)) {
		_position.x += _speed;
	}
	if (_inputManager->isKeyDown(SDLK_LSHIFT)) {
		_speed = _sprint;
	}
	else{
		_speed = _walk;
	}
	collideWithLevel(levelData);
}


Player::Player():_currentGun(-1)
{
}


Player::~Player()
{
}
