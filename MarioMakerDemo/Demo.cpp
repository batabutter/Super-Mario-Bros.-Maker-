#include "Demo.h"

#include <windows.h>
#include <string>

void Demo::Load()
{
	// Initialize the sprite sheet.
	// NOTE: The variable "sprites" is **intended** to hold the sprites for the character, but this decision is likely to be overhauled.
	map = new SpriteSheet(L"test.png", graphics, 16, 16);

	character->Load(graphics);
}


void Demo::Unload()
{
	// Delete sprites variable from memory
	delete map;
}

void Demo::Render()
{
	// Start by clearing the screen of the graphics
	graphics->ClearScreen(0.5f, 0.5f, 0.5f);

	// Begin by drawing the grid of the playable area. Everything will essentially be over this grid
	DrawGrid();
	
	// TEST RECTANGLE TO BE DRAWN. USED FOR DEMO PURPOSES ONLY:
	// Draws the outline of a green rectangle
	//graphics->DrawRectangle(80, 50, 180, 150, 0.0f, 1.0f, 0.0f, 0.3f, false);

	// Draws the playable character
	DrawCharacter();

	// Using the singleton levelEditor, we load the build interface for the game since we intend to have a building section
	levelEditor->CreateBuildInterface();

	// For all moveable objects in the level, load them
	// NOTE: This is unused currently, but this is intended to be used for enemies or any other dynamic objects
	for (int i = 0; i < moveableObjects.size(); i++)
		DrawRectObject(moveableObjects.at(i));
}

// Not implemented for demo
void Demo::Update()
{

}

// Deconstructor:
// NOTE: This program is terribly wasteful in memory. These objects need to be properly destroyed after use. 
// TODO: Fix this
Demo::~Demo()
{
	/*
	ClearObjects();
	delete character;
	delete sprites;
	*/
}
