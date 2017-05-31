#include "../Vec2.h"
#include "../entities/Entity.h"
#include "../text/Text.h"
#include "../entities/Button.h"


#include "../Collision.h"


class MenuBarItemOption : public Button
{
public:
	MenuBarItemOption(Texture* texture, Vec2 pos, Vec2 dimens, std::string optionString, std::string name, TextImageManager *timng);
	~MenuBarItemOption();

	/**
	@brief Update the MenuBarItemOption.
	@param dt The delta time.
	*/
	virtual void update(float dt);


	/**
	@brief Render the MenuBarItemOption.
	@param renderer A pointer to the renderer.
	*/
	virtual void render(SDL_Renderer* renderer);

	std::string getName();


protected:
	Text *optionText;
	std::string name;
};