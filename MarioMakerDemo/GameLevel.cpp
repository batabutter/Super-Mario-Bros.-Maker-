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
	int *coords = new int[4]{ 
		(int) (floor(left/ DEAULT_PIXEL_INTERVAL)), 
			(int)(floor(top / DEAULT_PIXEL_INTERVAL)), 
			(int)(ceil(right / DEAULT_PIXEL_INTERVAL)), 
			(int)(ceil(bottom / DEAULT_PIXEL_INTERVAL)) };


	return coords;
}

// TODO: These "move" methods does not check for any moveable objects. Overall functionality for those is extremley lacking > 
/*
* THESE METHODS ARE SO REPETITIVE, FIX THIS ASAP. 
* Literally just add a copy constructor
*/
bool GameLevel::MoveUp(int framesHeld, RectObject* obj, bool holdingDown)
{

	wchar_t charBuffer[256];
	swprintf_s(charBuffer, sizeof(charBuffer) / sizeof(wchar_t), L"Inside gamelevel before >: %f\n", obj->GetBottom());
	OutputDebugString(charBuffer);
	RectObject* temp = RectObjectFactory::CreateNewRectObject(obj);
	bool result = true;



	result = temp->MoveUp(framesHeld, holdingDown);

	CollisionCheckerLoop(temp, obj);

	if (!result)
		OutputDebugString(L"Move up failed\n");

	if (temp->isFalling)
		OutputDebugString(L"falling in temp\n");

	swprintf_s(charBuffer, sizeof(charBuffer) / sizeof(wchar_t), L"Inside gamelevel after >: %f\n", obj->GetBottom());
	OutputDebugString(charBuffer);

	return result;
}

bool GameLevel::MoveDown(int framesHeld, RectObject* obj, bool holdingDown)
{

	bool result = false;
	RectObject* temp = RectObjectFactory::CreateNewRectObject(obj);

	result = temp->MoveDown(framesHeld, holdingDown);

	delete temp;

	return result;
}

bool GameLevel::MoveLeft(int framesHeld, RectObject* obj, bool holdingDown)
{
	bool result = false;
	RectObject* temp = RectObjectFactory::CreateNewRectObject(obj);

	result = temp->MoveLeft(framesHeld, holdingDown);

	CollisionCheckerLoop(temp, obj);

	delete temp;
	return result;
}

