#pragma once
#include "../Texture.h"
#include "../Vec2.h"
#include "../entities/Entity.h"
#include "../text/Text.h"
#include "MenuBarItem.h"

class MenuBar : public Entity {
public:
	MenuBar(Vec2 pos);
	~MenuBar();

	void addBarItemOption(std::string barOption, FUNCTION )

private:
	std::vector<MenuBarItem*> menuBarItems;

};