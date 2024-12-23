#pragma once

#include "SpriteSheet.h"
#include "Graphics.h"

const float CHARACTER_MOVE_BY = 10.0f;
const float DEFAULT_TARGET_VELOCITY = 10.0f;

const float DEFAULT_MARIO_MOVEMENT_ACCELERATION = 0.5f;
const float DEFAULT_MARIO_GRAVITY_ACCELERATION = 0.01f;

const float DEFAULT_MARIO_JUMP_VELOCITY = -10.0f;

class RectObject
{

public:
	struct velocity
	{
		float current;
		float target;

		float currDir = 1.0f;
	};

private:
	float xLeft = 0;
	float xRight = xLeft + width;
	float yTop = 0;
	float yBottom = yTop + length;

	float r = 0.0f;
	float g = 0.0f;
	float b = 0.0f;
	float a = 0.0f;

	float length;
	float width;

	SpriteSheet* sprites;  

	bool moveable;

public:

	velocity xVelocity = { 0.0f, DEFAULT_TARGET_VELOCITY };
	velocity yVelocity = { 0.0f, DEFAULT_TARGET_VELOCITY };

	RectObject(float length, float width, float left, float top, bool moveable) { this->length = length; this->width = width; this->moveable = moveable; Reposition(left, top); };

	RectObject(float length, float width, float left, float top, float r, float g, float b, float a, bool moveable) : RectObject(length, width, left, top, moveable)
		{ this->r = r; this->g = g; this->b = b; this->a = a; };

	RectObject(const RectObject& obj) {
		length = obj.length; width = obj.width; xLeft = obj.xLeft; yTop = obj.yTop; moveable = obj.moveable;
		r = obj.r; g = obj.g; b = obj.b; a = obj.a; 
		xVelocity = { obj.xVelocity.current, obj.xVelocity.target, obj.xVelocity.currDir };
		yVelocity = { obj.yVelocity.current, obj.yVelocity.target, obj.yVelocity.currDir };
	};

	static bool WillCollide(RectObject *obj1, RectObject *obj2);
	bool static PointInsideRect(POINT *point, RectObject *obj);

	float GetLeft() { return xLeft; }
	float GetRight() { return xRight; }
	float GetTop() { return yTop; }
	float GetBottom() { return yBottom; }

	float GetLength() { return length; }
	float GetWidth() { return width; }

	void Reposition(float left, float top);

	float GetRed() { return r; }
	float GetBlue() { return b; }
	float GetGreen() { return g; }
	float GetAlpha() { return a; }

	bool isMoveable() { return moveable; }

	bool Load(Graphics *gfx);
	bool Draw();

	void MoveRight(int acceleration);
	void MoveLeft(int acceleration);
	void MoveDown(int acceleration);
	void MoveUp(int acceleration);
};