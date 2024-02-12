#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

#include "Ship.hpp"
#include "Bullet.hpp"

class Game {
public:

	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

	Game();
	~Game();
	void run();

private:

	SDL_Window* window;
	SDL_Surface* screenSurface;
	SDL_Renderer* renderer;

	Ship playerShip;
	
	std::vector<Bullet*> bullets;
};

#endif // !GAME_HPP
