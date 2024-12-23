#include "GameController.h"

GameLevel* GameController::currentLevel;
bool GameController::loading;


void GameController::LoadInitialLevel(GameLevel* level)
{
	// Starts by setting loading to true
	loading = true;

	// Sets the current level and loads it
	currentLevel = level;
	currentLevel->Load();

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

void GameController::Init()
{

	// Start loading and intialize the currentLevel
	loading = true;
	currentLevel = 0;
}