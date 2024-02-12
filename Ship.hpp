#ifndef SHIP_HPP
#define SHIP_HPP

#include <iostream>
#include <cmath>

#include <SDL.h>
#include <SDL_image.h>

class Ship {
	
public:
	Ship();
	~Ship();
	void init(const char*, SDL_Renderer*, int, int);
	void render(SDL_Renderer*);
	void rotate(double);
	void setRotationSpeed(int);
	void move(double, int, int);
	void setAcceleration(int);

	double getX();
	double getY();
	double getAngle();

private:
	SDL_Texture* shipTexture;

	int width;
	int height;

	double x;
	double y;

	double angle;
	double rotationSpeed = 0.;

	double speedX = 0.;
	double speedY = 0.;
	double accelerationX = 0.;
	double accelerationY = 0.;

	const double ROTATION_SPEED = 0.3;
	const double MOVE_ACCELERATION = 0.0005;
	const double DRAG = 1 - 1e-4;

};

#endif // !SHIP_HPP
