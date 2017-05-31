#pragma once
#include "../Texture.h"
#include "../Vec2.h"
#include "../entities/Entity.h"
#include "../text/Text.h"
#include "MenuBarItem.h"
#include "../entities/Button.h"
#include "MenuBarItemOption.h"

#include "../Collision.h"

class MenuBarItem : public Button
{
public:
	MenuBarItem(Texture *baritemTex, Vec2 pos, Vec2 dimens, std::string itemName, TextImageManager * timng);
	~MenuBarItem();

	/**
	@brief Update the Creature.
	@param dt The delta time.
	*/
	virtual void update(float dt);


	/**
	@brief Render the Creature.
	@param renderer A pointer to the renderer.
	*/
	virtual void render(SDL_Renderer* renderer);


	std::string checkSelectedItem(Vec2 mousePos);

	void checkHoveredItem(Vec2 mousePos);


protected:
	std::string itemName;
	Texture *baritemTex;
	//list of menu bar item options
	std::vector<MenuBarItemOption*> menubarItemOptions;

	bool showOptions = false;

	Text* itemText;
};