#include "LevelEditor.h"

Graphics* LevelEditor::graphics = nullptr;
LevelEditor* LevelEditor::instance = nullptr;

void LevelEditor::CreateBuildInterface()
{
	RectObject *curr;
	// Start by loading all the placeable objects
	for (int i = 0; i < builderObjects.size(); i++)
	{
		curr = builderObjects.at(i);
		graphics->DrawRectangle(curr->GetLeft(), curr->GetTop(), curr->GetRight(), curr->GetBottom(), curr->GetRed(), curr->GetGreen(), curr->GetBlue(), curr->GetAlpha(), true);
	}

	if (currentSelectedObject != nullptr)
		graphics->DrawRectangle(
			currentSelectedObject->GetLeft(), currentSelectedObject->GetTop(), currentSelectedObject->GetRight(), currentSelectedObject->GetBottom(),
			currentSelectedObject->GetRed(), currentSelectedObject->GetGreen(),
			currentSelectedObject->GetBlue(), currentSelectedObject->GetAlpha(), true);
}

// Use this method to load all of hte placeable objects in the game 
void LevelEditor::Init(Graphics *gfx)
{
	graphics = gfx; 

	RectObject* squareBasic = new RectObject(100, 100, 600, 50, 1.0f, 0.0f, 0.0f, 1.0f, false);

	builderObjects.push_back(squareBasic);

}

void LevelEditor::ProcessMouseInput(float xPos, float yPos)
{
	
	RectObject* obj = nullptr;

	if (currentSelectedObject == nullptr)
	{
		obj = RectObjectClickedOn(xPos, yPos);

		if (obj != nullptr)
		{
			currentSelectedObject = new RectObject(
				obj->GetLength(), obj->GetWidth(),
				obj->GetLeft(), obj->GetTop(),
				obj->GetRed(), obj->GetGreen(), obj->GetBlue(),
				obj->GetAlpha() * 0.25f, obj->isMoveable());
		}
		else
			return;
	}
	else
	{

		/* Make this code neater for the love of god
		*/

		RectObject* ghostObject = currentSelectedObject;

		ghostObject->Reposition(xPos, yPos);

		float left = ghostObject->GetLeft();
		float top = ghostObject->GetTop();

		// Draws the object in the middle of the mouse cursor
		float offsetX = left - (currentSelectedObject->GetWidth() / 2.0f);
		float offsetY = top - (currentSelectedObject->GetLength() / 2.0f);

		ghostObject->Reposition(offsetX, offsetY);

		float right = ghostObject->GetRight();
		float bottom = ghostObject->GetBottom();


		// If an object was clicked on, draw the object onto the current mouse position
		//graphics->DrawRectangle(0, 0, 100, 100, 1.0f, 0.0f, 0.0f, 1.0f, true);
		//graphics->DrawRectangle(left, top, right, bottom, ghostObject->GetRed(), ghostObject->GetGreen(), ghostObject->GetBlue(), ghostObject->GetAlpha(), true);

		currentSelectedObject = ghostObject;
	}
}

RectObject* LevelEditor::RectObjectClickedOn(float xPos, float yPos)
{
	RectObject* curr = nullptr;

	for (int i = 0; i < builderObjects.size(); i++)
	{
		curr = builderObjects.at(i);

		if (xPos >= curr->GetLeft() && xPos <= curr->GetRight())
		{
			if (yPos >= curr->GetTop() && yPos <= curr->GetBottom())
			{
				return curr;
			}
		}
	}

	return nullptr;
}