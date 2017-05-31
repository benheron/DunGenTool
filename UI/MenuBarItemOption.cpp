#include "MenuBarItemOption.h"

MenuBarItemOption::MenuBarItemOption(Texture* texture, Vec2 pos, Vec2 dimens, std::string optionString, std::string name, TextImageManager *timng) : Button(texture, pos, dimens), name(name)
{
	optionText = new Text(Vec2(pos.x + 4, pos.y + 4), 0, "Arial", 20, optionString, timng);
}

MenuBarItemOption::~MenuBarItemOption()
{

}

void MenuBarItemOption::update(float dt)
{
	
}

void MenuBarItemOption::render(SDL_Renderer* renderer)
{
	switch (bState)
	{
	case Button::buttonHover:
		texture->pushSpriteToScreen(renderer, pos, Vec2(0, 200), dimensions);
		break;
	case Button::buttonSelected:
		texture->pushSpriteToScreen(renderer, pos, Vec2(0, 400), dimensions);
		break;
	case Button::buttonIdle:
		texture->pushSpriteToScreen(renderer, pos, 0, dimensions);
		break;
	default:
		texture->pushSpriteToScreen(renderer, pos, spritePos, dimensions);
		break;
	}

	optionText->render(renderer);
}

std::string MenuBarItemOption::getName()
{
	return name;
}