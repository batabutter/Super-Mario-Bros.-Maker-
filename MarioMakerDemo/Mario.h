#pragma once

#include "RectObject.h"

const float CHARACTER_MOVE_BY = 3.7f;
const float DEFAULT_TARGET_VELOCITY = 3.7f;

const float DEFAULT_MARIO_MOVEMENT_ACCELERATION = 0.5f;
const float DEFAULT_MARIO_GRAVITY_ACCELERATION = 0.01f;

const float DEFAULT_MARIO_JUMP_VELOCITY = -17.36f;

const float DEFAULT_TARGET_FREEFALL = 3.7f;

class Mario : public RectObject
{

public:
	const char* GetClassName() override { return "Mario"; }

	Mario(float length, float width, float left, float top, bool moveable) : RectObject(length, width, left, top, moveable) 
	{
		xVelocity = { 0.0f, DEFAULT_TARGET_VELOCITY };
		yVelocity = { 0.0f, DEFAULT_TARGET_VELOCITY };
	};

	Mario(float length, float width, float left, float top, float r, float g, float b, float a, bool moveable) : RectObject(length, width, left, top, r, g, b, a, moveable)
	{
		xVelocity = { 0.0f, DEFAULT_TARGET_VELOCITY };
		yVelocity = { 0.0f, DEFAULT_TARGET_VELOCITY };
	};

	Mario(const RectObject& obj) : RectObject(obj) {}

	bool MoveRight(int frame, bool holdingDown) override;
	bool MoveLeft(int frame, bool holdingDown) override;
	bool MoveDown(int frame, bool holdingDown) override;
	bool MoveUp(int frame, bool holdingDown) override;
	bool FreeFall(int frame) override;

	float CalcHorizontalSpeed(int frame, bool holdingDown, float speed);
	float CalcVerticalHighJump(int frame, bool holdingDown);

	float CalcVerticalFallSpeed(int frame);
};
