#pragma once

#include "../entities/Entity.h"
#include "Tile.h"
#include "../entities/creatures/Character.h"
#include "../entities/creatures/Creature.h"
#include <Vector>
#include "MapManager.h"
#include "RoomTemplate.h"
#include <math.h>

#include "../entities/Entity.h"

/**
@brief Contains the data for a single room on the map
*/
class MapRoom
{
public:
	/**
	@brief Creates a blank MapRoom
	*/
	MapRoom(Vec2 rp);


	/**
	@brief Creates a blank MapRoom
	*/
	MapRoom();


	/**
	@brief Creates a MapRoom using the map
	*/
	MapRoom(MapManager *mpmng, Vec2 pos, int e);

	/**
	@brief Creates a MapRoom using the imported data
	*/
	MapRoom::MapRoom(MapManager *mpmng, Vec2 pos, int e, int index, Vec2 rp);


	/**
	@brief Room destructor
	*/
	~MapRoom();

	/**
	@brief Update the Map.
	@param dt The delta time.
	*/
	void update(float dt);


	/**
	@brief Render the Tile objects in the map.
	@param renderer A pointer to the renderer.
	*/
	void render(SDL_Renderer* renderer);



	/**
	@brief
	*/
	void createRoom(MapManager *mpmng, TileTypeManager *ttmng, CreatureManager *cmng, Vec2 pos, int type, bool fromlevel, int index);

	/**
	@brief
	*/
	void loadPlayer(CharacterType *pt);

	/**
	@brief
	*/
	int checkCollide(Entity *e);

	/**
	@brief
	*/
	void setPos(Vec2 pos);

	/**
	@brief
	*/
	Vec2 getPos();

	/**
	@brief
	*/
	void setAccess(bool b);

	/**
	@brief
	*/
	bool getAccess();

	/**
	@brief
	*/
	Tile* getTile(Vec2 xy);

	/**
	@brief
	*/
	bool getExists();


	/**
	@brief
	*/
	void setExists(bool e);


	void changeTileType(std::string layer, Vec2 mousePos, std::string tileID, TileTypeManager *ttmng);

	void changeTileType(std::string layer, Vec2 mousePos, std::string tileID, TileTypeManager *ttmng, int t);

	std::unordered_map<std::string, std::vector<std::vector<std::string>>> getRoomTilesStrings();

	std::vector<std::string> getRoomCreaturesStrings();

	std::vector<std::string> getLayerIDs();

	void addCreature(Vec2 p, CreatureType *ct);

	Creature* getCreatureByIndex(int index);

	int getNumCreatures();

	void setPosition(Vec2 pos);

	

private:

	///A vector to hold all of the layer IDs.
	std::vector<std::string> layerIDs;
	///A 3D vector that contains all of the tiles. [Layer ID][Y Index][X Index]
	std::unordered_map<std::string, std::vector<std::vector<Tile*>>> roomTiles;


	std::unordered_map<std::string, std::vector<std::vector<std::string>>> roomTilesStrings;
	std::vector<std::string> roomCreatureStrings;

	//An unordered map that contains all of the creatures. [Layer ID][Y Index][X Index]
	//std::unordered_map<std::string, Creature*> mapCreatures;

	///A vector of all creatures
	std::vector<Creature*> roomCreatures;

	///A 2D vector storing the spawn point of the player
	Vec2 spawnPoint;

	///the map's ID
	std::string ID;

	Vec2 roomPos;


	bool playerLoaded = false;


	Vec2 mapPos;

	bool access = false;

	Character *player;

	bool exists = false;

	Vec2 renderPosition;
};