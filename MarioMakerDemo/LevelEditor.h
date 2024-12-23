#pragma once

#include "RectObject.h"
#include "Graphics.h"
#include <vector>

class LevelEditor
{

private:
	LevelEditor() {};

	// Because you initalize this outside of a class, you do not want to delete graphics inside this class
	static Graphics* graphics;
	static LevelEditor *instance;

	bool isObjectSelected;
	bool mouseDown;
	RectObject *currentSelectedObject = nullptr;

	std::vector<RectObject*> builderObjects; 
	
	RectObject* RectObjectClickedOn(float xPos, float yPos);

public:
	
	LevelEditor(const LevelEditor&) = delete;
	LevelEditor& operator=(const LevelEditor&) = delete;

	// Rework this
	~LevelEditor() {  }

	void Init(Graphics* gfx);
	static LevelEditor* GetInstance() { if (instance == nullptr) instance = new LevelEditor(); return instance; }

	void CreateBuildInterface();
	void ProcessMouseInput(float xPos, float yPos);

	RectObject* GetSelectedObject() { return currentSelectedObject; }
	void FreeSelectedObject() { if (currentSelectedObject != nullptr) delete currentSelectedObject; currentSelectedObject = nullptr; };

};