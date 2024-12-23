#include "GameLevel.h"
#include <string>

Graphics* GameLevel::graphics;

// Initalize the background
D2D1_COLOR_F GameLevel::backgroundColor = DEFAULT_BACKGROUND;

void GameLevel::Init(Graphics* graphics, RectObject* obj, float charStartPosX, float charStartPosY, LevelEditor *editor)
{
	// Intialize the member varaibles
	GameLevel::graphics = graphics;
	character = *&obj;
	levelEditor = editor;

	// Create a 2D array of pixel structs
	grid = new pixel*[DEFAULT_WIDTH / DEAULT_PIXEL_INTERVAL];


	for (int i = 0; i < DEFAULT_WIDTH / DEAULT_PIXEL_INTERVAL; i++)
		grid[i] = new pixel[DEFAULT_HEIGHT / DEAULT_PIXEL_INTERVAL];

	// Reposition the character at it's starting position
	// TODO: The rectobject now holds a stating position. This code needs to be reworked
	character->Reposition(charStartPosX, charStartPosY);

}

void GameLevel::ShowGrid()
{
	float gridHeight = DEFAULT_HEIGHT;
	float gridWidth = DEFAULT_WIDTH;
	float pixelInterval = DEAULT_PIXEL_INTERVAL;
	for (int i = 0; i < (gridWidth / pixelInterval); i++)
	{

		// Draws all the lines that outline each box of the grid
		graphics->DrawLine(0, (i * pixelInterval), gridWidth, (i * pixelInterval), 1.0f, 0.0f, 0.0f, 0.5f);
		graphics->DrawLine((i * pixelInterval), 0, (i * pixelInterval), gridHeight, 1.0f, 0.0f, 0.0f, 0.5f);
	}

}

void GameLevel::DrawGrid()
{
	
	// Loop through the grid array and draw each row and collumn
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
	// Convert the grid integer positionst to find out where to draw the starting and ending pixels
	float pixelPosLeft = ((float) row * DEAULT_PIXEL_INTERVAL);
	float pixelPosTop = ((float) col * DEAULT_PIXEL_INTERVAL);
	float pixelPosRight = pixelPosLeft + (float) DEAULT_PIXEL_INTERVAL;
	float pixelPosBottom = pixelPosTop + (float) DEAULT_PIXEL_INTERVAL;

	// ??? I don't know why it doesn't work when flipped, but I am too lazy to care -> "grid[col][row]"?
	// NOTE: Rename the variables and fix later.
	// Get the colors of the cube
	float red = grid[col][row].color.r;
	float green = grid[col][row].color.g;
	float blue = grid[col][row].color.b;
	float alpha = grid[col][row].color.a;

	// Draw the cube [ ] 
	graphics->DrawRectangle(pixelPosLeft, pixelPosTop, pixelPosRight, pixelPosBottom, red, green, blue, alpha, true);

}

int* GameLevel::RectObjectToGridCoords(RectObject &obj)
{
	float left = obj.GetLeft();
	float right = obj.GetRight();
	float top = obj.GetTop();
	float bottom = obj.GetBottom();

	/* The corresponding array positions for the coords array are -> 
	* Coords[0] = left
	* Coords[1] = top
	* Coords[2] = right
	* Coords[3] = bottom
	*/

	// Create the array
	int *coords = new int[4]{ (int) (left/ DEAULT_PIXEL_INTERVAL), (int)(top / DEAULT_PIXEL_INTERVAL), (int)(right / DEAULT_PIXEL_INTERVAL), (int)(bottom / DEAULT_PIXEL_INTERVAL) };

	return coords;
}

// TODO: These "move" methods does not check for any moveable objects. Overall functionality for those is extremley lacking > 
/*
* THESE METHODS ARE SO REPETITIVE, FIX THIS ASAP. 
* Literally just add a copy constructor
*/
bool GameLevel::MoveUp(int framesHeld, RectObject* obj, bool holdingDown)
{
	bool canMoveUp = true;
	canMoveUp = obj->MoveUp(framesHeld, holdingDown);


	return canMoveUp;
}

