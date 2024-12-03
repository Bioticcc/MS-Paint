#include "basic_tools.h"

PencilTool::~PencilTool() {}

void PencilTool::toolSelect(Game& currentGame, const sf::Vector2i mousePosition) {}

void PencilTool::toolDeselect(Game& currentGame, const sf::Vector2i mousePosition) {}

void PencilTool::mouseDown(Game& currentGame, const sf::Vector2i mousePosition) {}

void PencilTool::mouseDrag(Game& currentGame, const sf::Vector2i mousePosition) {}

void PencilTool::mouseUp(Game& currentGame, const sf::Vector2i mousePosition) {}

EraserTool::~EraserTool() {}

void EraserTool::toolSelect(Game& currentGame, const sf::Vector2i mousePosition) {}

void EraserTool::toolDeselect(Game& currentGame, const sf::Vector2i mousePosition) {}

void EraserTool::mouseDown(Game& currentGame, const sf::Vector2i mousePosition) {}

void EraserTool::mouseDrag(Game& currentGame, const sf::Vector2i mousePosition) {}

void EraserTool::mouseUp(Game& currentGame, const sf::Vector2i mousePosition) {}

SelectionTool::~SelectionTool() {}

void SelectionTool::toolSelect(Game& currentGame, const sf::Vector2i mousePosition) {}

void SelectionTool::toolDeselect(Game& currentGame, const sf::Vector2i mousePosition) {}

void SelectionTool::mouseDown(Game& currentGame, const sf::Vector2i mousePosition) {}

void SelectionTool::mouseDrag(Game& currentGame, const sf::Vector2i mousePosition) {}

void SelectionTool::mouseUp(Game& currentGame, const sf::Vector2i mousePosition) {}
