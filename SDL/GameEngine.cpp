#include "GameEngine.h"
#include "GameObject.h"
#include "InputManager.h"

GameEngine::GameEngine(int windowWidth, int windowHeigth) {

	InitSDL();
	InitWindowAndRenderer(windowWidth, windowHeigth);

}

void GameEngine::Update() {
	//INIT TIME
	float dt = 0.0;
	float lastTime = (float)SDL_GetPerformanceCounter() / (float)SDL_GetPerformanceFrequency();

	const int FPS = 60;
	const float frameTime = 1.0f / (float)FPS; 

	//SCENES
	std::map<std::string, Scene*> gameScene;

	gameScene["MainMenu"] = new MenuScene();
	gameScene["Gameplay"] = new GameplayScene();
	gameScene["HighScores"] = new HighScoresScene();

	Scene* currentScene = gameScene["MainMenu"];
	currentScene->Start(renderer);

	while (!IM.GetQuit()) {
		IM.Listen();

		//DELTA TIME CONTROL
		float currentTime = (float)SDL_GetPerformanceCounter() / (float)SDL_GetPerformanceFrequency();
		dt += currentTime - lastTime;

		if (dt > frameTime) {
			//LOGIC
			currentScene->Update(dt);

			//RENDER
			SDL_RenderClear(renderer);						//Limpia lo anterior
			currentScene->Render(renderer);
			SDL_RenderPresent(renderer);					//Pinta lo nuevo

			//SCENE TRANSITION
			if (currentScene->Isfinished()) {
				currentScene->Exit();
				currentScene = gameScene[currentScene->GetTargetScene()];
				currentScene->Start(renderer);
			}

			dt -= frameTime;
		}
	}
}
void GameEngine::Finish() {

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

}

void GameEngine::InitSDL() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Error al inicializar SDL: " << SDL_GetError();
	}

	if (TTF_Init() < 0) {
		std::cout << "Error al inicializar TTF : " << TTF_GetError();
	}
}
void GameEngine::InitWindowAndRenderer(int windowWidth, int windowHeigth) {

	//WINDOWS
	window = SDL_CreateWindow("Mi First Game Engine",		//Name
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,		//Position
		windowWidth, windowHeigth,							//Size
		SDL_WINDOW_SHOWN);									//Show by default

	if (window == nullptr) {
		std::cout << "Error al inicializar window: " << SDL_GetError();
	}

	//RENDERER
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr) {
		std::cout << "Error al inicializar el render: " << SDL_GetError();
	}
}