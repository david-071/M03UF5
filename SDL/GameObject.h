#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Utils.h"

class GameObject {
protected:
	Vector2 position;
	Vector2 scale;
	float zRotation;

	SDL_Texture* texture;
	//SPRITESHEET CONF
	Vector2Int textureCoor; 
	Vector2Int size;
public:
	GameObject(SDL_Renderer* renderer, Vector2Int* _textureCoor, Vector2Int* _size);

	virtual void Update(float dt) = 0;
	virtual void Render(SDL_Renderer* renderer);
};
