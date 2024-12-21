#include "GameController.h"

GameLevel* GameController::currentLevel;
bool GameController::loading;


void GameController::LoadInitialLevel(GameLevel* level)
{
	loading = true;

	currentLevel = level;
	currentLevel->Load();

	loading = false;

}
void GameController::SwitchLevel(GameLevel* level)
{
	loading = true;

	currentLevel->Unload();
	level->Load();
	delete currentLevel;
	currentLevel = level;

	loading = false;


}

void GameController::Render()
{
	if (loading)
		return;
	currentLevel->Render();
}

void GameController::Update()
{
	if (loading)
		return;
	currentLevel->Update();
}

void GameController::Init()
{
	loading = true;
	currentLevel = 0;
}