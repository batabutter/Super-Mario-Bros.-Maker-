#pragma once

#include "GameLevel.h"

class GameController
{

private:
	GameController() {};
	static GameLevel* currentLevel;
	static bool loading;
public:
	static void LoadInitialLevel(GameLevel* level);
	static void SwitchLevel(GameLevel* level);

	static void Render();
	static void Update();

	static void Init();
};