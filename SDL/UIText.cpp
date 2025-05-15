#include "UIText.h"

UIText::UIText(SDL_Renderer* rend, Vector2 pos, Vector2 initScale, float initZRotation, std::string textToPrint, int initFontSize) {
	position = pos;
	scale = initScale;
	zRotation = initZRotation;
	text = textToPrint;
	fontSize = initFontSize;

	fontPath = "resources/Hyperspace.ttf";
	width = 0;
	height = 0;

	GenerateTexture(rend);
}

void UIText::GenerateTexture(SDL_Renderer* rend) {
	//Open font file
	TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
	if (font == nullptr) {
		std::cout << "Error al cargar la fuente: " << TTF_GetError() << std::endl;
		return;
	}

	SDL_Color textColor{ 255, 0, 255, 255 };

	SDL_Surface* surf = TTF_RenderText_Solid(font, text.c_str(), textColor);
	if (surf == nullptr) {
		std::cout << "Error al cargar la surface: " << TTF_GetError() << std::endl;
		TTF_CloseFont(font);
		return;
	}

	texture = SDL_CreateTextureFromSurface(rend, surf);
	if (texture == nullptr) {
		std::cout << "Error al cargar la textura: " << SDL_GetError() << std::endl;
		TTF_CloseFont(font);
		return;
	}

	width = surf->w;
	height = surf->h;
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
}

void UIText::Update(float dt) {
}

void UIText::Render(SDL_Renderer* rend) {
	if (texture == nullptr) return;

	SDL_Rect dest;
	dest.w = width * scale.x;
	dest.h = height * scale.y;
	dest.x = position.x - width / 2.f;
	dest.y = position.y - width / 2.f;

	SDL_RenderCopyEx(rend, texture, NULL, &dest, zRotation, NULL, SDL_FLIP_NONE);
}

void UIText::SetText(std::string newText, SDL_Renderer* rend) {
	if (texture) {
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}

	text = newText;
	GenerateTexture(rend);
}