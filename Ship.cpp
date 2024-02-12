#include "Ship.hpp"

Ship::Ship() {

	shipTexture = NULL;
	width = 0;
	height = 0;
	x = 0.;
	y = 0.;
	angle = 0.;
}

Ship::~Ship() {

	SDL_DestroyTexture(shipTexture);
	shipTexture = NULL;

	IMG_Quit();
}

void Ship::init(const char* path, SDL_Renderer* renderer, int x, int y) {

	this->x = x;
	this->y = y;

	shipTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path);

	if (loadedSurface == NULL) {
		std::cout << "Can't load player image: " << 
			IMG_GetError() << '\n';
	}
	else {
		SDL_SetColorKey(loadedSurface, SDL_TRUE, 
			SDL_MapRGB(loadedSurface->format, 0, 0, 0));
		shipTexture = SDL_CreateTextureFromSurface(
			renderer, loadedSurface);
		if (shipTexture == NULL) {
			std::cout << "Can't create texture: " <<
				SDL_GetError() << '\n';
		}
		else {
			width = loadedSurface->w;
			height = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
}

void Ship::render(SDL_Renderer* renderer) {

	SDL_Point center = { width / 2, height / 2 };

	SDL_Rect renderQuad = { x, y, width, height };
	SDL_RenderCopyEx(renderer, shipTexture,
		NULL, &renderQuad, angle, 
		&center, SDL_FLIP_NONE);
}

void Ship::rotate(double deltaTime) {
	angle += rotationSpeed * deltaTime;
	if (angle >= 360. || angle <= -360.) {
		angle = 0.;
	}
}

void Ship::setRotationSpeed(int direction) {
	rotationSpeed += ROTATION_SPEED * direction;
}

void Ship::move(double deltaTime, int width, int height) {

	x += speedX * deltaTime;
	y -= speedY * deltaTime;

	speedX += accelerationX * deltaTime;
	speedY -= accelerationY * deltaTime;

	if (abs(speedX) > 1e-2) speedX *= DRAG;
	if (abs(speedY) > 1e-2) speedY *= DRAG;

	if (x > width) x = 0;
	if (x < 0) x = width;
	if (y > height) y = 0;
	if (y < 0) y = height;
}

void Ship::setAcceleration(int direction) {

	if (direction > 0) {
		accelerationX += MOVE_ACCELERATION * sin(angle * M_PI / 180);
		accelerationY -= MOVE_ACCELERATION * cos(angle * M_PI / 180);
	} 
	else {
		accelerationX = 0.;
		accelerationY = 0.;
	}
}

double Ship::getX() {
	return x;
}

double Ship::getY() {
	return y;
}

double Ship::getAngle() {
	return angle;
}