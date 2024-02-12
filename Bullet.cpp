#include "Bullet.hpp"

Bullet::Bullet(const char* path, SDL_Renderer* renderer, 
	double x, double y, double angle) {

	bulletTexture = NULL;
	this->x = x;
	this->y = y;
	this->angle = angle;

	width = 0;
	height = 0;

	bulletTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path);

	if (loadedSurface == NULL) {
		std::cout << "Can't load bullet image: " <<
			IMG_GetError() << '\n';
	}
	else {
		SDL_SetColorKey(loadedSurface, SDL_TRUE,
			SDL_MapRGB(loadedSurface->format, 0, 0, 0));
		bulletTexture = SDL_CreateTextureFromSurface(
			renderer, loadedSurface);
		if (bulletTexture == NULL) {
			std::cout << "Can't create texture: " <<
				SDL_GetError() << '\n';
		}
		else {
			width = loadedSurface->w / 2;
			height = loadedSurface->h / 2;
		}
		SDL_FreeSurface(loadedSurface);
	}
}

Bullet::~Bullet() {

	SDL_DestroyTexture(bulletTexture);
	bulletTexture = NULL;

	IMG_Quit();
}

void Bullet::render(SDL_Renderer* renderer) {

	SDL_Point center = { width / 2, height / 2 };

	SDL_Rect renderQuad = { x, y, width, height };
	SDL_RenderCopyEx(renderer, bulletTexture,
		NULL, &renderQuad, 0,
		&center, SDL_FLIP_NONE);
}

void Bullet::move(double deltaTime) {

	x += SPEED * sin(angle * M_PI / 180) * deltaTime;
	y -= SPEED * cos(angle * M_PI / 180) * deltaTime;
}

double Bullet::getX() {
	return x;
}

double Bullet::getY() {
	return y;
}