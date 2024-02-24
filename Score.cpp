#include "Score.hpp"

Score::Score() {

	scoreValue = 0;
	scoreFont = NULL;
	scoreTexture = NULL;

	x = 0;
	y = 0;

	height = 0;
	width = 0;

	TTF_Init();
}

Score::~Score() {
	SDL_DestroyTexture(scoreTexture);
	TTF_CloseFont(scoreFont);
	scoreTexture = NULL;
	scoreFont = NULL;

	TTF_Quit();
}

void Score::init(const char* path, SDL_Renderer* renderer, 
	double x, double y) {

	this->x = x;
	this->y = y;

	scoreFont = TTF_OpenFont(path, 24);
	if (scoreFont == NULL) {
		std::cout << "Cannot find score font: " << TTF_GetError() << '\n';
	}

}

void Score::showScore(SDL_Renderer* renderer) {

	SDL_DestroyTexture(scoreTexture);

	SDL_Surface* surface;

	surface = TTF_RenderText_Solid(scoreFont, (std::string("score: ") + std::to_string(scoreValue)).c_str(), textColor);
	scoreTexture = SDL_CreateTextureFromSurface(renderer, surface);
	width = surface->w;
	height = surface->h;
	SDL_FreeSurface(surface);

	SDL_Rect renderQuad = { x, y, width, height };
	SDL_RenderCopy(renderer, scoreTexture, NULL, 
		&renderQuad);
}

void Score::incrementScore(int value) {
	scoreValue += value;
}

void Score::resetScore() {
	scoreValue = 0;
}