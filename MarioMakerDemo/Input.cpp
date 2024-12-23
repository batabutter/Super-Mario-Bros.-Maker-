#include "Input.h"

Input* Input::instance = nullptr;
GameLevel* Input::currLevel = nullptr;

Input::KeyboardInputMap Input::keyboard;

void Input::ProcessKeyboardInput(uint32_t VKCode, bool wasDown, bool isDown, RectObject *obj)
{
	bool successfulMove = false;
	keyboard.lastKeyPressed = VKCode;

	if (obj != nullptr)
	{

		switch (VKCode)
		{

		case VK_UP:

			keyboard.keys[DC_UP].isDown = isDown;
			keyboard.keys[DC_UP].wasDown = wasDown;

			if (keyboard.keys[DC_UP].isDown && !obj->isFalling)
			{
				keyboard.keys[DC_UP].framesReleased = 0;

				keyboard.keys[DC_UP].framesHeld++;
				successfulMove = currLevel->MoveUp(keyboard.keys[DC_UP].framesHeld, obj, keyboard.keys[DC_UP].isDown);
				keyboard.keys[DC_UP].successfulMove = successfulMove;

				if (!keyboard.keys[DC_UP].successfulMove)
					obj->isFalling = true;

			}
			else 
			{
				keyboard.keys[DC_UP].framesHeld = 0;
				obj->isFalling = true;
			}

			break;

		case VK_DOWN:
			keyboard.keys[DC_DOWN].isDown = isDown;
			keyboard.keys[DC_DOWN].wasDown = wasDown;

	
			// This should just duck tbh

			break;

		case VK_LEFT:
			keyboard.keys[DC_LEFT].isDown = isDown;
			keyboard.keys[DC_LEFT].wasDown = wasDown;

			if (keyboard.keys[DC_LEFT].isDown)
			{

				keyboard.keys[DC_LEFT].framesReleased = 0;
				keyboard.keys[DC_LEFT].framesHeld++;
				successfulMove = currLevel->MoveLeft(keyboard.keys[DC_LEFT].framesHeld, obj, keyboard.keys[DC_LEFT].isDown);

			}
			else 
			{
				keyboard.keys[DC_LEFT].framesHeld = 0;
			}

			break;

		case VK_RIGHT:

			keyboard.keys[DC_RIGHT].isDown = isDown;
			keyboard.keys[DC_RIGHT].wasDown = wasDown;

			if (keyboard.keys[DC_RIGHT].isDown)
			{
				keyboard.keys[DC_RIGHT].framesReleased = 0;
				//OutputDebugString(L"Moving right");

				keyboard.keys[DC_RIGHT].framesHeld++;
				successfulMove = currLevel->MoveRight(keyboard.keys[DC_RIGHT].framesHeld, obj, keyboard.keys[DC_RIGHT].isDown);

			}
			else 
			{
				keyboard.keys[DC_RIGHT].framesHeld = 0;
			}

			break;
		}

		// This code is a little wonky, but I can fix it later
		if (obj->xVelocity.current > 0 && !keyboard.keys[DC_RIGHT].isDown)
		{
			keyboard.keys[DC_RIGHT].framesReleased++;
			currLevel->MoveRight(keyboard.keys[DC_RIGHT].framesReleased, obj, keyboard.keys[DC_RIGHT].isDown);
		}

		if (obj->xVelocity.current < 0 && !keyboard.keys[DC_LEFT].isDown)
		{
			// Experiment with this, but I think it has a minor bug

			OutputDebugString(L"Trying to update > ");

			wchar_t charBuffer[256];

			swprintf(charBuffer, 256, L" final lvel: %f\n", obj->xVelocity.current);
			OutputDebugString(charBuffer);

			keyboard.keys[DC_LEFT].framesReleased++;
			currLevel->MoveLeft(keyboard.keys[DC_LEFT].framesReleased, obj, keyboard.keys[DC_LEFT].isDown);
		}

		if (obj->isFalling) {
			obj->timeSpentFalling++;
			successfulMove = currLevel->FreeFall(obj->timeSpentFalling++, obj);
		}

		if (!keyboard.keys[DC_DOWN].successfulMove)
		{
			keyboard.keys[DC_UP].successfulMove = true;
		}



	}


}