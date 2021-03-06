#pragma once

#include "../Vec2.h"
#include "../Texture.h"

/**
@brief Contains all the data and functions dealing with the Entity.
*/
class Entity
{
public:
	Entity(Vec2 pos);

	Entity(Vec2 pos, Vec2 dimensions);

	/**
	@brief Create the Entity using the size of the Texture as the size of the Entity.
	@param texture A pointer to the Texture.
	@param pos The position of the Entity.
	*/
	Entity(Texture* texture, Vec2 pos);

	/**
	@brief Create the Entity.
	@param texture A pointer to the Texture.
	@param pos The position of the Entity.
	@param dimensions The dimensions of the Entity.
	*/
	Entity(Texture* texture, Vec2 pos, Vec2 dimensions);



	/**
	@brief Create the Entity with a sprite from a spritesheet. Use this one for quick parts of images
	@param texture A pointer to the Texture.
	@param pos The position of the Entity.
	@param dimensions The dimensions of the Entity.
	@param spritePos The position of the sprite in the spritesheet.
	*/
	Entity(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spritePos);




	/**
	@brief Create the Entity with a sprite from a spritesheet.
	@param texture A pointer to the Texture.
	@param pos The position of the Entity.
	@param dimensions The dimensions of the Entity.
	@param spritePos The position of the sprite in the spritesheet.
	@param spriteDimensions The dimensions of the sprite in the spritesheet.
	*/
	Entity(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spritePos, Vec2 spriteDimensions);


	virtual ~Entity();

	/**
	@brief Update the Entity.
	@param dt The delta time.
	*/
	virtual void update(float dt) = 0;

	/**
	@brief Render the Entity.
	@param renderer A pointer to the renderer.
	*/
	virtual void render(SDL_Renderer* renderer);

	virtual void render(SDL_Renderer* renderer, float scale);

	/**
	@brief Set the position of the Entity.
	@param pos The position of the Entity.
	*/
	void setPosition(Vec2 pos);

	/**
	@brief Set the dimensions of the Entity.
	@param dimensions The dimensions of the Entity.
	*/
	void setDimensions(Vec2 dimensions);

	/**
	@brief Get the position of the Entity.
	@return The position of the Entity.
	*/
	Vec2 getPosition();	

	/**
	@brief Get the dimensions of the Entity.
	@return The dimensions of the Entity.
	*/
	Vec2 getDimensions();




	bool mouseCollide(int mouseX, int mouseY);


	Vec2 getLastPos();

protected:
	///The XY position of the Entity.
	Vec2 pos;
	///The dimensions of the Entity.
	Vec2 dimensions;
	///A pointer to the Texture of the entity.
	Texture* texture;
	///The position of the sprite in the spritesheet.
	Vec2 spritePos;
	///The dimensions of the sprite in the spritesheet.
	Vec2 spriteDimensions;

	///The frame of the state this entity is in
	int frame = 0;

	///The state of the entity - idle, attacking, wandering, hiding etc
	int state = 0;

	///The current action of the entity - walking, stopped
	int action = 0;

	///The velocity of the entity - direction and current speed
	Vec2 velocity = Vec2(0,0);


	///The last position of the Entity
	Vec2 lastPos = Vec2(0);
	

};