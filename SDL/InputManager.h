#pragma once
#include <SDL.h>
#include <map>
#include "Utils.h"

enum KeyState {EMPTY, DOWN, UP, HOLD};

#define IM InputManager:: Instance()

class InputManager {

private:
	//TECLADO
	std::map<Sint32, KeyState> keys;

	//RATÓN
	Vector2Int mousePos;
	bool leftClick = false;

	//CLOSE SCREEN
	bool quitGame = false;

public:
	static InputManager& Instance() {
		static InputManager manager;
		return manager;
	}

	//GETTERS
	Vector2Int GetMousePos() { return mousePos; }
	bool GetQuit() { return quitGame; }
	bool GetLeftClick() { return leftClick; }

	bool GetKey(Sint32 key, KeyState state) { return keys[key] == state; }

	void Listen();
};