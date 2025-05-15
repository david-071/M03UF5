#include "GameObject.h"
GameObject::GameObject(SDL_Renderer* renderer, Vector2Int* _textureCoor, Vector2Int* _size) {

	position = Vector2(50, 50);
	zRotation = 0.f;
	scale = Vector2(1.f, 1.f);

	textureCoor = *_textureCoor;
	size = *_size;

	//LOAD TEXTURE
	SDL_Surface* surf = IMG_Load("resources/asteroids_spritesheet.png");
	if (surf == nullptr) {
		std::cout << "Error al cargar la surface: " << SDL_GetError();
	}

	texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == nullptr) {
		std::cout << "Error al cargar la textura: " << SDL_GetError();
	}

	SDL_FreeSurface(surf);
}

void GameObject::Render(SDL_Renderer* renderer) {

	SDL_Rect source{ textureCoor.x, textureCoor.y,			//Texture Position
					size.x, size.y };						//Texture Size

	SDL_Rect destination{ position.x, position.y,					//Window Position
					source.w*scale.x, source.h*scale.y };			//Window Size

	//SDL_RenderCopy(renderer, texture, &source, &destination);
	SDL_RenderCopyEx(renderer, texture, &source, &destination, zRotation, NULL, SDL_FLIP_NONE);		//NULL es el centro 
}