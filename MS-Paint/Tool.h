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
	Function Name - Called when:
	toolSelect    - When the user picks this tool
	toolUpdate    - When the user changes something that may affect the tool (color, size, etc...)
	toolDeselect  - When the user picks a different (or identical) tool.

	A Game reference and mouse position are included as arguments for the below functions.
	Function Name - Called when the mouse is:
	mouseDown()   - Clicked on canvas
	mouseDrag()   - Moved while the button is held down
	mouseUp()     - Released
*/
class Tool
{
public:
	
	//Default Constructor
	Tool() {};

	//Virtual Destructor
	virtual ~Tool() = 0;

	virtual void toolSelect(Game& currentGame) = 0;
	virtual void toolUpdate(Game& currentGame) = 0;
	virtual void toolDeselect(Game& currentGame) = 0;

	virtual void mouseDown(Game& currentGame, const sf::Vector2f mousePosition) = 0;
	virtual void mouseDrag(Game& currentGame, const sf::Vector2f mousePosition) = 0;
	virtual void mouseUp(Game& currentGame, const sf::Vector2f mousePosition) = 0;

	bool in_use = false;

};

inline Tool::~Tool() {}

#endif // !TOOL_H
