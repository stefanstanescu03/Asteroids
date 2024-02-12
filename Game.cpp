#include "Game.hpp"

Game::Game() {

	window = NULL;
	screenSurface = NULL;
	renderer = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Could not initialize SDL: " << 
			SDL_GetError() << '\n';
	}
	else {
		window = SDL_CreateWindow("Asteroids",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (window == NULL) {
			std::cout << "Window could not be created: " <<
				SDL_GetError() << '\n';
		}
		else {

			renderer = SDL_CreateRenderer(
				window, -1, SDL_RENDERER_ACCELERATED);

			if (renderer == NULL) {
				std::cout << "Renderer could not be created: " <<
					SDL_GetError() << '\n';
			}
			else {
				SDL_SetRenderDrawColor(renderer, 
					0x20, 0x20, 0x20, 0xFF);
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					std::cout << "SDL_image could not initialize: " << 
						IMG_GetError() << '\n';
				}
				else {
					playerShip.init("ship.png", renderer, 
						SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
				}
			}
		}
	}
}

Game::~Game() {

	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
}

void Game::run() {

	SDL_Event e;
	bool shouldQuit = false;

	Uint64 now = SDL_GetPerformanceCounter();
	Uint64 last = 0;
	double deltaTime = 0.f;

	while (!shouldQuit) {

		last = now;
		now = SDL_GetPerformanceCounter();

		deltaTime = (double)((now - last) * 1000 / (double)SDL_GetPerformanceFrequency());

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				shouldQuit = true;
			}
			else if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
				switch (e.key.keysym.sym) {
				case SDLK_LEFT:
					playerShip.setRotationSpeed(-1);
					break;
				case SDLK_RIGHT:
					playerShip.setRotationSpeed(1);
					break;
				case SDLK_UP:
					playerShip.setAcceleration(1);
					break;
				case SDLK_SPACE:
					bullets.push_back(new Bullet("bullet.png",
						renderer, playerShip.getX(), playerShip.getY(), playerShip.getAngle()));
					break;
				default:
					break;
				}
			}
			else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
				switch (e.key.keysym.sym) {
				case SDLK_LEFT:
					playerShip.setRotationSpeed(1);
					break;
				case SDLK_RIGHT:
					playerShip.setRotationSpeed(-1);
					break;
				case SDLK_UP:
					playerShip.setAcceleration(-1);
					break;
				default:
					break;
				}
			}
		}

		SDL_RenderClear(renderer);
		playerShip.render(renderer);

		for (unsigned int i = 0; i < bullets.size(); i++) {
			bullets[i]->render(renderer);
			bullets[i]->move(deltaTime);

			if (bullets[i]->getX() > SCREEN_WIDTH ||
				bullets[i]->getX() < 0 || 
				bullets[i]->getY() > SCREEN_HEIGHT ||
				bullets[i]->getY() < 0) {

				bullets.erase(bullets.begin() + i);
				i--;
			}
		}

		SDL_RenderPresent(renderer);
		playerShip.rotate(deltaTime);
		playerShip.move(deltaTime, SCREEN_WIDTH, SCREEN_HEIGHT);

	}
}