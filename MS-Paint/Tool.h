#pragma once

#ifndef TOOL_H
#define TOOL_H

#include <SFML/Graphics.hpp>

#include "Game.h"

/*
Programmed by: Ethan Goode
	Abstract Tools class that all tools are children of. Contains five methods for working with the tools.
	
	toolSelect()
	toolDeselect()

	A Game pointer and mouse position are included as arguments for the below functions.
	Function Name - Called when the mouse is:
	mouseDown()   - Clicked on canvas
	mouseDrag()   - Moved while the button is held down
	mouseUp()     - Released
*/
class Tool
{
public:
	virtual ~Tool() = 0;

	virtual void toolSelect(Game& currentGame, const sf::Vector2i mousePosition) = 0;
	virtual void toolDeselect(Game& currentGame, const sf::Vector2i mousePosition) = 0;

	virtual void mouseDown(Game& currentGame, const sf::Vector2i mousePosition) = 0;
	virtual void mouseDrag(Game& currentGame, const sf::Vector2i mousePosition) = 0;
	virtual void mouseUp(Game& currentGame, const sf::Vector2i mousePosition) = 0;

};

#endif // !TOOL_H
