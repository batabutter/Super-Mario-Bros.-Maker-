#pragma once

#include "GameLevel.h"
#include <vector>

class Demo : public GameLevel
{
private:
	float yIncrement = 0.0f;
	float xIncrement = 0.0f;

	int frame;

	// Specific to level 1
	SpriteSheet* sprites;


public:

	Demo() { }
	~Demo();

	float userY = 0;
	float userX = 0;
	void Load() override;
	void Unload() override;
	void Render() override;
	void Update() override;

	void SetMainObject(RectObject& obj) { character = &obj; }

};

