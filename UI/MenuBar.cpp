#include "MenuBar.h"

MenuBar::MenuBar(Texture *bgTex, Texture *buttonsTex, Vec2 pos, Vec2 dimens, TextImageManager *timng) : Entity(pos, dimens), bgTex(bgTex)
{

	Vec2 itemDimens = Vec2(36, 32);
	MenuBarItem* barFile = new MenuBarItem(buttonsTex, Vec2(pos.x, pos.y), itemDimens, "File", timng);

	menuBarItems.push_back(barFile);
	menuBarItemsUM["File"] = barFile;

	//MenuBarItem* 



}

MenuBar::~MenuBar()
{

}

void MenuBar::update(float dt)
{
	for (int i = 0; i < menuBarItems.size(); i++)
	{
		if (menuBarItems[i]->getSelected())
		{

		}
	}
}

void MenuBar::render(SDL_Renderer* renderer)
{
	bgTex->pushSpriteToScreen(renderer, pos, dimensions);
	for (int i = 0; i < menuBarItems.size(); i++)
	{
		menuBarItems[i]->render(renderer);
	}
}

void MenuBar::checkHover(Vec2 mousePos)
{
	//buttons
	for (int i = 0; i < menuBarItems.size(); i++)
	{
		if (Collision::pointBoxCollision(mousePos, menuBarItems[i]->getPosition(), menuBarItems[i]->getDimensions()))
		{
			if (!menuBarItems[i]->getSelected())
			{
				menuBarItems[i]->setHover(true);
			}
		}
		else {

			if (!menuBarItems[i]->getSelected())
			{
				menuBarItems[i]->setIdle();
			}
		}
		menuBarItems[i]->checkHoveredItem(mousePos);
	}
}

std::string MenuBar::checkSelected(Vec2 mousePos)
{
	std::string returnVal = "None";
	for (int i = 0; i < menuBarItems.size(); i++)
	{
		if (menuBarItems[i]->getSelected())
		{
			std::string option = menuBarItems[i]->checkSelectedItem(mousePos);
			if (option != "None")
			{
				returnVal = option;
				menuBarItems[i]->setIdle();
			}
			else {
				menuBarItems[i]->setIdle();
			}
		}

		if (Collision::pointBoxCollision(mousePos, menuBarItems[i]->getPosition(), menuBarItems[i]->getDimensions()))
		{
			if (!menuBarItems[i]->getSelected())
			{
				menuBarItems[i]->setSelected(true);
				//returnVal = 1;
			}
		}
		else {
			//menuBarItems[i]->setIdle();
		}
		
	}

	return returnVal;
}



void MenuBar::addBarItemOption(std::string barOption)
{
	//menuBarItemsUM[barOption]->setSelectedEvent()
}