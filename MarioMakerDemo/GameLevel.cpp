#include "GameLevel.h"
#include <string>

Graphics* GameLevel::graphics;

D2D1_COLOR_F GameLevel::backgroundColor = DEFAULT_BACKGROUND;

void GameLevel::Init(Graphics* graphics, RectObject* obj, float charStartPosX, float charStartPosY, LevelEditor *editor)
{
	GameLevel::graphics = graphics;
	character = *&obj;
	levelEditor = editor;

	//DEFAULT_WIDTH / DEAULT_PIXEL_INTERVAL][DEFAULT_HEIGHT / DEAULT_PIXEL_INTERVAL
	grid = new pixel*[DEFAULT_WIDTH / DEAULT_PIXEL_INTERVAL];

	for (int i = 0; i < DEFAULT_WIDTH / DEAULT_PIXEL_INTERVAL; i++)
		grid[i] = new pixel[DEFAULT_HEIGHT / DEAULT_PIXEL_INTERVAL];

	character->Reposition(charStartPosX, charStartPosY);

}

void GameLevel::ShowGrid()
{
	float gridHeight = DEFAULT_HEIGHT;
	float gridWidth = DEFAULT_WIDTH;
	float pixelInterval = DEAULT_PIXEL_INTERVAL;

	for (int i = 0; i < (gridWidth / pixelInterval); i++)
	{
		graphics->DrawLine(0, (i * pixelInterval), gridWidth, (i * pixelInterval), 1.0f, 0.0f, 0.0f, 0.5f);
		graphics->DrawLine((i * pixelInterval), 0, (i * pixelInterval), gridHeight, 1.0f, 0.0f, 0.0f, 0.5f);
	}

}

void GameLevel::DrawGrid()
{
	
	// Next, use the grid vectors to fill in every position

	for (int i = 0; i < gridRows; i++)
	{
		for (int k = 0; k < gridColumns; k++)
		{
			DrawRowCol(i, k);
		}
	}

	// Last, draw the grid over the objects
	ShowGrid();
}

void GameLevel::DrawRowCol(int row, int col)
{
	float pixelPosLeft = ((float) row * DEAULT_PIXEL_INTERVAL);
	float pixelPosTop = ((float) col * DEAULT_PIXEL_INTERVAL);
	float pixelPosRight = pixelPosLeft + (float) DEAULT_PIXEL_INTERVAL;
	float pixelPosBottom = pixelPosTop + (float) DEAULT_PIXEL_INTERVAL;

	// ??? I don't know why it doesn't work when flipped, but I am too lazy to care
	// NOTE: Rename the variables and fix later.
	float red = grid[col][row].color.r;
	float green = grid[col][row].color.g;
	float blue = grid[col][row].color.b;
	float alpha = grid[col][row].color.a;

	graphics->DrawRectangle(pixelPosLeft, pixelPosTop, pixelPosRight, pixelPosBottom, red, green, blue, alpha, true);

}

int* GameLevel::RectObjectToGridCoords(RectObject &obj)
{
	float left = obj.GetLeft();
	float right = obj.GetRight();
	float top = obj.GetTop();
	float bottom = obj.GetBottom();

	/*
	* Coords[0] = left
	* Coords[1] = top
	* Coords[2] = right
	* Coords[3] = bottom
	*/

	int *coords = new int[4]{ (int) (left/ DEAULT_PIXEL_INTERVAL), (int)(top / DEAULT_PIXEL_INTERVAL), (int)(right / DEAULT_PIXEL_INTERVAL), (int)(bottom / DEAULT_PIXEL_INTERVAL) };


	return coords;
}


void GameLevel::MoveUp()
{
	int* coords = RectObjectToGridCoords(*character);
	coords[1] = coords[1] - 1;

	if ((coords[1] >= 0) && !(WillCollide(coords)))
		character->Reposition(character->GetLeft(), character->GetTop() - DEAULT_PIXEL_INTERVAL);

	delete[] coords;
}

void GameLevel::MoveDown()
{
	int* coords = RectObjectToGridCoords(*character);
	coords[3] = coords[3] + 1;

	if ((coords[3] <= gridRows) && !(WillCollide(coords)))
		character->Reposition(character->GetLeft(), character->GetTop() + DEAULT_PIXEL_INTERVAL);

	delete[] coords;
}

void GameLevel::MoveLeft()
{
	int* coords = RectObjectToGridCoords(*character);
	coords[0] = coords[0] - 1;

	if ((coords[0] >= 0) && !(WillCollide(coords)))
		character->Reposition(character->GetLeft() - DEAULT_PIXEL_INTERVAL, character->GetTop());

	delete[] coords;
}

void GameLevel::MoveRight()
{
	int* coords = RectObjectToGridCoords(*character);
	coords[2] = coords[2] + 1;

	if ((coords[2] <= gridColumns) && !(WillCollide(coords)))
		character->Reposition(character->GetLeft() + DEAULT_PIXEL_INTERVAL, character->GetTop());

	delete[] coords;
}

void GameLevel::DrawRectObject(RectObject* rect)
{
	float left = rect->GetLeft();
	float right = rect->GetRight();
	float top = rect->GetTop();
	float bottom = rect->GetBottom();

	float red = rect->GetRed();
	float green = rect->GetGreen();
	float blue = rect->GetBlue();


	float alpha = rect->GetAlpha();

	// Improve this to draw the actual sprite of the character
	graphics->DrawRectangle(left, top, right, bottom, red, green, blue, alpha, true);

}

void GameLevel::DrawCharacter()
{
	DrawRectObject(character);
}

void GameLevel::AppendStaticRectObject(RectObject *rect)
{

	bool placeValid = false;

	if (rect != nullptr)
	{
		placeValid = true;
		int* coords = RectObjectToGridCoords(*rect);
		int sizeOfCoords = 4;

		int lengthOfRect = rect->GetLength();
		int widthOfRect = rect->GetWidth();

		pixel pixelToAdd;
		pixelToAdd.occupied = true;
		pixelToAdd.color = D2D1::ColorF(rect->GetRed(), rect->GetGreen(), rect->GetBlue());

		if (coords[1] < 0)
			placeValid = false;
		if (coords[3] >= gridRows)
			placeValid = false;

		if (coords[0] < 0)
			placeValid = false;
		if (coords[2] >= gridColumns)
			placeValid = false;

		if (placeValid && !WillCollide(coords) && !RectObject::WillCollide(character, rect) )
		{
			for (int k = coords[1]; k < coords[3]; k++)
			{
				for (int j = coords[0]; j < coords[2]; j++)
					grid[k][j] = pixelToAdd;
			}

			objects.push_back(rect);
		}
	}

}

void GameLevel::AppendMoveableRectObject(RectObject* rect)
{
	moveableObjects.push_back(rect);
}

void GameLevel::ClearObjects()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects.at(i);
}


bool GameLevel::WillCollide(int *coords)
{

	// "Draw" a line trhough the grid array and check for intersectons

	for (int k = coords[1]; k < coords[3]; k++)
	{
		for (int j = coords[0]; j < coords[2]; j++)
			if (grid[k][j].occupied == true)
				return true;
	}

	return false;
}