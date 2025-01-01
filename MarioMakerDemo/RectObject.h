#pragma once

#include "SpriteSheet.h"
#include "Graphics.h"

namespace RectObjectData
{

	class RectObject;

	// The default background color of the grid will be white for now
	#define DEFAULT_BACKGROUND D2D1::ColorF(0.572f, 0.564f, 1.0f)
	/* pixel
	* Abstract representation of a pixel. Stores an rgb value and if it is current "occupied," basically if it is either the background or not.
	*/
	struct pixel
	{
		RectObject* obj = nullptr;
		D2D1_COLOR_F color = DEFAULT_BACKGROUND;

	};

	enum MOVEMENTDIR
	{
		UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3
	};

	class RectObject
	{

	public:

		virtual const char* GetClassName() { return "RectObject"; }

		struct velocity
		{
			float current;
			float target;

			float currDir = 1.0f;

		};

	protected:
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

		SpriteSheet* sprites = nullptr;

		bool moveable;


	public:

		velocity xVelocity = { 0.0f, 0.0f };
		velocity yVelocity = { 0.0f, 0.0f };

		bool isFalling = false;
		int timeSpentFalling = 0;

		RectObject(float length, float width, float left, float top, bool moveable)
		{
			this->length = length; this->width = width; this->moveable = moveable; Reposition(left, top);
		};

		RectObject(float length, float width, float left, float top, float r, float g, float b, float a, bool moveable) : RectObject(length, width, left, top, moveable)
		{
			this->r = r; this->g = g; this->b = b; this->a = a;
		};

		RectObject(const RectObject& obj) {
			length = obj.length; width = obj.width; xLeft = obj.xLeft; yTop = obj.yTop; moveable = obj.moveable;
			r = obj.r; g = obj.g; b = obj.b; a = obj.a;
			xVelocity = { obj.xVelocity.current, obj.xVelocity.target, obj.xVelocity.currDir };
			yVelocity = { obj.yVelocity.current, obj.yVelocity.target, obj.yVelocity.currDir };
		};

		static bool WillCollide(RectObject* obj1, RectObject* obj2);
		bool static PointInsideRect(POINT* point, RectObject* obj);

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

		virtual bool Update() { return true; };
		bool Load(Graphics* gfx, const wchar_t* spriteFilename);
		bool Unload();
		bool Draw();


		virtual bool MoveRight(int frame, bool holdingDown) { return false; };
		virtual bool MoveLeft(int frame, bool holdingDown) { return false; };
		virtual bool MoveDown(int frame, bool holdingDown) { return false; };
		virtual bool MoveUp(int frame, bool holdingDown) { return false; };

		virtual bool FreeFall(int frame) { return false; };

		virtual bool CollisionHandler(RectObject *obj, MOVEMENTDIR direction) { return false; };
	};
}