bool GameLevel::MoveRight(int framesHeld, RectObject* obj, bool holdingDown)
{
	bool result = false;
	RectObject* temp = RectObjectFactory::CreateNewRectObject(obj);

	result = temp->MoveRight(framesHeld, holdingDown);
	CollisionCheckerLoop(temp, obj);

	delete temp;
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
		pixelToAdd.obj = rect;
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

// Overhaul or change in the future

bool GameLevel::WillCollide(int *coords)
{

	// "Draw" a line trhough the grid array and check for intersectons

	for (int k = coords[1]; k < coords[3]; k++)
	{
		for (int j = coords[0]; j < coords[2]; j++)
			if (grid[k][j].obj != nullptr)
				return true;
	}

	return false;
}

bool GameLevel::FreeFall(int framesHeld, RectObject* obj)
{

	wchar_t charBuffer[256];

	bool result = false;
	RectObject* temp = RectObjectFactory::CreateNewRectObject(obj);

	// Create the projection of where the object will move to 
	temp->FreeFall(framesHeld);

	int gridBottom = floor(temp->GetBottom() / DEAULT_PIXEL_INTERVAL);


	if (gridBottom < gridColumns)
	{
		CollisionCheckerLoop(temp, obj);
		/**
		wchar_t charBuffer[256];
		//swprintf_s(buffer, sizeof(buffer) / sizeof(wchar_t), L"Float value: %.2f\n", value);
		swprintf_s(charBuffer, sizeof(charBuffer) / sizeof(wchar_t), L"Temp left>: %.2f\n", temp->GetLeft());
		OutputDebugString(charBuffer);

		*/
	}
	else 
	{
		// This logic needs an overhaul when I work on collisions
		obj->Reposition(temp->GetLeft(), DEFAULT_HEIGHT - temp->GetLength());

		obj->isFalling = false;
		obj->timeSpentFalling = 0;

		result = false;
	}

	delete temp;

	return result;

}

void GameLevel::CollisionCheckerLoop(RectObject* temp, RectObject *original)
{

	wchar_t charBuffer[256];
	//swprintf_s(buffer, sizeof(buffer) / sizeof(wchar_t), L"Float value: %.2f\n", value);

	RectObject* collidingObj = nullptr;
	int oldLeftPos = floor(original->GetLeft() / DEAULT_PIXEL_INTERVAL);
	int oldRightPos = floor(original->GetRight() / DEAULT_PIXEL_INTERVAL);
	int oldBottom = floor(original->GetBottom() / DEAULT_PIXEL_INTERVAL);
	int oldTop = floor(original->GetTop() / DEAULT_PIXEL_INTERVAL);

	int newLeftPos = floor(temp->GetLeft() / DEAULT_PIXEL_INTERVAL);
	int newRightPos = floor(temp->GetRight() / DEAULT_PIXEL_INTERVAL);
	int newBottom = floor(temp->GetBottom() / DEAULT_PIXEL_INTERVAL);
	int newTop = floor(temp->GetTop() / DEAULT_PIXEL_INTERVAL);

	float newXVel = temp->GetLeft() + temp->xVelocity.current;
	float newYVel = temp->GetTop() - temp->yVelocity.current;


	// I don't like this and I think it needs to be changed. I don't like having the adjustion check once
	bool adjustion = false;

	if (newBottom >= gridColumns)
		// Band-aid fix
		newBottom = newBottom - 1;

	// First, check the horizontal movement based off the xVelocity and adjust accordingly

	// If the object is moving right
	swprintf_s(charBuffer, sizeof(charBuffer) / sizeof(wchar_t), L"right location of original>: %d\n", oldRightPos);
	OutputDebugString(charBuffer);


	// I don't like this logic flow
	if (temp->GetLeft() >= 0 && (temp->GetRight() < DEFAULT_WIDTH) && !adjustion)
	{

		if (temp->xVelocity.current > 0)
		{

			if (grid[newTop][newRightPos].obj != nullptr)
			{
				collidingObj = grid[newTop][newRightPos].obj;
			}
			else if (grid[newBottom][newRightPos].obj != nullptr)
			{

				collidingObj = grid[newBottom][newRightPos].obj;
			}

			if (collidingObj != nullptr)
			{
				swprintf_s(charBuffer, sizeof(charBuffer) / sizeof(wchar_t), L"left location of obj>: %f\n", floor(collidingObj->GetLeft() / DEAULT_PIXEL_INTERVAL));
				OutputDebugString(charBuffer);
			}

			if (collidingObj != nullptr && (oldRightPos <= floor(collidingObj->GetLeft() / DEAULT_PIXEL_INTERVAL)))
			{
				temp->CollisionHandler(collidingObj, MOVEMENTDIR::RIGHT);
				adjustion = true;
			}
		}
		// If the object is moving left
		else if (temp->xVelocity.current < 0)
		{
			if (grid[newTop][newLeftPos].obj != nullptr)
			{
				collidingObj = grid[newTop][newLeftPos].obj;
			}
			else if (grid[newBottom][newLeftPos].obj != nullptr)
			{
				collidingObj = grid[newBottom][newLeftPos].obj;
			}

			if (collidingObj != nullptr && (oldLeftPos >= floor(collidingObj->GetRight() / DEAULT_PIXEL_INTERVAL)))
			{
				temp->CollisionHandler(collidingObj, MOVEMENTDIR::LEFT);
				adjustion = true;
			}
		}
	}
	else 
	{
		if (temp->GetRight() >= DEFAULT_WIDTH)
		{
			temp->Reposition(DEFAULT_WIDTH - temp->GetWidth(), temp->GetTop());
			temp->xVelocity.current = 0;

			// Band-aid fix
			newRightPos = (int)floor(temp->GetRight() / DEAULT_PIXEL_INTERVAL) - 1;
		}
		else if (temp->GetLeft() < 0)
		{

			temp->Reposition(0, temp->GetTop());
			temp->xVelocity.current = 0;
		}
			
	}

	if (!adjustion)
	{
		// Next, check the vertical movement based off the yVelocity and adjust accordingly

		if (temp->yVelocity.current > 0)
		{
			if (grid[newTop][newLeftPos].obj != nullptr)
			{
				collidingObj = grid[newTop][newLeftPos].obj;
			}
			else if (grid[newTop][newRightPos].obj != nullptr)
			{
				collidingObj = grid[newTop][newRightPos].obj;
			}

			if (collidingObj != nullptr)
			{
				temp->CollisionHandler(collidingObj, MOVEMENTDIR::UP);
				adjustion = true;
			}

		}
		else if (temp->yVelocity.current < 0)
		{

			if (grid[newBottom][newLeftPos].obj != nullptr)
			{
				collidingObj = grid[newBottom][newLeftPos].obj;
			}
			else if (grid[newBottom][newRightPos].obj != nullptr)
			{
				collidingObj = grid[newBottom][newRightPos].obj;
			}

			if (collidingObj != nullptr)
			{

				temp->CollisionHandler(collidingObj, MOVEMENTDIR::DOWN);
				//temp->isFalling = false;
				temp->timeSpentFalling = 0;
				adjustion = true;
			}
			else {
				temp->isFalling = true;
			}

		}

	}

	original->Reposition(temp->GetLeft(), temp->GetTop());
	original->xVelocity.current = temp->xVelocity.current;
	original->yVelocity.current = temp->yVelocity.current;
	original->isFalling = temp->isFalling;
	original->timeSpentFalling = temp->timeSpentFalling;
}