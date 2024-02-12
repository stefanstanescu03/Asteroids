#ifndef BULLET_H
#define BULLET_H

#include <iostream>

#include <cmath>
#include <SDL.h>
#include <SDL_image.h>

class Bullet {
public:
	Bullet(const char*, SDL_Renderer*, double, double, double);
	~Bullet();
	void render(SDL_Renderer*);
	void move(double);

	double getX();
	double getY();

private:
	SDL_Texture* bulletTexture;

	int width;
	int height;

	double x;
	double y;

	double angle;

	const double SPEED = 1;


};

#endif // !BULLET_H
