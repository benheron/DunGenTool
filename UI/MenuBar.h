#pragma once
#include "../Texture.h"
#include "../Vec2.h"
#include "../entities/Entity.h"
#include "../text/Text.h"
#include "MenuBarItem.h"
#include "../Collision.h"

class MenuBar : public Entity {
public:
	MenuBar(Texture *bgTex, Texture *buttonsTex, Vec2 pos, Vec2 dimens, TextImageManager *timng);
	~MenuBar();

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


	void addBarItemOption(std::string barOption);

	void checkHover(Vec2 mousePos);

	std::string checkSelected(Vec2 mousePos);

protected:
	std::vector<MenuBarItem*> menuBarItems;
	std::unordered_map<std::string, MenuBarItem*> menuBarItemsUM;


	Texture* bgTex;
};