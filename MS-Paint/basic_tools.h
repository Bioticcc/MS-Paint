#pragma once
#ifndef BASIC_TOOLS_H
#define BASIC_TOOLS_H
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Assignment: PA9
// File: basic_tools.h
// Description:
// Declares various tool classes (SelectionTool, EraserTool, PencilTool, EyeDropper) 
// which inherit from Tool and implement different canvas interactions.
//
//
#define _USE_MATH_DEFINES
#include <math.h>

#include "Tool.h"
//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Class: SelectionTool
// Parameters: None
// Return Values: None (class definition)
// Description:
// A tool that handles selecting elements on the canvas (currently minimal functionality).
//
//
class SelectionTool : public Tool {
public:
	~SelectionTool() override;

	void toolSelect(class Game& currentGame) override;
	void toolUpdate(class Game& currentGame) override;
	void toolDeselect(class Game& currentGame) override;

	void mouseDown(class Game& currentGame, const sf::Vector2f mousePosition) override;
	void mouseDrag(class Game& currentGame, const sf::Vector2f mousePosition) override;
	void mouseMotion(class Game& currentGame, const sf::Vector2f mousePosition) override;
	void mouseUp(class Game& currentGame, const sf::Vector2f mousePosition) override;
};

//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Class: EraserTool
// Parameters: None
// Return Values: None (class definition)
// Description:
// A tool that simulates an eraser by drawing white shapes over the canvas.
// It changes the drawn pixels to appear erased.
//
//
class EraserTool : public Tool {
public:
	~EraserTool() override;

	void toolSelect(class Game& currentGame) override;
	void toolUpdate(class Game& currentGame) override;
	void toolDeselect(class Game& currentGame) override;

	void mouseDown(class Game& currentGame, const sf::Vector2f mousePosition) override;
	void mouseDrag(class Game& currentGame, const sf::Vector2f mousePosition) override;
	void mouseMotion(class Game& currentGame, const sf::Vector2f mousePosition) override;
	void mouseUp(class Game& currentGame, const sf::Vector2f mousePosition) override;

private:
	sf::CircleShape dot;
	sf::RectangleShape line;
	sf::CircleShape sizeIndicator;
	sf::Vector2f lastPosition;
};
//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Class: PencilTool
// Parameters: None
// Return Values: None (class definition)
// Description:
// A tool that draws colored lines on the canvas, simulating a pencil stroke.
//
class PencilTool : public Tool {
public:
	~PencilTool() override;

	void toolSelect(class Game& currentGame) override;
	void toolUpdate(class Game& currentGame) override;
	void toolDeselect(class Game& currentGame) override;

	void mouseDown(class Game& currentGame, const sf::Vector2f mousePosition) override;
	void mouseDrag(class Game& currentGame, const sf::Vector2f mousePosition) override;
	void mouseMotion(class Game& currentGame, const sf::Vector2f mousePosition) override;
	void mouseUp(class Game& currentGame, const sf::Vector2f mousePosition) override;

	sf::CircleShape getDot();
private:
	sf::CircleShape dot; // displayed on mousedown and after lines, adds rounded corners to rectangles
	sf::RectangleShape line; // The lines connecting the dots, with thickness of 2x brush size
	sf::CircleShape sizeIndicator; // Thin black circle outline for showing brush size.
	sf::Vector2f lastPosition; // Used to determine where the rectangle should extend to.
};
//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Class: EyeDropper
// Parameters: None
// Return Values: None (class definition)
// Description:
// A tool that picks a color from the canvas pixels under the cursor.
//
class EyeDropper : public Tool {
public:
	~EyeDropper() override;

	void toolSelect(class Game& currentGame) override;
	void toolUpdate(class Game& currentGame) override;
	void toolDeselect(class Game& currentGame) override;

	void mouseDown(class Game& currentGame, const sf::Vector2f mousePosition) override;
	void mouseDrag(class Game& currentGame, const sf::Vector2f mousePosition) override;
	void mouseMotion(class Game& currentGame, const sf::Vector2f mousePosition) override;
	void mouseUp(class Game& currentGame, const sf::Vector2f mousePosition) override;

private:
	sf::CircleShape colorIndicator;
};

#endif // !BASIC_TOOLS_H
