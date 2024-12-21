#include "Graphics.h"


// Graphics():
// Sets default values to null
Graphics::Graphics()
{
	factory = NULL;
	renderTarget = NULL;
}

Graphics::~Graphics()
{
	if (factory != NULL)
		factory->Release();
	if (renderTarget != NULL)
		renderTarget->Release();
}

bool Graphics::Init(HWND windowHandle)
{

	// If result goes through, sets the factory as a new type of single threaded factory
	HRESULT result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	if (result != S_OK)
		return false;

	RECT rect = {};

	// Sets the rect to the dimensions of the window handle
	GetClientRect(windowHandle, &rect);

	// If the result goes through, it sets the renderTarget pointer to a new renderTarget using the factory's methods
	result = factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(), // Use default properties
		D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)),
		&renderTarget
	);
	if (result != S_OK)
		return false;



	return true;
}

void Graphics::ClearScreen(float r, float g, float b)
{
	renderTarget->Clear(D2D1::ColorF(r, g, b));

}

void Graphics::DrawCircle(
	float x, float y,
	float radius,
	float r, float g, float b,
	float a)
{
	ID2D1SolidColorBrush* brush;
	renderTarget->CreateSolidColorBrush(D2D1::ColorF(r, g, b, a), &brush);

	renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush, 3.0f);

	brush->Release();

}
void Graphics::DrawLine(float x1, float y1, float x2, float y2, float r, float g, float b, float a)
{
	ID2D1SolidColorBrush* brush;
	renderTarget->CreateSolidColorBrush(D2D1::ColorF(r, g, b, a), &brush);

	D2D1_POINT_2F start;
	start.x = x1;
	start.y = y1;

	D2D1_POINT_2F end;
	end.x = x2;
	end.y = y2;

	renderTarget->DrawLine(start, end, brush, 1.0f);

	brush->Release();


}

void Graphics::DrawRectangle(float x1, float y1, float x2, float y2, float r, float g, float b, float a, bool fill)
{

	ID2D1SolidColorBrush* brush;
	renderTarget->CreateSolidColorBrush(D2D1::ColorF(r, g, b, a), &brush);

	D2D1_RECT_F rect;
	rect.left = x1;
	rect.top = y1;
	rect.right = x2;
	rect.bottom = y2;

	if (!fill)
		renderTarget->DrawRectangle(rect, brush, 1.0f);
	else
		renderTarget->FillRectangle(rect, brush);

	brush->Release();

}
