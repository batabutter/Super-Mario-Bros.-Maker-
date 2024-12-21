#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(const wchar_t* filename, Graphics* graphics)
{
	this->graphics = graphics;	// initalize the graphics 
	bmp = NULL;		// Null bitmap to start
	HRESULT result;	// Check for errors during initialization.

	// Create a WIC factory, research what the methods do
	IWICImagingFactory* wicFactory = NULL;

	result = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory, // Reference to interface that communicates with the object
		((LPVOID*)&wicFactory)); // Pointer that contains our facotry

	// Create a decoder
	IWICBitmapDecoder* wicDecoder = NULL;
	result = wicFactory->CreateDecoderFromFilename(
		filename, // Name of the file to be read
		NULL, // Use deault vendors
		GENERIC_READ, // Reading the file, not writing
		WICDecodeMetadataCacheOnLoad, // We aren't caching anything, dump later
		&wicDecoder); // Decoder we are making

	// Reading the frame from the image >
	IWICBitmapFrameDecode* wicFrame = NULL;
	result = wicDecoder->GetFrame(0, &wicFrame); // store in the frame

	// Now we create a converter to convert WIC to ID2D1Bitmap

	IWICFormatConverter* wicConverter = NULL;
	result = wicFactory->CreateFormatConverter(&wicConverter);

	// Use the converter to convert the WICBitmap to D2D1Bitmap

	result = wicConverter->Initialize(
		wicFrame,	// Frame
		GUID_WICPixelFormat32bppPBGRA, // Pixel format
		WICBitmapDitherTypeNone,	// Irrelevant
		NULL,	// No palette
		0.0,	// Alpha transparency
		WICBitmapPaletteTypeCustom); // Also irrelevant


	// Use the convertered to create a D2D1Bitmap
	graphics->GetRenderTarget()->CreateBitmapFromWicBitmap(
		wicConverter, // Take the wicConverter before
		NULL,
		&bmp); // Use the graphics to create a bmp from the converter

	if (wicFactory) wicFactory->Release();
	if (wicDecoder) wicDecoder->Release();
	if (wicConverter) wicConverter->Release();
	if (wicFrame) wicFrame->Release();


	spriteWidth = bmp->GetSize().width;
	spriteHeight = bmp->GetSize().height;
	spritesAcross = 1;
}

SpriteSheet::SpriteSheet(const wchar_t* filename, Graphics* graphics, int spriteWidth, int spriteHeight) : SpriteSheet(filename, graphics)
{
	this->spriteWidth = spriteWidth;
	this->spriteHeight = spriteWidth;
	spritesAcross = (int)bmp->GetSize().width / spriteWidth;
}

SpriteSheet::~SpriteSheet()
{
	if (bmp)
		bmp->Release();
}

void SpriteSheet::Draw()
{
	graphics->GetRenderTarget()->DrawBitmap(
		bmp, // Our bitmap
		D2D1::RectF(0.0f, 0.0f,
			bmp->GetSize().width, bmp->GetSize().height), // Determine where the recange will be put
		1.0f, // Opacity
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, // Deals with stretching or shrinking
		D2D1::RectF(0.0f, 0.0f,
			bmp->GetSize().width, bmp->GetSize().height)); // Create a rectangle that holds the bmp with the size of the bmp;


}

void SpriteSheet::Draw(int index, int x, int y)
{
	// Create a rectangle from tehe sprite sheet
	D2D_RECT_F src = D2D1::RectF(
		(float)(index % spritesAcross) * spriteWidth,
		(float)(index / spritesAcross) * spriteHeight,
		(float)(index % spritesAcross) * spriteWidth + spriteWidth,
		(float)(index / spritesAcross) * spriteHeight + spriteHeight);

	// Create a destination recxtangle to determine where to show on the screen
	D2D_RECT_F dest = D2D1::RectF(
		x, y,
		x + spriteWidth,
		y + spriteHeight);

	graphics->GetRenderTarget()->DrawBitmap(
		bmp, // Our bitmap
		dest, // Create a rectangle that holds the bmp with the size of the bmp
		1.0f, // Opacity
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, // Deals with stretching or shrinking
		src);

}