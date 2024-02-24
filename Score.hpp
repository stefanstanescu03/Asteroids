#ifndef SCORE_HPP
#define SCORE_HPP

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class Score{
public:
	Score();
	~Score();
	
	void init(const char* , SDL_Renderer* , double, double);

	void showScore(SDL_Renderer*);
	void incrementScore(int value);
	void resetScore();

private:
	int scoreValue;
	TTF_Font* scoreFont;
	SDL_Texture* scoreTexture;
	SDL_Color textColor = { 255, 255, 255, 0 };

	double x, y;
	int width, height;
};

#endif // !SCORE_HPP
