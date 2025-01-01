#include "Mario.h"
#include <string>

float Mario::CalcHorizontalSpeed(int frame, bool holdingDown, float currSpeed)
{
	float newVel = 0.0f;
	if (holdingDown)
	{
		// 9.091t + 0.039

		newVel = 9.091f * ((float)frame / 60.0f) + 2.039;


		if (newVel > xVelocity.target)
			newVel = xVelocity.target;

	}
	else {

		newVel = -5.091f * ((float)frame / 60.0f) + currSpeed;

		if (newVel < 0)
			newVel = 0.0f;

	}

	return newVel;

}

float Mario::CalcVerticalHighJump(int frame, bool holdingDown)
{
	float newSpeed = 0.0f;
	float t = ((float)frame / 60.0f);
	if (holdingDown)
	{
		// -17.396x^{2}+15.209x\ +0.007

		newSpeed = -17.396 * pow(t, 2) + 15.209*t + 2.007;

	}
	else {

		newSpeed = 0.0f;

	}

	return newSpeed;

}

bool Mario::MoveRight(int frame, bool holdingDown)
{

	bool result = true;
	// Fix this monstrocity
	float newVel = CalcHorizontalSpeed(frame, holdingDown, xVelocity.current);
	xVelocity.current = newVel;
	Reposition(xLeft + newVel, GetTop());

	// Change this
	//isFalling = true;

	return result;
}

bool Mario::MoveLeft(int frame, bool holdingDown)
{
	bool result = true;
	// Fix this monstrocity
	float newVel = CalcHorizontalSpeed(frame, holdingDown, (-1.0f) * xVelocity.current);
	xVelocity.current = (-1.0f) *newVel;
	Reposition(xLeft + xVelocity.current, GetTop());

	// Change this
	//isFalling = true;

	return result;
}

bool Mario::MoveDown(int frame, bool holdingDown)
{
	bool result = true;

	wchar_t charBuffer[256];
	float newVel = 0.0f;

	newVel = yVelocity.current + DEFAULT_MARIO_GRAVITY_ACCELERATION * (float)frame;


	if (newVel > yVelocity.currDir * yVelocity.target)
		newVel = yVelocity.target;

	yVelocity.current = newVel;

	Reposition(xLeft, GetTop() + newVel);

	return result;
}

bool Mario::MoveUp(int frame, bool holdingDown)
{
	bool result = true;
	// Fix this monstrocity
	float newVel = CalcVerticalHighJump(frame, holdingDown);
	yVelocity.current = newVel;

	if (newVel >= 0)
	{
		yVelocity.current = newVel;
	}
	else
	{
		result = false;
		yVelocity.current = 0.0f;
		isFalling = true;
	}

	Reposition(xLeft + xVelocity.current, GetTop() - newVel);

	return result;
}

bool Mario::FreeFall(int frame)
{
	bool result = true;


	float prevSpeed = yVelocity.current;
	float calc = CalcVerticalFallSpeed(frame);
	float newVel = 0.0f;


	if (calc <= 0)
		newVel = 0;
	else
	{
		newVel = prevSpeed + CalcVerticalFallSpeed(frame);
		yVelocity.current = newVel;
	}
	Reposition(xLeft, GetTop() + newVel);

	return result;

}

float Mario::CalcVerticalFallSpeed(int frame)
{
	//-27.940t^2 - 1.057t + 2.477

	float speed = 0.0f;

	float t = (float)frame / 60;

	speed = -87.940 * pow(t, 2) - 1.057 * t + 2.477;

	return speed;
}


// CollisionHandler(RectObject* obj)
// Given a RectObject, we check if the object collides with another object. If so, we handle the collision. There may be more paramterds we should pass in the future, 
// but for now this works
bool Mario::CollisionHandler(RectObject* obj, MOVEMENTDIR dir)
{

	switch (dir)
	{
	case RIGHT:
		// This is a BANDAID FIX. I will probably have to come up with a better solution later
		Reposition(obj->GetLeft() - GetWidth() - 1, GetTop());
		xVelocity.current = 0.0f;
		break;
	case LEFT:
		Reposition(obj->GetRight(), GetTop());
		xVelocity.current = 0.0f;
		break;
	case DOWN:
		Reposition(xLeft, obj->GetTop() - GetLength());
		yVelocity.current = 0.0f;
		break;

	case UP:
		Reposition(xLeft, obj->GetBottom());
		yVelocity.current = 0.0f;
		break;
	}

	return true;
}

bool Mario::Update()
{

	return true;
}