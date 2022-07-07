#pragma once
#include "Human.h"
#include "Key.h"
#include "Portal.h"
#include "InputManager.h"
#include <vector>
#include "Camera2D.h"

class Player: public Human
{
private:
	InputManager* _inputManager;
	int _currentGun;
	float _sprint;
	float _walk;
	bool _hasKey;
	Camera2D* _camera;
public:
	Player();
	~Player();

	bool hasKey() const { return _hasKey; }
	void getKey() { _hasKey = true; }

	bool collideWithKey(Key* key);
	bool collideWithPortal(Portal* portal);

	void init(float speed, glm::vec2 position, InputManager* inputManager, Camera2D* camera, std::string texturePath);
	void update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies );
};

