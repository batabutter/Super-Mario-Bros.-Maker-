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

			if (keyboard.keys[DC_UP].isDown && keyboard.keys[DC_UP].wasDown)
			{
				keyboard.keys[DC_UP].framesHeld++;
				successfulMove = currLevel->MoveUp(keyboard.keys[DC_UP].framesHeld, obj);
				keyboard.keys[DC_UP].successfulMove = successfulMove;

				if (!successfulMove)
				{
					keyboard.keys[DC_DOWN].framesHeld = 0;
					keyboard.keys[DC_DOWN].successfulMove = true;
				}
				else
				{
					return;
				}
			}
			else
			{

				keyboard.keys[DC_UP].framesHeld = 0;


				keyboard.keys[DC_DOWN].successfulMove = true;
				keyboard.keys[DC_DOWN].framesHeld++;
				currLevel->MoveDown(keyboard.keys[DC_DOWN].framesHeld, obj);
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
				keyboard.keys[DC_LEFT].framesHeld++;
				successfulMove = currLevel->MoveLeft(keyboard.keys[DC_LEFT].framesHeld, obj);

				return;
			}
			else 
			{
				keyboard.keys[DC_RIGHT].framesHeld = 0;
			}

			break;

		case VK_RIGHT:

			keyboard.keys[DC_RIGHT].isDown = isDown;
			keyboard.keys[DC_RIGHT].wasDown = wasDown;

			if (keyboard.keys[DC_RIGHT].isDown)
			{
				//OutputDebugString(L"Moving right");

				keyboard.keys[DC_RIGHT].framesHeld++;
				successfulMove = currLevel->MoveRight(keyboard.keys[DC_RIGHT].framesHeld, obj);

				return;
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
			//obj->MoveRight(-2.5f);
			currLevel->MoveRight(-2.5f, obj);
		}

		if (obj->xVelocity.current < 0 && !keyboard.keys[DC_LEFT].isDown)
		{
			// Experiment with this, but I think it has a minor bug
			currLevel->MoveLeft(-2.5f, obj);
		}

		if (!keyboard.keys[DC_UP].isDown && keyboard.keys[DC_DOWN].successfulMove) {
			keyboard.keys[DC_DOWN].framesHeld++;
			successfulMove = currLevel->MoveDown(keyboard.keys[DC_DOWN].framesHeld, obj);
			keyboard.keys[DC_DOWN].successfulMove = successfulMove;
		}

		if (!keyboard.keys[DC_DOWN].successfulMove)
		{
			keyboard.keys[DC_UP].successfulMove = true;
		}



	}


}