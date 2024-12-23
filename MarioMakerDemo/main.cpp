#include <windows.h>
#include <d2d1_1.h>
#include "Graphics.h"
#include "Demo.h"
#include "GameController.h"
#include "RectObject.h"
#include <windowsx.h>
#include "LevelEditor.h"
#include "Input.h"

#include <chrono>
#include <thread>

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 800

/* main.cpp
* Make sure to check the imported libraries within the Solution's directory if any copies of code are made.
*/
static Demo* level1 = new Demo();
static GameController* game = GameController::GetInstance();

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, int nCmdShow)
{
	const wchar_t* CLASS_NAME = L"Window";

	const wchar_t* GAME_NAME = L"Mario Maker Demo";

	WNDCLASS wc = { };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	RECT rect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	HWND windowHandle = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		GAME_NAME,    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);

	if (windowHandle == NULL)
		return -1;


	MSG message = {};
	message.message = WM_NULL;

	int result = 1;

	ShowWindow(windowHandle, nCmdShow);

	result = GameController::Init(windowHandle);

	if (result == -1)
		return -1;

	GameController::LoadInitialLevel(level1);

	while (message.message != WM_QUIT)
	{

		result = game->UpdateGame();

		if (result == -1)
			return result;

		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			DispatchMessage(&message);
		}

	}


	GameController::GetInstance()->~GameController();

	return result;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	static POINT ptInitialClick;

	switch (uMsg)
	{

	case (WM_DESTROY):

		PostQuitMessage(0);
		return 0;
		break;

	case WM_LBUTTONUP:

		ReleaseCapture();

		//levelEditor->FreeSelectedObject();
		break;

	case WM_LBUTTONDOWN:
		
		ptInitialClick.x = GET_X_LPARAM(lParam);
		ptInitialClick.y = GET_Y_LPARAM(lParam);
		SetCapture(hwnd);

		//levelEditor->ProcessMouseInput(ptInitialClick.x, ptInitialClick.y);
		break;


	case WM_MOUSEMOVE:

		POINT ptCurrent;
		ptCurrent.x = GET_X_LPARAM(lParam);
		ptCurrent.y = GET_Y_LPARAM(lParam);


		// Old Code. Rewrite this when you have the time

		/*

		// Note:: This is kind of a band-aid fix and I don't like it. Freeing and reassigning to bullptr is stupid, but I will fix this later. 
		if (DragDetect(hwnd, ptCurrent)) {
			levelEditor->ProcessMouseInput(ptCurrent.x, ptCurrent.y);
		}
		else {

			// You would need to do this every time per demo. I want to rewrite this windproc function to make the calls way more modular
			level1->AppendStaticRectObject(levelEditor->GetSelectedObject());
			levelEditor->FreeSelectedObject();
		}
		*/

		break;
	
	case WM_SYSKEYDOWN:
	case WM_KEYDOWN:
	case WM_SYSKEYUP:
	case WM_KEYUP:
	{
		// These operators use the properties of lParam and how the bits are ordered.
		GameController::wasKeyDown = (lParam & (1 << 30)) != 0;
		GameController::isKeyDown = (lParam & (1 << 31)) == 0;

		uint32_t VKCode = wParam;
		Input::keyboard.lastKeyPressed = VKCode;

		break;
	}

	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}