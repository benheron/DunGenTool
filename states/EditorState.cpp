#include "EditorState.h"
#include "../Utility.h"
#include "../Collision.h"




EditorState::EditorState(StateManager* manager, Platform *platform, DataManager *dtmng)
	: State(manager, platform), dtmng(dtmng)
{
	stateName = "EditorState";
	viewSelected = editSelection;
}

EditorState::~EditorState()
{

}

bool EditorState::eventHandler()
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	resetView = false;

	mousePos = Vec2(mouseX, mouseY);
	SDL_Event events;
	while (SDL_PollEvent(&events))
	{
		switch (events.type)
		{

		case SDL_MOUSEMOTION:
			//while mouse is moving
			if (mm->mouseCollide(mouseX, mouseY))
			{
				//Utility::log(Utility::I, "Collided at: " + Utility::intToString(mouseX) + ", " + Utility::intToString(mouseY));
			}

			//slider
			if (mouseDownSlider)
			{
				if (Collision::pointBoxCollision(mousePos, numRoomsSlider->getPosition(), numRoomsSlider->getDimensions()))
				{
					numRoomsSlider->changeValue(mousePos);

					/*Texture *nTex = new Texture(platform->getRenderer(), Utility::intToString(numRoomsSlider->getValue()), font, { 255,255,255 });
					Texture *oldTex = numRoomsText;

					numRoomsText = nTex;

					delete oldTex;*/
				}
			}


		



			//buttons
			for (int i = 0; i < editorButtons.size(); i++)
			{
				if (Collision::pointBoxCollision(mousePos, editorButtons[i]->getPosition(), editorButtons[i]->getDimensions()))
				{
					if (!editorButtons[i]->getSelected())
					{
						editorButtons[i]->setHover(true);
					}
				}
				else {
					//editorButtons[i]->setHover(false);
					if (!editorButtons[i]->getSelected())
					{
						editorButtons[i]->setIdle();
					}
				}
			}

			menuBar->checkHover(mousePos);


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
				//minimap
				if (mm->mouseCollide(mouseX, mouseY))
				{
					Vec2 tmp = mm->changeRoom(mouseX, mouseY);
					if (tmp.x != -1)
					{
						randFloor->setCurRoomPos(tmp);
						currentMap = randFloor->getCurMap();
					}
				}

				//generate map button
				if (Collision::pointBoxCollision(Vec2(mouseX, mouseY), genMapBtn->getPosition(), genMapBtn->getDimensions()))
				{
					genBtnDwn = true;
					createNewMap();
				}

				//slider
				if (Collision::pointBoxCollision(mousePos, numRoomsSlider->getPosition(), numRoomsSlider->getDimensions()))
				{
					numRoomsSlider->changeValue(mousePos);
					mouseDownSlider = true;

					/*Texture *nTex = new Texture(platform->getRenderer(), Utility::intToString(numRoomsSlider->getValue()), font, { 255,255,255 });
					Texture *oldTex = numRoomsText;

					numRoomsText = nTex;

					delete oldTex;*/
				}



				//add tiles or creatures to the map itself
				if (Collision::pointBoxCollision(mousePos, randFloor->getPosition(), randFloor->getDimensions()))
				{
					changingTiles = true;
				/*	if (tileSelection->getTypeSelected() == "O")
					{
						randFloor->getCurMap()->changeTileType("O", mousePos / 32, tileTypeSelected, ttmng);
					}
					else if (tileSelection->getTypeSelected() == "B") {
						randFloor->getCurMap()->changeTileType("B", mousePos / 32, tileTypeSelected, ttmng);
					}
					else if (tileSelection->getTypeSelected() == "C") {
						randFloor->getCurMap()->addCreature(mousePos, cmng->getCreatureType("A0"));
					}*/
					
					
				}

				//tile selection
				if (Collision::pointBoxCollision(mousePos, tileSelection->getPosition(), tileSelection->getDimensions()))
				{
					tileSelection->changeSelectedTile(mousePos);
					tileTypeSelected = tileSelection->getSelectedTile();
					paintBtn->setSelected(true);
					eraseBtn->setIdle();
				}

				//background layer button
				if (Collision::pointBoxCollision(mousePos, bgLayerBtn->getPosition(), bgLayerBtn->getDimensions()))
				{
					bgLayerBtn->setSelected(true);
					crLayerBtn->setIdle();
					objLayerBtn->setIdle();
					
					tileSelection->setTypeSelected("B");
					tileTypeSelected = tileSelection->getSelectedTile();
				}

				//object layer button
				if (Collision::pointBoxCollision(mousePos, objLayerBtn->getPosition(), objLayerBtn->getDimensions()))
				{
					

					bgLayerBtn->setIdle();
					crLayerBtn->setIdle();
					objLayerBtn->setSelected(true);
					tileSelection->setTypeSelected("O");
					tileTypeSelected = tileSelection->getSelectedTile();
				}

				//add creature
				if (Collision::pointBoxCollision(mousePos, crLayerBtn->getPosition(), crLayerBtn->getDimensions()))
				{
					
					bgLayerBtn->setIdle();
					crLayerBtn->setSelected(true);

					objLayerBtn->setIdle();
					
					tileSelection->setTypeSelected("C");
				}


				//test map button
				if (Collision::pointBoxCollision(mousePos, testMapBtn->getPosition(), testMapBtn->getDimensions()))
				{
					playMap = true;
				}

				if (Collision::pointBoxCollision(mousePos, paintBtn->getPosition(), paintBtn->getDimensions()))
				{
					paintBtn->setSelected(true);
					eraseBtn->setIdle();
					
				}

				if (Collision::pointBoxCollision(mousePos, eraseBtn->getPosition(), eraseBtn->getDimensions()))
				{
					
					eraseBtn->setSelected(true);
					paintBtn->setIdle();
				}
				
				std::string mbSelect = menuBar->checkSelected(mousePos);

				if (mbSelect != "None" && mbSelect != "bar")
				{
					viewSelected = menuBarSelection;
					/*if (mbSelect == "IRT")
					{

					}*/
					//import map button
					if (mbSelect == "IFM")
					{
						importLevelData();
					}
					//export room as template button
					if (mbSelect == "ETRT")
					{
						exportRoomAsTemplate();
					}
					//export map button
					if (mbSelect == "EM")
					{
						exportData(0);
					}

					resetView = true;
				}
				else {
					viewSelected = editSelection;
				}

				if (Collision::pointBoxCollision(mousePos, menuBar->getPosition(), menuBar->getDimensions()))
				{
					
					viewSelected = menuBarSelection;
				}
				else {

				//	viewSelected = editSelection;
				}

				/*if (menuBar->checkSelected(mousePos))
				{
					viewSelected = menuBarSelection;
				}
				else {
					viewSelected = editSelection;
				}*/


			break;
				

			}
			break;
		case SDL_MOUSEBUTTONUP:
			switch (events.button.button)
			{
			case SDL_BUTTON_LEFT:
				mouseDownSlider = false;
				changingTiles = false;
			break;
			}
		break;
		case SDL_KEYDOWN:
			switch (events.key.keysym.sym)
			{
				//pressing a key
			case SDLK_ESCAPE:
				//pause menu
				stateManager->addState(dtmng->getPauseMenuState());
				break;
			}
			break;
		case SDL_KEYUP:
			switch (events.key.keysym.sym)
			{
			case SDLK_i:
				//importLevelData();
				break;

			case SDLK_e:
				//exportLevelData();
				break;
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

void EditorState::update(float dt)
{
	//Utility::log(Utility::I, "Slider value: " + Utility::intToString(numRoomsSlider->getValue()));
	if (playMap)
	{
		playMap = false;
		active = false;
		stateManager->addState(new GameState(stateManager, platform, dtmng, randFloor, 1));
	}

	
	if (viewSelected == editSelection && !resetView)
	{
		//add tiles or creatures to the map itself
		if (changingTiles)
		{
			if (Collision::pointBoxCollision(mousePos, randFloor->getPosition() + Vec2(32, 32), randFloor->getDimensions() - Vec2(64, 64)))
			{
				if (paintBtn->getSelected())
				{
					if (tileSelection->getTypeSelected() == "O")
					{
						randFloor->getCurMap()->changeTileType("O", mousePos, tileTypeSelected, dtmng->getTileTypeManager(), 0);
					}
					else if (tileSelection->getTypeSelected() == "B") {
						randFloor->getCurMap()->changeTileType("B", mousePos, tileTypeSelected, dtmng->getTileTypeManager(), 0);
					}
					else if (tileSelection->getTypeSelected() == "C") {
						randFloor->getCurMap()->addCreature(mousePos, dtmng->getCreatureManager()->getCreatureType("A0"));
					}
				}
				else if (eraseBtn->getSelected()) {
					if (tileSelection->getTypeSelected() == "O")
					{
						randFloor->getCurMap()->changeTileType("O", mousePos, "XX", dtmng->getTileTypeManager(), 0);
					}
					else if (tileSelection->getTypeSelected() == "B") {
						randFloor->getCurMap()->changeTileType("B", mousePos, "XX", dtmng->getTileTypeManager(), 0);
					}
					else if (tileSelection->getTypeSelected() == "C") {
						randFloor->getCurMap()->changeTileType("C", mousePos, "XX", dtmng->getTileTypeManager(), 0);
					}
				}
			}
		}
	}
	
}

void EditorState::render()
{
	editBgTexture->pushSpriteToScreen(platform->getRenderer(), 0);
	randFloor->getCurMap()->render(platform->getRenderer());
	//room grid
	for (int i = 1; i < 20; i ++)
	{
		white->pushToScreen(platform->getRenderer(), Vec2(i * 32 + 10, 32 + 42), Vec2(1, 13*32));
	}
	for (int j = 1; j < 15; j++)
	{
		white->pushToScreen(platform->getRenderer(), Vec2(32 + 10, j*32 + 42), Vec2(18*32,1));
	}

	toolBgTexture->pushSpriteToScreen(platform->getRenderer(), toolbgpos);
	black->pushToScreen(platform->getRenderer(), toolbgpos, Vec2(1, 540));
	black->pushToScreen(platform->getRenderer(), Vec2(0.f, menuBar->getDimensions().y), Vec2(platform->getWindowSize().x, 1.f));

	//minimap grid
	for (int i = 0; i < 11; i++)
	{
		white->pushToScreen(platform->getRenderer(), Vec2(700+(i * 20), 36), Vec2(1, 10 * 15));
	}
	for (int j = 0; j < 11; j++)
	{
		white->pushToScreen(platform->getRenderer(), Vec2(700, 36+(j * 15)), Vec2(10 * 20, 1));
	}

	

	numRoomsSlider->render(platform->getRenderer());

	
	tileSelection->render(platform->getRenderer());



	layerText->render(platform->getRenderer());
	bgText->render(platform->getRenderer());
	objText->render(platform->getRenderer());
	enemyText->render(platform->getRenderer());


	



	bgLayerBtn->render(platform->getRenderer());
	objLayerBtn->render(platform->getRenderer());
	crLayerBtn->render(platform->getRenderer());

	
	/*testMapBtn->render(platform->getRenderer());
	expMapBtn->render(platform->getRenderer());
	impMapBtn->render(platform->getRenderer());
	expRoomBtn->render(platform->getRenderer());
	genMapBtn->render(platform->getRenderer());*/

	if (crLayerBtn->getSelected())
	{
		enemy->render(platform->getRenderer());
	}
	//enemy->render(platform->getRenderer());


	mm->render(platform->getRenderer());

	menuBar->render(platform->getRenderer());
	for (int i = 0; i < editorButtons.size(); i++)
	{
		editorButtons[i]->render(platform->getRenderer());
	}
}

void EditorState::load()
{
	//generate-map button
	//white texture
	white = new Texture(platform->getRenderer(), 255, 255, 255);
	black = new Texture(platform->getRenderer(), 0, 0, 0);

	editBgTexture = new Texture("res/img/background.png", platform->getRenderer());
	toolBgTexture = new Texture("res/img/lighterbackground.png", platform->getRenderer());
	

	//room slider
	numRoomsSlider = new Slider(white, Vec2(700, 247), Vec2(200, 15), 20, dtmng->getTextImageManager());

	//map
	randFloor = new RandMap(dtmng->getMapManager(), dtmng->getTileTypeManager(), dtmng->getCreatureManager(), numRoomsSlider->getValue());
	currentMap = randFloor->getCurMap();

	//minimap
	mm = new MiniMap(platform->getRenderer(), 1);
	mm->buildMiniMap(randFloor, Vec2(700, 36));


	//buttons
	genTexture = new Texture("res/img/buttons/generateBtn.png", platform->getRenderer());
	genMapBtn = new Button(genTexture, Vec2(750, 192), Vec2(100, 46), Vec2(0, 0));

	Texture *testMapTexture = new Texture("res/img/buttons/testmapBtn.png", platform->getRenderer());
	testMapBtn = new Button(testMapTexture, Vec2(280, 0), Vec2(100, 32), Vec2(0, 0));

	/*Texture *impTexture = new Texture("res/img/buttons/importBtn.png", platform->getRenderer());
	impMapBtn = new Button(impTexture, Vec2(0, 485), Vec2(50, 23), Vec2(0, 0));

	Texture *expTexture = new Texture("res/img/buttons/exportBtn.png", platform->getRenderer());
	expMapBtn = new Button(expTexture, Vec2(0, 510), Vec2(50, 23), Vec2(0, 0));


	Texture *expRoomTexture = new Texture("res/img/buttons/exportRoomBtn.png", platform->getRenderer());
	expRoomBtn = new Button(expRoomTexture, Vec2(60, 510), Vec2(50, 23), Vec2(0, 0));*/


	editorButtons.push_back(genMapBtn);
	editorButtons.push_back(testMapBtn);
	





	tileSelctionPos = Vec2(670, 330);

	toolbgpos = Vec2(tileSelctionPos.x - 10, 0.f);

	//tile selection
	Texture *grey = new Texture(platform->getRenderer(), 128, 128, 128);
	tileSelection = new TileSelection(Vec2(670, 340), Vec2(8, 5), dtmng->getTileTypeManager(), white, grey);
	tileTypeSelected = "G0";
	tileSelection->setTypeSelected("B");



	//layer
	Texture *btn = new Texture("res/img/buttons/selectBtn.png", platform->getRenderer());

	bgLayerBtn = new Button(btn, Vec2(795, 315), Vec2(16, 16), Vec2(0, 0));
	objLayerBtn = new Button(btn, Vec2(885, 315), Vec2(16, 16), Vec2(0, 0));
	crLayerBtn = new Button(btn, Vec2(735, 505), Vec2(16, 16), Vec2(0, 0));
	bgLayerBtn->setSelected(true);

	paintTex = new Texture("res/img/buttons/paint.png", platform->getRenderer());
	eraseTex = new Texture("res/img/buttons/erase.png", platform->getRenderer());

	paintBtn = new Button(paintTex, Vec2(540, 0), Vec2(32, 32), Vec2(0, 0));
	eraseBtn = new Button(eraseTex, Vec2(572, 0), Vec2(32, 32), Vec2(0, 0));

	paintBtn->setSelected(true);
	eraseBtn->setIdle();

	editorButtons.push_back(paintBtn);
	editorButtons.push_back(eraseBtn);


	layerText = new Text(Vec2(670, 295), 0, "Arial", 20, "Layer: ", dtmng->getTextImageManager());
	bgText = new Text(Vec2(690, 315), 0, "Arial", 20, "Background: ", dtmng->getTextImageManager());
	objText = new Text(Vec2(820, 315), 0, "Arial", 20, "Object: ", dtmng->getTextImageManager());
	enemyText = new Text(Vec2(670, 503), 0, "Arial", 20, "Enemy: ", dtmng->getTextImageManager());

	enemy = new Creature(grey, Vec2(680, 348), Vec2(13, 19), dtmng->getCreatureManager()->getCreatureType("A0"));
	
	barbg = new Texture("res/img/menubarbg.png", platform->getRenderer());
	optionTexture = new Texture("res/img/menuimage.png", platform->getRenderer());

	menuBar = new MenuBar(barbg, optionTexture, 0, Vec2(platform->getWindowSize().x, 32.f), dtmng->getTextImageManager());
	 
}

void EditorState::unload()
{
	for (int i = editorButtons.size()-1; i > -1; i--)
	{
		delete editorButtons[i];
	}

	delete layerText;
	delete bgText;
	delete objText;
	delete enemyText;
	delete tileSelection;
	//delete font;
	delete numRoomsSlider;
	delete randFloor;
	delete mm;
	delete genTexture;

	delete barbg;
	delete optionTexture;


	
}

void EditorState::createNewMap()
{
	RandMap *newFloor = new RandMap(dtmng->getMapManager(), dtmng->getTileTypeManager(), dtmng->getCreatureManager(), numRoomsSlider->getValue());
	RandMap *oldFloor;

	oldFloor = randFloor;
	randFloor = newFloor;

	delete oldFloor;

	MiniMap *newMiniMap = new MiniMap(platform->getRenderer(), 0);
	newMiniMap->buildMiniMap(randFloor, Vec2(700, 36));

	MiniMap *oldMiniMap = mm;
	delete oldMiniMap;

	mm = newMiniMap;

	currentMap = randFloor->getCurMap();
}


void EditorState::createMapFromFile(MapManager *newmng)
{
	RandMap *newFloor = new RandMap(newmng, dtmng->getTileTypeManager(), dtmng->getCreatureManager(), true);
	RandMap *oldFloor;

	oldFloor = randFloor;
	randFloor = newFloor;

	delete oldFloor;

	MiniMap *newMiniMap = new MiniMap(platform->getRenderer(), 0);
	newMiniMap->buildMiniMap(randFloor, Vec2(700, 36));

	MiniMap *oldMiniMap = mm;
	delete oldMiniMap;

	mm = newMiniMap;

	currentMap = randFloor->getCurMap();

	randFloor->setCurRoomPos(Vec2(5, 5));
	mm->update(0.f);
}

void EditorState::importLevelData()
{
	IFileDialog *pfd;
	if (SUCCEEDED(CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd))))
	{
		if (SUCCEEDED(pfd->Show(NULL)))
		{
			IShellItem *psi;
			if (SUCCEEDED(pfd->GetResult(&psi)))
			{
				PWSTR pszPath;
				if (SUCCEEDED(psi->GetDisplayName(SIGDN_FILESYSPATH, &pszPath)))
				{
					std::string str = CW2A(pszPath);
					Utility::log(Utility::I, str);

					//get level data
					MapManager *newmmng = new MapManager(str, dtmng->getTileTypeManager(), dtmng->getCreatureManager(), 1);
					createMapFromFile(newmmng);

					delete newmmng;

					CoTaskMemFree(pszPath);
				}
				psi->Release();
			}
		}
		pfd->Release();
	}
}

