#pragma once
#include "../Texture.h"
#include "../Vec2.h"
#include "../entities/Entity.h"
#include "../text/Text.h"
#include "SliderSquare.h"

/**
@brief A slider that holds values between a min and max. Uses SliderSquare
*/
class Slider {
public:

	/**
	@brief Creates slider
	@param p The position the slider starts at
	@param d The dimensions the slider has w/h
	@param t The texture used for the slider. Coloured pixel
	*/
	Slider(Texture *t, Vec2 p, Vec2 d, int v, TextImageManager *timng);

	/**
	@brief Slider deconstructor
	*/
	~Slider();

	void render(SDL_Renderer* renderer);


	void setPosition(Vec2 p);


	Vec2 getPosition();


	void changeValue(Vec2 p);

	int getValue();

	Vec2 getDimensions();

private:

	int value;

	Vec2 pos;
	Vec2 dimens;


	SliderSquare *square;

	Texture* texture;

	Vec2 half;
	Vec2 squarePos;
	Vec2 squareDimens = Vec2(7, 13);

	Text *sliderTextValue;

};