#pragma once

#include <windows.h>
#include <d2d1_1.h>
#include "Graphics.h"
#include "Demo.h"
#include "GameController.h"
#include "RectObject.h"
#include <windowsx.h>
#include "LevelEditor.h"
#include "Input.h"

#include <chrono>
#include <thread>

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

	static GameController* instance;
	LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	struct TimeInfo
	{
		std::chrono::time_point<std::chrono::steady_clock> now = std::chrono::high_resolution_clock::now();
		std::chrono::time_point<std::chrono::steady_clock> lastUpdate = std::chrono::high_resolution_clock::now();

		std::chrono::milliseconds deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUpdate);

	};

	static TimeInfo* timeInfo;


public:

	// Both copies deleted since singleton class
	GameController(const LevelEditor&) = delete;
	GameController& operator=(const LevelEditor&) = delete;

	~GameController();


	int UpdateGame();

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
	static int Init(HWND windowHandle);

	static GameController* GetInstance() { if (instance == nullptr) { instance = new GameController(); } return instance; }

public:

	static const float frameIntervalMS;
	static const int WINDOW_HEIGHT = 800;
	static const int WINDOW_WIDTH = 800;

	static const float xCharacterStart;
	static const float yCharacterStart;

	// Create singleton LevelEditor
	static LevelEditor* levelEditor;

	// Create singleton Input handler

	static Graphics* graphics;

	static bool wasKeyDown;
	static bool isKeyDown;

};