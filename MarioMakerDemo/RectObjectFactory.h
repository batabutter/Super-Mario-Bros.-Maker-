#pragma once
#include "RectObject.h"
#include "Mario.h"
#include <typeinfo>
#include <string>

class RectObjectFactory
{

	RectObjectFactory();

public:

	RectObjectFactory(const RectObjectFactory&) = delete;
	RectObjectFactory& operator=(const RectObjectFactory&) = delete;

	static RectObject* CreateNewRectObject(const char* classname, float length, float width, float left, float top, bool moveable)
	{
		if (strcmp("Mario", classname) == 0)
			return new Mario(length, width, left, top, moveable);
		else if (strcmp("RectObject", classname) == 0)
			return new RectObject(length, width, left, top, moveable);
		return nullptr;
	}

	static RectObject* CreateNewRectObject(const char* classname, float length, float width, float left, float top, float r, float g, float b, float a, bool moveable)
	{
		if (strcmp("Mario", classname) == 0)
			return new Mario(length, width, left, top, r, g, b, a, moveable);

		else if (strcmp("RectObject", classname) == 0)
			return new RectObject(length, width, left, top, r, g, b, a, moveable);
		return nullptr;
	}

	static RectObject* CreateNewRectObject(RectObject* obj)
	{
		if (obj == nullptr)
			return nullptr;


		RectObject* result = nullptr;

		const char * typeClass = obj->GetClassName();

		if (strcmp(typeClass, "Mario") == 0)
			result = new Mario(*obj);
		else if (strcmp(typeClass, "RectObject") == 0)
			result = new RectObject(*obj);

		return result;
	}

};