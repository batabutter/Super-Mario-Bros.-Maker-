#pragma once

#include <windows.h>
#include <d2d1.h>

/* Graphics.h
* Wrapper class that simplifies the drawing proceudres on a window.
*/

class Graphics
{

private:
	// Factory used to create graphics resources
	ID2D1Factory* factory;

	// Tells you where you are rendering to
	ID2D1HwndRenderTarget* renderTarget;

public:

	Graphics();
	~Graphics();

	bool Init(HWND windowHandle);

	ID2D1RenderTarget* GetRenderTarget() { return renderTarget; }

	// Begins drawing for the renderTarget
	void BeginDraw() { renderTarget->BeginDraw(); }
	//In order to properly update, call this function when you finiah drawing.
	void EndDraw() { renderTarget->EndDraw(); }

	// Use the color to color the screen
	void ClearScreen(float r, float g, float b);

	void DrawCircle(float x, float y, float radius, float r, float g, float b, float a);
	void DrawLine(float x1, float y1, float x2, float y2, float r, float g, float b, float a);
	void DrawRectangle(float x1, float y1, float x2, float y2, float r, float g, float b, float a, bool fill);

};