bool GameLevel::MoveDown(int framesHeld, RectObject* obj, bool holdingDown)
{

	bool result = false;
	RectObject* temp = RectObjectFactory::CreateNewRectObject(obj);

	temp->MoveDown(framesHeld, holdingDown);

	/*
	wchar_t charBuffer[256];

	swprintf(charBuffer, 256, L"tempvel: %f\n", temp->yVelocity.current);
	OutputDebugString(charBuffer);

	swprintf(charBuffer, 256, L"obj vel before: %f\n", obj->yVelocity.current);
	OutputDebugString(charBuffer);

	*/


	//int* coords = RectObjectToGridCoords(*temp);
	//coords[2] = coords[2] + 1;

	if (temp->GetBottom() < DEFAULT_HEIGHT)
	{
		obj->Reposition(temp->GetLeft(), temp->GetTop());
		obj->yVelocity.current = temp->yVelocity.current;
		result = true;
	}
	else {
		obj->Reposition(temp->GetLeft(), DEFAULT_HEIGHT - temp->GetLength());
		obj->yVelocity.current = 0;
	}

	/*
	swprintf(charBuffer, 256, L"obj vel after: %f\n", obj->yVelocity.current);
	OutputDebugString(charBuffer);
	*/

	delete temp;
	//delete[] coords;

	/*
	swprintf(charBuffer, 256, L"final: %f\n", obj->yVelocity.current);
	OutputDebugString(charBuffer);
	*/
	return result;
}

bool GameLevel::MoveLeft(int framesHeld, RectObject* obj, bool holdingDown)
{


	/*
	bool result = false;
	RectObject* temp = RectObjectFactory::CreateNewRectObject(obj);

	temp->MoveRight(framesHeld, holdingDown);

	//int* coords = RectObjectToGridCoords(*temp);
	//coords[2] = coords[2] + 1;

	wchar_t charBuffer[256];

	if (temp->GetRight() < DEFAULT_WIDTH)
	{
		obj->Reposition(temp->GetLeft(), temp->GetTop());
		obj->xVelocity.current = temp->xVelocity.current;
		result = true;
	}
	else {
		obj->Reposition(DEFAULT_WIDTH - temp->GetWidth(), temp->GetTop());
		obj->xVelocity.current = 0;
	}

	delete temp;
	//delete[] coords;

	
	return result;
}
	*/
	bool result = false;
	RectObject* temp = RectObjectFactory::CreateNewRectObject(obj);

	temp->MoveLeft(framesHeld, holdingDown);

	wchar_t charBuffer[256];

	swprintf(charBuffer, 256, L"tempvel: %f\n", temp->xVelocity.current);
	//OutputDebugString(charBuffer);

	swprintf(charBuffer, 256, L"obj vel before: %f\n", obj->xVelocity.current);
	//OutputDebugString(charBuffer);


	//int* coords = RectObjectToGridCoords(*temp);
	//coords[2] = coords[2] + 1;

	if (temp->GetLeft() > 0)
	{
		obj->Reposition(temp->GetLeft(), temp->GetTop());
		obj->xVelocity.current = temp->xVelocity.current;
		result = true;
	}
	else {
		obj->Reposition(0, obj->GetTop());
		obj->xVelocity.current = 0;
	}

	swprintf(charBuffer, 256, L"obj vel after: %f\n", obj->xVelocity.current);
	//OutputDebugString(charBuffer);

	delete temp;
	//delete[] coords;

	swprintf(charBuffer, 256, L"final: %f\n", obj->xVelocity.current);
	//OutputDebugString(charBuffer);

	return result;
}

bool GameLevel::MoveRight(int framesHeld, RectObject* obj, bool holdingDown)
{

	bool result = false;
	RectObject* temp = RectObjectFactory::CreateNewRectObject(obj);

	temp->MoveRight(framesHeld, holdingDown);

	//int* coords = RectObjectToGridCoords(*temp);
	//coords[2] = coords[2] + 1;

	wchar_t charBuffer[256];

	if (temp->GetRight() < DEFAULT_WIDTH)
	{
		obj->Reposition(temp->GetLeft(), temp->GetTop());
		obj->xVelocity.current = temp->xVelocity.current;
		result = true;
	}
	else {
		obj->Reposition(DEFAULT_WIDTH - temp->GetWidth(), temp->GetTop());
		obj->xVelocity.current = 0;
	}

	delete temp;
	//delete[] coords;

	
	return result;
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

	// use the coorindates to draw the object
	// TODO: Improve this to draw the actual sprite of the character
	graphics->DrawRectangle(left, top, right, bottom, red, green, blue, alpha, true);

	rect->Draw();
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

bool GameLevel::FreeFall(int framesHeld, RectObject* obj)
{

	bool result = false;
	RectObject* temp = RectObjectFactory::CreateNewRectObject(obj);

	temp->FreeFall(framesHeld);

	if (temp->GetBottom() < DEFAULT_HEIGHT)
	{
		obj->Reposition(temp->GetLeft(), temp->GetTop());
		obj->yVelocity.current = temp->yVelocity.current;
		result = true;
	}
	else {

		// This logic needs an overhaul when I work on collisions
		obj->Reposition(temp->GetLeft(), DEFAULT_HEIGHT - temp->GetLength());

		obj->isFalling = false;
		obj->timeSpentFalling = 0;

		result = false;
	}

	delete temp;


	return result;

}