#include "GameController.h"
#include "Mario.h"

GameLevel* GameController::currentLevel;
bool GameController::loading;
GameController* GameController::instance = nullptr;

const float GameController::frameIntervalMS = 16.0f;

// Create singleton LevelEditor
LevelEditor* GameController::levelEditor = LevelEditor::GetInstance();

const float GameController::xCharacterStart = 256.0f;
const float GameController::yCharacterStart = 256.0f;

// Create singleton Input handler

Graphics* GameController::graphics = new Graphics();;

bool GameController::wasKeyDown = false;
bool GameController::isKeyDown = false;

GameController::TimeInfo* GameController::timeInfo = nullptr;


void GameController::LoadInitialLevel(GameLevel* level)
{
	// Starts by setting loading to true
	loading = true;

	// Sets the current level and loads it
	currentLevel = level;

	RectObject* character = new Mario(32.0f, 24.0f, 64.0f, 64.0f, 0.0f, 1.0f, 0.0f, 1.0f, true);
	currentLevel->Init(graphics, character, xCharacterStart, yCharacterStart, levelEditor);
	currentLevel->Load();

	// For testing
	currentLevel->AppendStaticRectObject(new RectObject(432.0f, 64.0f, 160.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, true));

	// WE SET THE CHARACTER FALLING TO TRUE. PROBABLY CHAGNE THIS LATER

	character->isFalling = true;


	// Just lods level 1
	Input::Init(currentLevel);

	// No longer loading
	loading = false;


}
void GameController::SwitchLevel(GameLevel* level)
{

	// Set loading to true
	loading = true;

	// Unload the current level and delete it
	currentLevel->Unload();
	level->Load();
	delete currentLevel;
	currentLevel = level;

	// No longer loading
	loading = false;
}

void GameController::Render()
{

	// Wait until not loading
	if (loading)
		return;

	// If not loading, render the level

	if (currentLevel != nullptr)
		currentLevel->Render();
}


void GameController::Update()
{

	// If not loading, update the level
	if (loading)
		return;

	if (currentLevel != nullptr)
	currentLevel->Update();
}

int GameController::Init(HWND windowHandle)
{

	// Start loading and intialize the currentLevel
	loading = true;
	currentLevel = 0;

	if (!graphics->Init(windowHandle)) {
		delete graphics;
		return -1;
	}

	GameController::timeInfo = new GameController::TimeInfo {std::chrono::high_resolution_clock::now(), std::chrono::high_resolution_clock::now(), std::chrono::duration<long long, std::milli>::duration() };


	// Initialize the level editor and the input

	levelEditor->Init(graphics);

	return 1;
}

int GameController::UpdateGame()
{

	int result = 1;

	//RectObject* block = new RectObject(100.0f, 100.0f, 80.0f, 50.0f, 0.0f, 0.0f, 0.0f, 1.0f, false);
	/* Recreate this. This is so messy and all the window creating fuctions make it really hard to know where and what to edit
	*/

	//currLevel->AppendStaticRectObject(block);

	// Call the GameController which calls the level's load functions
	//WM_DESTROY
	// Peeks messages so the program isn't constatnly waiting for input
	timeInfo->now = std::chrono::high_resolution_clock::now();

	timeInfo->lastUpdate = std::chrono::high_resolution_clock::now();

	timeInfo->deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(timeInfo->now - timeInfo->lastUpdate);


	while (timeInfo->deltaTime.count() <= frameIntervalMS)
	{
		Input::ProcessKeyboardInput(Input::keyboard.lastKeyPressed, wasKeyDown, isKeyDown, currentLevel->GetCharacter());

		GameController::Update();
		graphics->BeginDraw();
		GameController::Render();
		graphics->EndDraw();

		timeInfo->now = std::chrono::high_resolution_clock::now();
		timeInfo->deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(timeInfo->now - timeInfo->lastUpdate);
	}

	/*

	// Make sure to delete the rest of the stuff

	*/

	return 1;
}


GameController::~GameController()
{
	delete currentLevel;
	currentLevel = nullptr;

	delete currentLevel;
	currentLevel = nullptr;

	delete timeInfo;
	timeInfo = nullptr;

	delete levelEditor;
	levelEditor = nullptr;

	delete graphics;
	graphics = nullptr;
}
