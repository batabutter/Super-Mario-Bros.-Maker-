#pragma once

#include "SpriteSheet.h"

class RectObject
{

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

	RectObject(float length, float width, float left, float top, bool moveable) { this->length = length; this->width = width; this->moveable = moveable; Reposition(left, top); };

	RectObject(float length, float width, float left, float top, float r, float g, float b, float a, bool moveable) : RectObject(length, width, left, top, moveable)
		{ this->r = r; this->g = g; this->b = b; this->a = a; };

	static bool WillCollide(RectObject *obj1, RectObject *obj2);
	bool static PointInsideRect(POINT *point, RectObject *obj);

	float GetLeft() { return xLeft; }
	float GetRight() { return xRight; }
	float GetTop() { return yTop; }
	float GetBottom() { return yBottom; }

	float GetLength() { return length; }
	float GetWidth() { return length; }

	void Reposition(float left, float top) { xLeft = left; xRight = xLeft + width; yTop = top; yBottom = yTop + length; }

	float GetRed() { return r; }
	float GetBlue() { return b; }
	float GetGreen() { return g; }
	float GetAlpha() { return a; }

	bool isMoveable() { return moveable; }

};