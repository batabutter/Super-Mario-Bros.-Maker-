#pragma once


/* SpriteSheet.h
* I am too lazy to document this right now. This shit is insanely complex. If you have further questions, please visit Microsoft's websites that host documentation
*/

#include <wincodec.h> // Header for creating a WIC factory and reading image files from disk
#include "Graphics.h" 


class SpriteSheet
{
private:
	Graphics* graphics; // Reference to the graphics class
	ID2D1Bitmap* bmp;	// Bitmap. Loaded file that is converted

	int spriteWidth, spriteHeight;
	int spritesAcross;

public:

	// Constructor that initializes the member variables, reads files, and converts to the bitmaps
	SpriteSheet(const wchar_t* filename, Graphics* graphics);
	SpriteSheet(const wchar_t* filename, Graphics* graphics, int spriteWidth, int spriteHeight);

	// Delete the bitmap
	~SpriteSheet();

	// Draw the bitmap to the render target
	void Draw();
	void Draw(int index, int x, int y);

};