void  EditorState::exportData(int type)
{
	// CoCreate the File Open Dialog object.
	IFileSaveDialog *pfsd;
	if (SUCCEEDED(CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfsd))))
	{
		pfsd->SetDefaultExtension(L"txt");

		if (SUCCEEDED(pfsd->Show(NULL)))
		{
			IShellItem *psiResult;

			if (SUCCEEDED(pfsd->GetResult(&psiResult)))
			{
				PWSTR pszNewFileName;
				if (SUCCEEDED(psiResult->GetDisplayName(SIGDN_FILESYSPATH, &pszNewFileName)))
				{
					std::string str = CW2A(pszNewFileName);
					Utility::log(Utility::I, str);
					if (type == 0)
					{
						exportLevelToFile(str);
					}
					else if (type == 1)
					{
						exportRoomAsTemplate();
					}

					CoTaskMemFree(pszNewFileName);
				}
				psiResult->Release();
			}
		}
		pfsd->Release();
	}
}



void EditorState::exportLevelToFile(std::string fn)
{

	std::ofstream levelFile(fn);

	if (levelFile.is_open())
	{
		Utility::log(Utility::I, "New file, yay");

		int numRoomsToSave = randFloor->getNumRooms();

		levelFile << numRoomsToSave;
		levelFile << "\n";

		for (int i = 0; i < numRoomsToSave; i++)
		{
			

			MapRoom *mr = randFloor->getRoom(i);
			Vec2 p = mr->getPos();

			levelFile << p.x;
			levelFile << " ";
			levelFile << p.y;
			levelFile << "\n";


			std::unordered_map<std::string, std::vector<std::vector<std::string>>> rts = mr->getRoomTilesStrings();
			std::vector<std::string> rcs = mr->getRoomCreaturesStrings();

			std::vector<std::string> lIDs = mr->getLayerIDs();


			for (int i = 0; i < 3; i++)
			{

				levelFile << lIDs[i];
				levelFile << "\n";


				int ySize = rts["B"].size();



				for (int y = 0; y < ySize; y++)
				{
					int xSize = rts["B"][0].size();

					if (lIDs[i] == "O" || lIDs[i] == "B")
					{
						for (int x = 0; x < xSize; x++)
						{
							//Get the tile
							std::string tileID = rts[lIDs[i]][y][x];

							levelFile << tileID;
							levelFile << " ";
						}

						levelFile << "\n";
					}
					else if (lIDs[i] == "C")
					{
						
						for (int x = 0; x < xSize; x++)
						{
							//Get the creature
							std::string creatureID = rcs[y*xSize + x];

							levelFile << creatureID;
							levelFile << " ";

			
						}
						levelFile << "\n";
					}

				}
			}

		}
		levelFile.close();

	}
	else {
		Utility::log(Utility::I, "Failed :(	");
	}
}


