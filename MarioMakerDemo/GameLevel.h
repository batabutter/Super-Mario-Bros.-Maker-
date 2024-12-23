#pragma once
#include "Graphics.h"
#include "SpriteSheet.h"
#include "RectObject.h"
#include "LevelEditor.h"
#include <vector>

/* GameLevel.h:
* Stores all of the needed information for a level in the game. It holds the grid, and lists of objects that need to be drawn.
* TODO: Make it so you can move and remove objects from the board, add functionality for other moveable objects, etc.
*/

// Default height and width for the grid. VERY SUBJECT TO CHANGE
const int DEFAULT_HEIGHT = 512;
const int DEFAULT_WIDTH = 512;

// The amount of pixels from segment to segment of the grid
const int DEAULT_PIXEL_INTERVAL = 16;

// The default background color of the grid will be white for now
#define DEFAULT_BACKGROUND D2D1::ColorF(0.572f, 0.564f, 1.0f)

/* pixel
* Abstract representation of a pixel. Stores an rgb value and if it is current "occupied," basically if it is either the background or not.
*/
struct pixel 
{
	bool occupied = false;
	D2D1_COLOR_F color = DEFAULT_BACKGROUND;
};

class GameLevel
{
private:

	// ShowGrid():
	// This method draws the visual lines that are represented on the grid onto the window.
	// TODO: Make the naming convention less confusing
	void ShowGrid();

	// DrawRowCol(int row, int col):
	// Given a row and a column, we draw it's grid position onto the window
	// row: Row of the grid position
	// col: Column of the grid position
	void DrawRowCol(int row, int col);

	// RectObjectToGridCoords(RectObject &obj):
	// Given a RectObject reference, we give the corresponding locations as if it we mapped onto a grid
	// obj: The object to find the coordinates of
	int* RectObjectToGridCoords(RectObject &obj);

protected:

	// Reference to the grraphics object we will use to draw to the window
	static Graphics* graphics;

	// rows and column sizes of the grid array
	int gridRows = DEFAULT_HEIGHT / DEAULT_PIXEL_INTERVAL;
	int gridColumns = DEFAULT_WIDTH / DEAULT_PIXEL_INTERVAL;

	// Reference to the singleton level editor that will be used to place objects into the game area
	LevelEditor* levelEditor;

	// The grid of pixels we use to draw many of the objects
	pixel **grid;

	// Lists of all the moveable and nonmoveable objects to be drawn, eventually
	std::vector<RectObject*> moveableObjects;
	std::vector<RectObject*> objects;

	// Reference to the current player object
	RectObject* character;

	// //Sprite (image) of the map itself 
	SpriteSheet* map;

public:

	// Background color of the window
	static D2D1_COLOR_F backgroundColor;

	// Init(Graphics* graphics, RectObject* obj, float charStartPosX, float charStartPosY, LevelEditor *editor):
	// Initializes the grpahics pointer, the character, the character's start position, and the pointer to the level editor
	void Init(Graphics* graphics, RectObject* obj, float charStartPosX, float charStartPosY, LevelEditor *editor);

	// Load():
	// Loads the images for the objecrts (sprites)
	virtual void Load() = 0;

	// Unload():
	// Unloads all the sprites for the objects
	virtual void Unload() = 0;

	// Render():
	// Draws objects to the current window as needed
	virtual void Render() = 0;

	// Update():
	// Updates the level, used to handle changes in logic
	virtual void Update() = 0;

	// DrawGrid():
	// Draws the grid from the rows and columns storing the pixel data.
	// TODO: Rename from confusing naming convention
	void DrawGrid();
	
	// DrawCharacter():
	// Draws the playable character onto the window
	void DrawCharacter();

	// MoveUp():
	bool MoveUp(int framesHeld, RectObject *obj);

	// MoveDown():
	bool MoveDown(int framesHeld, RectObject* obj);

	// MoveRight():
	bool MoveRight(int framesHeld, RectObject* obj);

	// MoveLeft():
	bool MoveLeft(int framesHeld, RectObject* obj);

	// DrawRectObject(RectObject* rect):
	// Given a RectObject, we simply draw it onto the window
	// rect: The object to be drawn
	void DrawRectObject(RectObject* rect);

	// AppendStaticRectObject(RectObject *rect):
	// Given a RectObject that is not intended to move, we store it onto the grid and append it to the list of objects
	// rect: The object to append
	void AppendStaticRectObject(RectObject *rect);

	// AppendMoveableRectObject(RectObject* rect):
	// Given a RectObject, we append the object to the list of moveable rect objects, i.e., ones that will not be stapled to the grid.
	// rect: The object to append
	void AppendMoveableRectObject(RectObject* rect);

	// ClearObjects():
	// Clears both lists of moveable and immoveable objects
	// TODO: Clear the character too, handle other memory leaks
	void ClearObjects();

	// WillCollide(int* coords):
	// Given coordinates, we check if the coordinates collide with any prexisting spot in the grid. If so, return true, else, return false.
	// coords: The coords we comapre to the coords on the grid
	bool WillCollide(int* coords);

	// GetGrid():
	// Returns a reference to this level's grid object
	pixel** GetGrid() { return grid; }

	RectObject* GetCharacter() { return character; }
};