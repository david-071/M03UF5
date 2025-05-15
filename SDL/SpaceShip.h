#pragma once
#include "GameObject.h"

class Spaceship : public GameObject {
private:
	float linealVelocity = 3.f;
	float angularVelocity = 2.f;

public:
	Spaceship(SDL_Renderer* renderer);

	void Update(float dt) override;
};