void EditorState::exportRoomAsTemplate()
{

	int msgbox = MessageBox(
		NULL,
		(LPCWSTR)L"Are you sure?",
		(LPCWSTR)L"Confirmation create template",
		MB_YESNO
	);

	Utility::log(Utility::I, Utility::intToString(msgbox));

	if (msgbox == 6)
	{
		MapRoom *mr = randFloor->getCurMap();

		std::unordered_map<std::string, std::vector<std::vector<std::string>>> rts = mr->getRoomTilesStrings();
		std::vector<std::string> rcs = mr->getRoomCreaturesStrings();

		std::vector<std::string> lIDs = mr->getLayerIDs();

		int a = dtmng->getMapManager()->getNumberMaps() + 1;



		std::ostringstream oss;
		oss << a;
		std::string filePath = "res/txt/map" + oss.str() + ".txt";


		std::ofstream roomFile(filePath);



		if (roomFile.is_open())
		{
			Utility::log(Utility::I, "New file, yay");


			if (a < 10)
			{
				roomFile << "M0";
			}
			else {
				roomFile << "M";
			}

			roomFile << a;

			roomFile << "\n";

			roomFile << "20";

			roomFile << "\n";

			roomFile << "15";

			roomFile << "\n";

			roomFile << "3";

			roomFile << "\n";

			roomFile << "32";

			roomFile << "\n";

			roomFile << "32";

			roomFile << "\n";

			for (int i = 0; i < 3; i++)
			{

				roomFile << lIDs[i];
				roomFile << "\n";


				int ySize = rts["B"].size();



				for (int y = 0; y < ySize; y++)
				{
					int xSize = rts["B"][0].size();

					if (lIDs[i] == "O" || lIDs[i] == "B")
					{
						for (int x = 0; x < xSize; x++)
						{


							std::string tileID;
							if (lIDs[i] == "O")
							{
								if ((y == 0 || y == 14) && x > 0 && x < 19)
								{
									tileID = "W0";
								}
								else if ((x == 0 || x == 19) && y > 0 && y < 14)
								{
									tileID = "W1";
								}
								else {
									tileID = rts[lIDs[i]][y][x];
								}

								int g = 0;
							}
							else {
								tileID = rts[lIDs[i]][y][x];
							}


							//Get the tile




							roomFile << tileID;
							roomFile << " ";
						}

						roomFile << "\n";
					}
					else if (lIDs[i] == "C")
					{

						for (int x = 0; x < xSize; x++)
						{
							//Get the creature
							std::string creatureID = rcs[y*xSize + x];

							roomFile << creatureID;
							roomFile << " ";


						}
						roomFile << "\n";
					}

				}
			}
			roomFile.close();
			dtmng->getMapManager()->loadMapData(filePath, dtmng->getTileTypeManager(), dtmng->getCreatureManager());

		}
		else {
			Utility::log(Utility::I, "Failed :(	");
		}
	}

	
}
