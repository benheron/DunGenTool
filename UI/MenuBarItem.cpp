#include "MenuBarItem.h"

MenuBarItem::MenuBarItem(Texture *baritemTex, Vec2 pos, Vec2 dimens, std::string itemName, TextImageManager *timng) : Button(pos, dimens), itemName(itemName), baritemTex(baritemTex)
{
	itemText = new Text(Vec2(pos.x+4, pos.y +4), 0, "Arial", 20, itemName, timng);

	Vec2 itemDimens = Vec2(266, 32);

	/*MenuBarItemOption *m = new MenuBarItemOption(baritemTex, Vec2(pos.x, pos.y+ 30), itemDimens, "Import Room Template", "IRT",  timng);
	menubarItemOptions.push_back(m);*/
	MenuBarItemOption *m2 = new MenuBarItemOption(baritemTex, Vec2(pos.x, pos.y + 32), itemDimens, "Import Full Map", "IFM", timng);
	menubarItemOptions.push_back(m2);
	MenuBarItemOption *m3 = new MenuBarItemOption(baritemTex, Vec2(pos.x, pos.y + 64), itemDimens, "Save Current Room As Template", "ETRT", timng);
	menubarItemOptions.push_back(m3);
	MenuBarItemOption *m4 = new MenuBarItemOption(baritemTex, Vec2(pos.x, pos.y + 96), itemDimens, "Export Map", "EM", timng);
	menubarItemOptions.push_back(m4);

}

MenuBarItem::~MenuBarItem()
{

}

void MenuBarItem::update(float dt)
{
	switch (bState)
	{
	case Button::buttonHover:
		
		break;
	case Button::buttonSelected:
		
		
		break;
	case Button::buttonIdle:
		
		break;
	default:
		
		break;
	}
}

void MenuBarItem::render(SDL_Renderer* renderer)
{
	switch (bState)
	{
	case Button::buttonHover:
		baritemTex->pushSpriteToScreen(renderer, pos, Vec2(0, 200), dimensions);
		break;
	case Button::buttonSelected:
		baritemTex->pushSpriteToScreen(renderer, pos, Vec2(0, 400), dimensions);

		for (int i = 0; i < menubarItemOptions.size(); i++)
		{
			menubarItemOptions[i]->render(renderer);
		}
		break;
	case Button::buttonIdle:
		baritemTex->pushSpriteToScreen(renderer, pos, 0, dimensions);
		break;
	default:
		baritemTex->pushSpriteToScreen(renderer, pos, spritePos, dimensions);
		break;
	}

	itemText->render(renderer);

}

void MenuBarItem::checkHoveredItem(Vec2 mousePos)
{
	switch (bState)
	{
	case Button::buttonHover:

		break;
	case Button::buttonSelected:
		for (int i = 0; i < menubarItemOptions.size(); i++)
		{
			if (Collision::pointBoxCollision(mousePos, menubarItemOptions[i]->getPosition(), menubarItemOptions[i]->getDimensions()))
			{
				if (!menubarItemOptions[i]->getSelected())
				{
					menubarItemOptions[i]->setHover(true);
				}
			}
			else {
				menubarItemOptions[i]->setIdle();
			}
		}

		break;
	case Button::buttonIdle:

		break;
	default:

		break;
	}
}


std::string MenuBarItem::checkSelectedItem(Vec2 mousePos)
{

	std::string returnVal = "None";
	switch (bState)
	{
	case Button::buttonHover:

		break;
	case Button::buttonSelected:
		for (int i = 0; i < menubarItemOptions.size(); i++)
		{
			if (Collision::pointBoxCollision(mousePos, menubarItemOptions[i]->getPosition(), menubarItemOptions[i]->getDimensions()))
			{
				if (!menubarItemOptions[i]->getSelected())
				{
					menubarItemOptions[i]->setSelected(true);
					returnVal = menubarItemOptions[i]->getName();
					//menubarItemOptions[i]->setIdle();
				}
				else {
					//menubarItemOptions[i]->setSelected(true);
				}
			}
			else {
				//menubarItemOptions[i]->setIdle();
			}
		}

		break;
	case Button::buttonIdle:

		break;
	default:

		break;
	}
	return returnVal;
}