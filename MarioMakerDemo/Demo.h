#pragma once

/*Demo.h
* Header file for the Demo class. This class inherits GameLevel and is used to model a demo for a "level1." 
*/

#include "GameLevel.h"
#include <vector>

class Demo : public GameLevel
{
private:

	// Sprites needed to be held for the level. 
	// TODO: Move these to the super class. 
	SpriteSheet* sprites;


public:

	// Demo():
	// Default Constructor, does not do anything 
	Demo() { }
	~Demo();

	// Two variables, uxerX and userY used to hold the x and y position of the main character respectively
	float userY = 0;
	float userX = 0;

	// Load():
	// Takes no parameters, used to used the inital sprite sheets
	// TODO: Make this work for the main character, but we might want to move sprite sheets into RectObject
	void Load() override;

	// Unload():
	// Hypothetical: Unloads given sprites
	// NOTE: Please see description of load.
	void Unload() override;

	// Render():
	// Uses graphics to load various objects onto the playable area.
	void Render() override;

	// Update():
	// Updates the given frame counter and/or other variables
	// NOTE: This method is unfinished and a dedicated frame counter is still needed. For purposes of the demo, this was not of priority.
	void Update() override;

	// SetMainObject(RectObject& obj):
	// Given a RectObject reference, we set the main character object of the level
	// obj: The RectObject we are setting the character to
	void SetMainObject(RectObject& obj) { character = &obj; }

};

