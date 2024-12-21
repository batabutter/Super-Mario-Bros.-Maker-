#include "Demo.h"

#include <windows.h>
#include <string>

void Demo::Load()
{
	yIncrement = 0.0f;
	xIncrement = 0.0f;

	sprites = new SpriteSheet(L"test.png", graphics, 16, 16);

}


void Demo::Unload()
{
	delete sprites;
}

void Demo::Render()
{

	graphics->ClearScreen(0.5f, 0.5f, 0.5f);
	DrawGrid();
	
	graphics->DrawRectangle(80, 50, 180, 150, 0.0f, 1.0f, 0.0f, 0.3f, false);

	DrawCharacter();

	levelEditor->CreateBuildInterface();

	for (int i = 0; i < moveableObjects.size(); i++)
		DrawRectObject(moveableObjects.at(i));
}

void Demo::Update()
{

	frame++;
}


Demo::~Demo()
{
	/*
	ClearObjects();
	delete character;
	delete sprites;
	*/
}
