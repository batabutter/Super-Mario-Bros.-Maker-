#include "RectObject.h"

bool RectObject::PointInsideRect(POINT *point, RectObject *rect)
{
	float pointX = point->x;
	float pointY = point->y;

	if (pointX >= rect->GetLeft() && pointX <= rect->GetRight())
		if (pointY >= rect->GetTop() && pointY <= rect->GetBottom())
			return true;

	return false;
}

bool RectObject::WillCollide(RectObject *obj1, RectObject *obj2)
{

	bool result = false;

	float left = obj2->GetLeft();
	float right = obj2->GetRight();
	float top = obj2->GetTop();
	float bottom = obj2->GetBottom();

	POINT *topLeft = new POINT();
	topLeft->x = left;
	topLeft->y = top;

	POINT* bottomLeft = new POINT();
	bottomLeft->x = left;
	bottomLeft->y = bottom;

	POINT *topRight = new POINT();
	topRight->x = right;
	topRight->y = top;

	POINT *bottomRight = new POINT();
	bottomRight->x = right;
	bottomRight->y = bottom;

	if (RectObject::PointInsideRect(topLeft, obj1) || RectObject::PointInsideRect(topRight, obj1) ||
		RectObject::PointInsideRect(bottomLeft, obj1) || RectObject::PointInsideRect(bottomRight, obj1))
		result = true;

	left = obj1->GetLeft();
	right = obj1->GetRight();
	top = obj1->GetTop();
	bottom = obj1->GetBottom();

	topLeft->x = left;
	topLeft->y = top;

	bottomLeft->x = left;
	bottomLeft->y = bottom;

	topRight->x = right;
	topRight->y = top;

	bottomRight->x = right;
	bottomRight->y = bottom;

	if (RectObject::PointInsideRect(topLeft, obj2) || RectObject::PointInsideRect(topRight, obj2) ||
		RectObject::PointInsideRect(bottomLeft, obj2) || RectObject::PointInsideRect(bottomRight, obj2))
		result = true;

	delete topLeft;
	delete bottomLeft;
	delete topRight;
	delete bottomRight;

	return result;
}