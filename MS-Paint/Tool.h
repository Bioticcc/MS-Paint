#pragma once

#ifndef TOOL_H
#define TOOL_H

#include <SFML/Graphics.hpp>

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
	
	//Default Constructor
	Tool() {};

	//Virtual Destructor
	virtual ~Tool() = 0;

	virtual void toolSelect(class Game& currentGame, const sf::Vector2i mousePosition) = 0;
	virtual void toolDeselect(class Game& currentGame, const sf::Vector2i mousePosition) = 0;

	virtual void mouseDown(class Game& currentGame, const sf::Vector2i mousePosition) = 0;
	virtual void mouseDrag(class Game& currentGame, const sf::Vector2i mousePosition) = 0;
	virtual void mouseUp(class Game& currentGame, const sf::Vector2i mousePosition) = 0;

};

inline Tool::~Tool() {}

#endif // !TOOL_H
