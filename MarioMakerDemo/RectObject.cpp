#include "RectObject.h"
#include <string>

bool RectObject::PointInsideRect(POINT *point, RectObject *rect)
{
	float pointX = point->x;
	float pointY = point->y;

	if (pointX >= rect->GetLeft() && pointX <= rect->GetRight())
		if (pointY >= rect->GetTop() && pointY <= rect->GetBottom())
			return true;

	return false;
}

bool RectObject::WillCollide(RectObject *obj1, RectObject *obj2)
{

	bool result = false;

	float left = obj2->GetLeft();
	float right = obj2->GetRight();
	float top = obj2->GetTop();
	float bottom = obj2->GetBottom();

	POINT *topLeft = new POINT();
	topLeft->x = left;
	topLeft->y = top;

	POINT* bottomLeft = new POINT();
	bottomLeft->x = left;
	bottomLeft->y = bottom;

	POINT *topRight = new POINT();
	topRight->x = right;
	topRight->y = top;

	POINT *bottomRight = new POINT();
	bottomRight->x = right;
	bottomRight->y = bottom;

	if (RectObject::PointInsideRect(topLeft, obj1) || RectObject::PointInsideRect(topRight, obj1) ||
		RectObject::PointInsideRect(bottomLeft, obj1) || RectObject::PointInsideRect(bottomRight, obj1))
		result = true;

	left = obj1->GetLeft();
	right = obj1->GetRight();
	top = obj1->GetTop();
	bottom = obj1->GetBottom();

	topLeft->x = left;
	topLeft->y = top;

	bottomLeft->x = left;
	bottomLeft->y = bottom;

	topRight->x = right;
	topRight->y = top;

	bottomRight->x = right;
	bottomRight->y = bottom;

	if (RectObject::PointInsideRect(topLeft, obj2) || RectObject::PointInsideRect(topRight, obj2) ||
		RectObject::PointInsideRect(bottomLeft, obj2) || RectObject::PointInsideRect(bottomRight, obj2))
		result = true;

	delete topLeft;
	delete bottomLeft;
	delete topRight;
	delete bottomRight;

	return result;
}

bool RectObject::Load(Graphics *gfx)
{

	sprites = new SpriteSheet(L"mario.png", gfx);

	return true;
}

bool RectObject::Draw()
{
	bool result = true;

	sprites->Draw(0, xLeft, yTop);

	return result;
}

void RectObject::MoveRight(int frame)
{
	// Fix this monstrocity
	float newVel = 0.0f;

	newVel = xVelocity.current + DEFAULT_MARIO_MOVEMENT_ACCELERATION * (float)frame;


	if (newVel > xVelocity.currDir * xVelocity.target)
		newVel = xVelocity.target;

	if (newVel < 0)
		newVel = 0;

	xVelocity.current = newVel;

	Reposition(xLeft + newVel, GetTop());

}

void RectObject::MoveLeft(int frame)
{
	float newVel = 0.0f;

	newVel = xVelocity.current - DEFAULT_MARIO_MOVEMENT_ACCELERATION * (float)frame;

	wchar_t charBuffer[256];

	swprintf(charBuffer, 256, L"newVel: %f\n", newVel);
	OutputDebugString(charBuffer);

	swprintf(charBuffer, 256, L"curr vel before : %f\n", xVelocity.current);
	OutputDebugString(charBuffer);

	// I don't like the hard code, but whatever
	if ((-1.0f) * newVel > xVelocity.target)
		newVel = (-1.0f) * xVelocity.target;

	swprintf(charBuffer, 256, L"newVel during: %f\n", newVel);
	OutputDebugString(charBuffer);

	if (newVel > 0)
		newVel = 0;
	xVelocity.current = newVel;

	swprintf(charBuffer, 256, L"curr vel after : %f\n", xVelocity.current);
	OutputDebugString(charBuffer);

	Reposition(GetLeft() + newVel, GetTop());

}
void RectObject::MoveDown(int frame)
{

	wchar_t charBuffer[256];
	float newVel = 0.0f;

	newVel = yVelocity.current + DEFAULT_MARIO_GRAVITY_ACCELERATION * (float)frame;


	if (newVel > yVelocity.currDir * yVelocity.target)
		newVel = yVelocity.target;

	yVelocity.current = newVel;

	Reposition(xLeft, GetTop() + newVel);
}
void RectObject::MoveUp(int frame)
{

	// Tweak this later, but this is just a demonstration 

	float newVel = 0.0f;

	newVel = DEFAULT_MARIO_JUMP_VELOCITY + DEFAULT_MARIO_GRAVITY_ACCELERATION * (float)frame;
	//newVel = -17.396 * pow((float)step, 2) + 15.209 * (step)+0.007;

	wchar_t charBuffer[256];


	// I don't like the hard code, but whatever

	/*
	if ((-1.0f) * newVel > yVelocity.target)
		newVel = (-1.0f) * yVelocity.target;
	*/

	
	if (newVel > 0)
	{
		newVel = 0;
	}
	
	yVelocity.current = newVel;


	Reposition(GetLeft(), GetTop() + newVel);


}

void RectObject::Reposition(float left, float top) 
{
	xLeft = left; 
	xRight = xLeft + width; 
	yTop = top; 
	yBottom = yTop + length; 

}
