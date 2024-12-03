#pragma once
#ifndef BASIC_TOOLS_H
#define BASIC_TOOLS_H

#include "Tool.h"

class SelectionTool : public Tool {
public:
	~SelectionTool() override;

	void toolSelect(class Game& currentGame, const sf::Vector2i mousePosition) override;
	void toolDeselect(class Game& currentGame, const sf::Vector2i mousePosition) override;

	void mouseDown(class Game& currentGame, const sf::Vector2i mousePosition) override;
	void mouseDrag(class Game& currentGame, const sf::Vector2i mousePosition) override;
	void mouseUp(class Game& currentGame, const sf::Vector2i mousePosition) override;
};

class EraserTool : public Tool {
public:
	~EraserTool() override;

	void toolSelect(class Game& currentGame, const sf::Vector2i mousePosition) override;
	void toolDeselect(class Game& currentGame, const sf::Vector2i mousePosition) override;

	void mouseDown(class Game& currentGame, const sf::Vector2i mousePosition) override;
	void mouseDrag(class Game& currentGame, const sf::Vector2i mousePosition) override;
	void mouseUp(class Game& currentGame, const sf::Vector2i mousePosition) override;
};

class PencilTool : public Tool {
public:
	~PencilTool() override;

	void toolSelect(class Game& currentGame, const sf::Vector2i mousePosition) override;
	void toolDeselect(class Game& currentGame, const sf::Vector2i mousePosition) override;

	void mouseDown(class Game& currentGame, const sf::Vector2i mousePosition) override;
	void mouseDrag(class Game& currentGame, const sf::Vector2i mousePosition) override;
	void mouseUp(class Game& currentGame, const sf::Vector2i mousePosition) override;
};

#endif // !BASIC_TOOLS_H
