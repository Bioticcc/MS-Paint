#pragma once
#ifndef BASIC_TOOLS_H
#define BASIC_TOOLS_H

//DEBUG remove iostream
#include <iostream>

#include "Tool.h"

class SelectionTool : public Tool {
public:
	~SelectionTool() override;

	void toolSelect(class Game& currentGame) override;
	void toolUpdate(class Game& currentGame) override;
	void toolDeselect(class Game& currentGame) override;

	void mouseDown(class Game& currentGame, const sf::Vector2f mousePosition) override;
	void mouseDrag(class Game& currentGame, const sf::Vector2f mousePosition) override;
	void mouseUp(class Game& currentGame, const sf::Vector2f mousePosition) override;
};

class EraserTool : public Tool {
public:
	~EraserTool() override;

	void toolSelect(class Game& currentGame) override;
	void toolUpdate(class Game& currentGame) override;
	void toolDeselect(class Game& currentGame) override;

	void mouseDown(class Game& currentGame, const sf::Vector2f mousePosition) override;
	void mouseDrag(class Game& currentGame, const sf::Vector2f mousePosition) override;
	void mouseUp(class Game& currentGame, const sf::Vector2f mousePosition) override;
};

class PencilTool : public Tool {
public:
	~PencilTool() override;

	void toolSelect(class Game& currentGame) override;
	void toolUpdate(class Game& currentGame) override;
	void toolDeselect(class Game& currentGame) override;

	void mouseDown(class Game& currentGame, const sf::Vector2f mousePosition) override;
	void mouseDrag(class Game& currentGame, const sf::Vector2f mousePosition) override;
	void mouseUp(class Game& currentGame, const sf::Vector2f mousePosition) override;

private:
	sf::CircleShape ink;
};

#endif // !BASIC_TOOLS_H
