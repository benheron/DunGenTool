#include "LoadState.h"
#include "../Utility.h"
#include "../Collision.h"

LoadState::LoadState(StateManager* manager, Platform *platform)
	: State(manager, platform)
{
	stateName = "LoadState";
}

LoadState::~LoadState()
{

}

bool LoadState::eventHandler()
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	Vec2 mousePos = Vec2(mouseX, mouseY);
	SDL_Event events;
	while (SDL_PollEvent(&events))
	{
		switch (events.type)
		{

		case SDL_MOUSEMOTION:



			break;
		case SDL_QUIT:
			return true;
			break;

		case SDL_MOUSEBUTTONDOWN:
			switch (events.button.button)
			{
				//while mouse is down

				//left click
			case SDL_BUTTON_LEFT:

				break;


			}
			break;
		case SDL_MOUSEBUTTONUP:
			switch (events.button.button)
			{
			case SDL_BUTTON_LEFT:
				break;
			}
			break;
		case SDL_KEYDOWN:
			switch (events.key.keysym.sym)
			{
				//pressing a key
			case SDLK_ESCAPE:
				//do same as quit
				return true;
				break;
			}
			break;
		case SDL_KEYUP:
			switch (events.key.keysym.sym)
			{
				//letting go of a key
			default:
				Utility::log(Utility::I, Utility::intToString(events.key.keysym.sym));
				break;
			}
			break;
		}
	}
	return false;
}

void LoadState::update(float dt)
{
	stateManager->changeState(new EditorState(stateManager, platform, dtmng));
}

void LoadState::render()
{

}

void LoadState::load()
{
	dtmng = new DataManager(platform, stateManager);
}

void LoadState::unload()
{

}
