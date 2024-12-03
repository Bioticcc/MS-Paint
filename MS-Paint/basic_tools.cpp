#include "basic_tools.h"

SelectionTool::~SelectionTool()
{
}

void SelectionTool::toolSelect(Game& currentGame)
{
}

void SelectionTool::toolUpdate(Game& currentGame)
{
}

void SelectionTool::toolDeselect(Game& currentGame)
{
}

void SelectionTool::mouseDown(Game& currentGame, const sf::Vector2f mousePosition)
{
}

void SelectionTool::mouseDrag(Game& currentGame, const sf::Vector2f mousePosition)
{
}

void SelectionTool::mouseUp(Game& currentGame, const sf::Vector2f mousePosition)
{
}

EraserTool::~EraserTool()
{
}

void EraserTool::toolSelect(Game& currentGame)
{
}

void EraserTool::toolUpdate(Game& currentGame)
{
}

void EraserTool::toolDeselect(Game& currentGame)
{
}

void EraserTool::mouseDown(Game& currentGame, const sf::Vector2f mousePosition)
{
}

void EraserTool::mouseDrag(Game& currentGame, const sf::Vector2f mousePosition)
{
}

void EraserTool::mouseUp(Game& currentGame, const sf::Vector2f mousePosition)
{
}

PencilTool::~PencilTool()
{
}

void PencilTool::toolSelect(Game& currentGame)
{
	
}

void PencilTool::toolUpdate(Game& currentGame)
{
	//ink.setRadius(currentGame.)
}

void PencilTool::toolDeselect(Game& currentGame)
{
}

void PencilTool::mouseDown(Game& currentGame, const sf::Vector2f mousePosition)
{
	
}

void PencilTool::mouseDrag(Game& currentGame, const sf::Vector2f mousePosition)
{
	//DEBUG - remove
	std::cout << "PencilTool Drag!";
}

void PencilTool::mouseUp(Game& currentGame, const sf::Vector2f mousePosition)
{
	//DEBUG - remove
	std::cout << "PencilTool Up!";
}
