#include "Asteroid.hpp"

Asteroid::Asteroid(const char* path, SDL_Renderer* renderer,
	double x, double y, double angle, double size) {

	asteroidTexture = NULL;
	this->x = x;
	this->y = y;
	this->angle = angle;

	this->size = size;

	width = 0;
	height = 0;

	SDL_Surface* loadedSurface = IMG_Load(path);

	if (loadedSurface == NULL) {
		std::cout << "Can't load bullet image: " <<
			IMG_GetError() << '\n';
	}
	else {
		SDL_SetColorKey(loadedSurface, SDL_TRUE,
			SDL_MapRGB(loadedSurface->format, 0, 0, 0));
		asteroidTexture = SDL_CreateTextureFromSurface(
			renderer, loadedSurface);
		if (asteroidTexture == NULL) {
			std::cout << "Can't create texture: " <<
				SDL_GetError() << '\n';
		}
		else {
			width = loadedSurface->w / size;
			height = loadedSurface->h / size;
		}
		SDL_FreeSurface(loadedSurface);
	}
}

Asteroid::~Asteroid() {

	SDL_DestroyTexture(asteroidTexture);
	asteroidTexture = NULL;

	IMG_Quit();
}

void Asteroid::render(SDL_Renderer* renderer) {

	SDL_Point center = { width / 2, height / 2 };

	SDL_Rect renderQuad = { x, y, width, height };
	SDL_RenderCopyEx(renderer, asteroidTexture,
		NULL, &renderQuad, angle,
		&center, SDL_FLIP_NONE);

	//SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
	//SDL_Rect outlineRect = { x, y, width, height };
	//SDL_RenderDrawRect(renderer, &outlineRect);
	//SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
	//SDL_RenderDrawPoint(renderer, x + width / 2, y + height / 2);
	//SDL_SetRenderDrawColor(renderer, 0x20, 0x20, 0x20, 0xFF);
}

void Asteroid::move(double deltaTime, int width, int height) {

	x += SPEED * sin(angle * M_PI / 180) * deltaTime;
	y -= SPEED * cos(angle * M_PI / 180) * deltaTime;

	if (x > width) x = 0;
	if (x < 0) x = width;
	if (y > height) y = 0;
	if (y < 0) y = height;

}

bool Asteroid::hasCollided(Bullet* bullet) {

	if ((bullet->getX() - x - width / 2) * (bullet->getX() - x - width / 2) +
		(bullet->getY() - y - height / 2) * (bullet->getY() - y - height / 2) < width * width / 4) {
		return true;
	}
	return false;
}

double Asteroid::getX() {
	return x;
}

double Asteroid::getY() {
	return y;
}

double Asteroid::getSize() {
	return size;
}