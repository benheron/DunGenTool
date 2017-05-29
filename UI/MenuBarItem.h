#pragma once
#include "../Texture.h"
#include "../Vec2.h"
#include "../entities/Entity.h"
#include "../text/Text.h"
#include "MenuBarItem.h"
#include "../entities/Button.h"

class MenuBarItem : public Button
{
public:
	MenuBarItem();
	~MenuBarItem();

protected:
	//list of menu bar item options
//	std::vector<MenuBarItemOption*>

};