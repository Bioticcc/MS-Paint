#pragma once
#ifndef BASIC_TOOLS_H
#define BASIC_TOOLS_H

#define _USE_MATH_DEFINES
#include <math.h>

#include "Tool.h"

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

// Just a white pencil
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
