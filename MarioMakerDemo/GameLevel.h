#pragma once
#include "Graphics.h"
#include "SpriteSheet.h"
#include "RectObject.h"
#include "LevelEditor.h"
#include <vector>

const int DEFAULT_HEIGHT = 500;
const int DEFAULT_WIDTH = 500;

const int DEAULT_PIXEL_INTERVAL = 10;

#define DEFAULT_USER_MOVE_BY_AMOUNT 10;

#define DEFAULT_BACKGROUND D2D1::ColorF(1.0f, 1.0f, 1.0f)

struct pixel {
	bool occupied = false;
	D2D1_COLOR_F color = DEFAULT_BACKGROUND;
};

class GameLevel
{
private:
	void ShowGrid();
	void DrawRowCol(int row, int col);

	int* RectObjectToGridCoords(RectObject &obj);
protected:
	static Graphics* graphics;
	int gridRows = DEFAULT_HEIGHT / DEAULT_PIXEL_INTERVAL;
	int gridColumns = DEFAULT_WIDTH / DEAULT_PIXEL_INTERVAL;
	LevelEditor* levelEditor;

	pixel **grid;

	std::vector<RectObject*> moveableObjects;
	std::vector<RectObject*> objects;
	RectObject* character;

public:
	static D2D1_COLOR_F backgroundColor;

	void Init(Graphics* graphics, RectObject* obj, float charStartPosX, float charStartPosY, LevelEditor *editor);

	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Render() = 0;
	virtual void Update() = 0;

	void DrawGrid();
	void DrawCharacter();

	void MoveUp();
	void MoveDown();
	void MoveRight();
	void MoveLeft();

	void DrawRectObject(RectObject* rect);
	void AppendStaticRectObject(RectObject *rect);
	void AppendMoveableRectObject(RectObject* rect);
	void ClearObjects();
	bool WillCollide(int* coords);

	pixel** GetGrid() { return grid; }
};