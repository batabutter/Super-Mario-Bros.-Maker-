#pragma once

#include "GameLevel.h"

/* GameController.h:
*  This singleton class is intended to be an overhead that switches between the current level we are playing.
*/

class GameController
{

private:

	// Singleton class, constructor not needed to be public 
	GameController() {};

	// Pointer to the current level
	static GameLevel* currentLevel;

	// Tells you whether or not we are in the midst of loading a level. Unused for now.
	static bool loading;
public:

	// Both copies deleted since singleton class
	GameController(const LevelEditor&) = delete;
	GameController& operator=(const LevelEditor&) = delete;

	// LoadInitialLevel(GameLevel* level):
	// Given a game level, we store the level as the currnet level passed as a parameter
	// level: The level we are storing.
	static void LoadInitialLevel(GameLevel* level);

	// SwitchLevel(GameLevel* level):
	// Given a level, we set the current level to the new one in the parameter
	// level: The level to switch to 
	static void SwitchLevel(GameLevel* level);

	// Render():
	// Renders the current level calling the currentLevel's render method.
	static void Render();

	// Update():
	// Updates the current level calling the currentLevel's update method.
	static void Update();

	// Init():
	// Starts loading and sets the currentLevel
	// NOTE: Unfinished
	static void Init();
};