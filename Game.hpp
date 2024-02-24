#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <string>

#include "Ship.hpp"
#include "Bullet.hpp"
#include "Asteroid.hpp"
#include "Score.hpp"

class Game {
public:

	const int SCREEN_WIDTH = 1024;
	const int SCREEN_HEIGHT = 768;

	Game();
	~Game();
	void run();

private:

	SDL_Window* window;
	SDL_Surface* screenSurface;
	SDL_Renderer* renderer;

	Ship playerShip;
	Score score;
	
	std::vector<Bullet*> bullets;
	std::vector<Asteroid*> asteroids;

};

#endif // !GAME_HPP
