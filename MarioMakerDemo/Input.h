#pragma once

#include "GameLevel.h"
#include <windows.h>
#include "RectObject.h"

// Number of keys that we will be useing. Since the NES has 6 buttons, this should pretty much never change for the general input.
// However, for debuggin ad possibly shifting the map and stuff this number could be subject to change


// Rework because this might just be as good as making everything static instead of insgleton


const int NUM_KEYS = 6;

#define DC_UP			0
#define DC_DOWN			1
#define DC_LEFT			2
#define DC_RIGHT		3

#define DC_X			4
#define DC_Z			5

class Input
{

public:

	struct KeyState
	{
		bool wasDown, isDown;
		int framesHeld = 0;

		bool successfulMove = true;
	};

	struct KeyboardInputMap
	{
		KeyState keys[NUM_KEYS];
		uint32_t lastKeyPressed;
	};

	static KeyboardInputMap keyboard;
	Input(const LevelEditor&) = delete;
	Input& operator=(const LevelEditor&) = delete;


	void static Init(GameLevel* level) { if (currLevel != nullptr) delete currLevel; currLevel = level; }

	~Input() { delete currLevel; currLevel = nullptr; }

	static void ProcessKeyboardInput(uint32_t VKCode, bool wasDown, bool isDown, RectObject* obj);

private:

	static GameLevel* currLevel;
	Input() {}
	static Input* instance;

};