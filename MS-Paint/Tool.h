#pragma once

#ifndef TOOL_H
#define TOOL_H

#include <SFML/Graphics.hpp>

#include "Game.h"
/*
Programmed by: Inventor4life
	Abstract Tools class that all tools are children of. Contains five methods for working with the tools.
	
	toolSelect()
	toolDeselect()

	A Game reference is included as an only argument for the below functions.
	Function Name - Called when the user:
	toolSelect    - Picks this tool
	toolUpdate    - Changes something that may affect the tool (color, size, etc...)
	toolDeselect   - Picks another tool (or this tool again)

	A Game reference and mouse position are included as arguments for the below functions.
	Function Name - Called when the mouse is:
	mouseDown()   - Clicked on canvas
	mouseDrag()   - Moved while the button is held down
	mouseMotion() - Called whenever the mouse is moved and on the canvas.
	mouseUp()     - Released

	UPGRADE:
		Replace virtual functions with default versions (like the PencilTool versions.)
		This will allow us to write less code for similar brushes, and not deal with 
		 abstract bullshittery.
*/
class Tool
{
public:
	
	//Default Constructor
	Tool() {};

	//Virtual Destructor
	virtual ~Tool() = 0;

	virtual void toolSelect(class Game& currentGame) = 0;
	virtual void toolUpdate(class Game& currentGame) = 0;
	virtual void toolDeselect(class Game& currentGame) = 0;

	virtual void mouseDown(class Game& currentGame, const sf::Vector2f mousePosition) = 0;
	virtual void mouseDrag(class Game& currentGame, const sf::Vector2f mousePosition) = 0;
	virtual void mouseMotion(class Game& currentGame, const sf::Vector2f mousePosition) = 0;
	virtual void mouseUp(class Game& currentGame, const sf::Vector2f mousePosition) = 0;

	bool in_use = false;

};

inline Tool::~Tool() {}

#endif // !TOOL_H
