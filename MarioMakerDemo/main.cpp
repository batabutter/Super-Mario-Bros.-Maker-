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
* Ensure you are linking to hte d2d1 library
*
*/
static float xStart = 256.0f;
static float yStart = 256.0f;

// Creating mario 
static RectObject *character = new RectObject(32.0f, 24.0f, 64.0f, 64.0f, 0.0f, 1.0f, 0.0f, 1.0f, true);

static RectObject *block = new RectObject(100.0f, 100.0f, 80.0f, 50.0f, 0.0f, 0.0f, 0.0f, 1.0f, false);
static Demo *level1 = new Demo();

// Create singleton LevelEditor
static LevelEditor *levelEditor = LevelEditor::GetInstance();

// Create singleton Input handler

Graphics* graphics;

static bool wasDown = false;
static bool isDown = false;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, int nCmdShow)
{
	const wchar_t* CLASS_NAME = L"Window";

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
		L"Mario Maker Demo",    // Window text
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

	/* Recreate this. This is so messy and all the window creating fuctions make it really hard to know where and what to edit
	*/

	float myFloat = character->GetRight();

	graphics = new Graphics();

	if (!graphics->Init(windowHandle)) {
		delete graphics;
		return -1;
	}

	// This is dumb, stupid and ugly. 
	level1->Init(graphics, character, xStart, yStart, levelEditor);

	//level1->AppendStaticRectObject(block);


	// Initialize the level editor and the input

	levelEditor->Init(graphics);
	Input::Init(level1);


	ShowWindow(windowHandle, nCmdShow);

	// Call the GameController which calls the level's load functions
	GameController::LoadInitialLevel(level1);

	MSG message = {};
	message.message = WM_NULL;

	// Peeks messages so the program isn't constatnly waiting for input
	while (message.message != WM_QUIT)
	{
		auto now = std::chrono::high_resolution_clock::now();

		auto lastUpdate = std::chrono::high_resolution_clock::now();

		auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUpdate);

		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{

			DispatchMessage(&message);
		}

		while (deltaTime.count() <= 16.0f)
		{

			Input::ProcessKeyboardInput(Input::keyboard.lastKeyPressed, wasDown, isDown, level1->GetCharacter());

			GameController::Update();
			graphics->BeginDraw();
			GameController::Render();
			graphics->EndDraw();

			now = std::chrono::high_resolution_clock::now();
			deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUpdate);
		}


		if (isDown)
			OutputDebugString(L"IsDown");

		/*
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			DispatchMessage(&message);
		}
		else
		{
			GameController::Update();
			graphics->BeginDraw();
			GameController::Render();
			graphics->EndDraw();
		}
		*/

		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

	delete graphics;
	
	/*
	
	// Make sure to delete the rest of the stuff
	
	*/

	return 0;
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

		levelEditor->FreeSelectedObject();
		break;

	case WM_LBUTTONDOWN:
		
		ptInitialClick.x = GET_X_LPARAM(lParam);
		ptInitialClick.y = GET_Y_LPARAM(lParam);
		SetCapture(hwnd);

		levelEditor->ProcessMouseInput(ptInitialClick.x, ptInitialClick.y);
		break;


	case WM_MOUSEMOVE:

		POINT ptCurrent;
		ptCurrent.x = GET_X_LPARAM(lParam);
		ptCurrent.y = GET_Y_LPARAM(lParam);


		// Note:: This is kind of a band-aid fix and I don't like it. Freeing and reassigning to bullptr is stupid, but I will fix this later. 
		if (DragDetect(hwnd, ptCurrent)) {
			levelEditor->ProcessMouseInput(ptCurrent.x, ptCurrent.y);
		}
		else {

			// You would need to do this every time per demo. I want to rewrite this windproc function to make the calls way more modular
			level1->AppendStaticRectObject(levelEditor->GetSelectedObject());
			levelEditor->FreeSelectedObject();
		}



		break;
	
	case WM_SYSKEYDOWN:
	case WM_KEYDOWN:
	case WM_SYSKEYUP:
	case WM_KEYUP:
	{
		// These operators use the properties of lParam and how the bits are ordered.
		wasDown = (lParam & (1 << 30)) != 0;
		isDown = (lParam & (1 << 31)) == 0;

		uint32_t VKCode = wParam;
		Input::keyboard.lastKeyPressed = VKCode;

		break;
	}
	

	}


	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}