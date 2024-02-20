#include "Game.hpp"

std::string getRandom() {
	return std::to_string(rand() % 4 + 1);
}

double getRandomAngle() {
	return rand() % 360;
}

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

	asteroids.push_back(new Asteroid(("asteroid" + getRandom() + ".png").c_str(), renderer, 500, 500, 30, 1));
	asteroids.push_back(new Asteroid(("asteroid" + getRandom() + ".png").c_str(), renderer, 200, 321, 90, 1));
	asteroids.push_back(new Asteroid(("asteroid" + getRandom() + ".png").c_str(), renderer, 450, 200, 270, 1));
	asteroids.push_back(new Asteroid(("asteroid" + getRandom() + ".png").c_str(), renderer, 100, 101, 180, 1));

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

		for (unsigned int i = 0; i < asteroids.size(); i++) {
			asteroids[i]->render(renderer);
			asteroids[i]->move(deltaTime, SCREEN_WIDTH, SCREEN_HEIGHT);

			bool wasDeleted = false;

			for (unsigned int j = 0; j < bullets.size() && !wasDeleted; j++) {
				if (asteroids[i]->hasCollided(bullets[j])) {

					if (asteroids[i]->getSize() <= 2) {
						for (unsigned int k = 0; k < 3; k++) {
							asteroids.push_back(new Asteroid(("asteroid" + getRandom() + ".png").c_str(),
								renderer, asteroids[i]->getX(), asteroids[i]->getY(), getRandomAngle(), asteroids[i]->getSize() * 2));
						}
					}
					asteroids.erase(asteroids.begin() + i);
					i--;
					bullets.erase(bullets.begin() + j);
					j--;
					wasDeleted = true;
				}
			}
		}

		if (asteroids.size() == 0) {
			asteroids.push_back(new Asteroid(("asteroid" + getRandom() + ".png").c_str(), renderer, 500, 500, 30, 1));
			asteroids.push_back(new Asteroid(("asteroid" + getRandom() + ".png").c_str(), renderer, 200, 321, 90, 1));
			asteroids.push_back(new Asteroid(("asteroid" + getRandom() + ".png").c_str(), renderer, 450, 200, 270, 1));
			asteroids.push_back(new Asteroid(("asteroid" + getRandom() + ".png").c_str(), renderer, 100, 101, 180, 1));
		}

		SDL_RenderPresent(renderer);
		playerShip.rotate(deltaTime);
		playerShip.move(deltaTime, SCREEN_WIDTH, SCREEN_HEIGHT);

	}
}