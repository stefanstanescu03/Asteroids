#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include <iostream>
#include <cmath>

#include <SDL.h>
#include <SDL_image.h>

#include "Bullet.hpp"

class Asteroid {
public:
	Asteroid(const char*, SDL_Renderer*, double, double, double, double);
	~Asteroid();
	void render(SDL_Renderer*);
	void move(double, int, int);

	bool hasCollided(Bullet*);

	double getX();
	double getY();

	int getHeight();
	int getWidth();

	double getSize();

private:
	SDL_Texture* asteroidTexture;

	int width;
	int height;

	double x;
	double y;
	double angle;

	double size;

	const double SPEED = 0.1;

};

#endif // !ASTEROID_HPP
