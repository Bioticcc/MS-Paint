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

void SelectionTool::mouseMotion(Game& currentGame, const sf::Vector2f mousePosition)
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
	dot.setRadius((float)currentGame.brushSize);
	dot.setFillColor(sf::Color::White);
	dot.setOrigin(dot.getRadius(), dot.getRadius());

	sizeIndicator.setRadius((float)currentGame.brushSize);
	sizeIndicator.setFillColor(sf::Color::Transparent);
	sizeIndicator.setOutlineColor(sf::Color::Black);
	sizeIndicator.setOutlineThickness(1.0);
	sizeIndicator.setOrigin(dot.getRadius(), dot.getRadius());

	line.setFillColor(sf::Color::White);
}

void EraserTool::toolUpdate(Game& currentGame)
{
	dot.setRadius((float)currentGame.brushSize);
	dot.setOrigin(dot.getRadius(), dot.getRadius());

	sizeIndicator.setRadius((float)currentGame.brushSize);
	sizeIndicator.setOrigin(dot.getRadius(), dot.getRadius());
}

void EraserTool::toolDeselect(Game& currentGame)
{
}

void EraserTool::mouseDown(Game& currentGame, const sf::Vector2f mousePosition)
{
	dot.setPosition(mousePosition);
	currentGame.drawToCanvas(dot);
	lastPosition = mousePosition;
}

void EraserTool::mouseDrag(Game& currentGame, const sf::Vector2f mousePosition)
{
	sf::Vector2f delta = (lastPosition - mousePosition);
	float length = std::sqrt(delta.x * delta.x + delta.y * delta.y);
	if (length == 0) return;
	sf::Vector2f size(length, currentGame.brushSize * (float)2.0);
	line.setSize(size);
	line.setOrigin(0, (float)currentGame.brushSize);
	if (delta.x == 0) {
		line.setRotation((float)90.0 * ((delta.y > 0) ? 1 : -1));
		//std::cout << line.getRotation(); lots of numbers on console
	}
	else {
		line.setRotation(std::atan2f(delta.y, delta.x) * 180 / (float)M_PI);
	}

	line.setPosition(mousePosition);
	currentGame.drawToCanvas(line);

	dot.setPosition(mousePosition);
	currentGame.drawToCanvas(dot);
	lastPosition = mousePosition;
}

void EraserTool::mouseMotion(Game& currentGame, const sf::Vector2f mousePosition)
{
	sizeIndicator.setPosition(mousePosition);
	currentGame.getWindowReference().draw(sizeIndicator);
}

void EraserTool::mouseUp(Game& currentGame, const sf::Vector2f mousePosition)
{
}

PencilTool::~PencilTool()
{
}

void PencilTool::toolSelect(Game& currentGame)
{
	dot.setRadius((float)currentGame.brushSize);
	dot.setFillColor(currentGame.currentColor);
	dot.setOrigin(dot.getRadius(), dot.getRadius());

	sizeIndicator.setRadius((float)currentGame.brushSize);
	sizeIndicator.setFillColor(sf::Color::Transparent);
	sizeIndicator.setOutlineColor(sf::Color::Black);
	sizeIndicator.setOutlineThickness(1.0);
	sizeIndicator.setOrigin(dot.getRadius(), dot.getRadius());


	line.setFillColor(currentGame.currentColor);
}

void PencilTool::toolUpdate(Game& currentGame)
{
	dot.setRadius((float)currentGame.brushSize);
	dot.setFillColor(currentGame.currentColor);
	dot.setOrigin(dot.getRadius(), dot.getRadius());

	sizeIndicator.setRadius((float)currentGame.brushSize);
	sizeIndicator.setOrigin(dot.getRadius(), dot.getRadius());

	line.setFillColor(currentGame.currentColor);
}

void PencilTool::toolDeselect(Game& currentGame)
{
}

// mousePosition = cursorCanvasPosition (relative to canvas)
void PencilTool::mouseDown(Game& currentGame, const sf::Vector2f mousePosition)
{
	dot.setPosition(mousePosition);
	currentGame.drawToCanvas(dot);
	lastPosition = mousePosition;
}

// mousePosition = cursorCanvasPosition (relative to canvas)
void PencilTool::mouseDrag(Game& currentGame, const sf::Vector2f mousePosition)
{
	// Sets rectangle to have thickness of 2x brush size, and just enough length to connect dots.
	sf::Vector2f delta = (lastPosition - mousePosition);
	float length = std::sqrt(delta.x * delta.x + delta.y * delta.y);
	if (length == 0) return;
	sf::Vector2f size(length, currentGame.brushSize * (float)2.0);
	line.setSize(size);

	// Puts center left at mouse rather than bottom left.
	line.setOrigin(0, (float)currentGame.brushSize);
	
	// Uses trig to find proper angle to connect dots
	if (delta.x == 0) { // arctan fails if x == 0 (because y/x)
		line.setRotation((float)90.0 * ((delta.y > 0) ? 1 : -1));
		//std::cout << line.getRotation(); lots of numbers on console
	}
	else {
		line.setRotation(std::atan2f(delta.y, delta.x) * 180/(float)M_PI);
	}

	//Draws rectangle at mouse canvas position.
	line.setPosition(mousePosition);
	currentGame.drawToCanvas(line);
	
	// Draws dots at mouse-side edge of rectangle to make corners round
	dot.setPosition(mousePosition);
	currentGame.drawToCanvas(dot);
	lastPosition = mousePosition;
}

// mousePosition = cursorPosition (relative to window)
void PencilTool::mouseMotion(Game& currentGame, const sf::Vector2f mousePosition)
{
	// Draws size indicator (hollow circle)
	sizeIndicator.setPosition(mousePosition);
	currentGame.getWindowReference().draw(sizeIndicator);
}

// mousePosition = cursorCanvasPosition (relative to canvas)
void PencilTool::mouseUp(Game& currentGame, const sf::Vector2f mousePosition)
{
}

sf::CircleShape PencilTool::getDot()
{
	return dot;
}

EyeDropper::~EyeDropper()
{
}

void EyeDropper::toolSelect(Game& currentGame)
{
	colorIndicator.setRadius(20.f);
	colorIndicator.setFillColor(sf::Color::Transparent);
	colorIndicator.setOutlineColor(sf::Color::Black);
	colorIndicator.setOutlineThickness(1.0);
	colorIndicator.setOrigin(20.f, 60.f);
}

void EyeDropper::toolUpdate(Game& currentGame)
{
}

void EyeDropper::toolDeselect(Game& currentGame)
{
}

void EyeDropper::mouseDown(Game& currentGame, const sf::Vector2f mousePosition)
{
	currentGame.currentColor = colorIndicator.getFillColor();
}

void EyeDropper::mouseDrag(Game& currentGame, const sf::Vector2f mousePosition)
{
}

void EyeDropper::mouseMotion(Game& currentGame, const sf::Vector2f mousePosition)
{
	colorIndicator.setPosition(mousePosition);
	currentGame.getWindowReference().draw(colorIndicator);
	sf::Texture screenshotTexture;
	screenshotTexture.create(currentGame.getWindowReference().getSize().x, currentGame.getWindowReference().getSize().y);
	screenshotTexture.update(currentGame.getWindowReference());
	sf::Image screenshot = screenshotTexture.copyToImage();
	sf::Color pColor = screenshot.getPixel(mousePosition.x, mousePosition.y);
	colorIndicator.setFillColor(pColor);
}

void EyeDropper::mouseUp(Game& currentGame, const sf::Vector2f mousePosition)
{
	currentGame.setTool(new PencilTool());
	sf::Color pColor = currentGame.currentColor;
	float offset = 00.0f;
	/*move red slider*/		currentGame.allSliderPos[0] = pColor.r - offset;
	/*move green slider*/	currentGame.allSliderPos[1] = pColor.g - offset;
	/*move blue slider*/	currentGame.allSliderPos[2] = pColor.b - offset;
	/*move alpha slider*/	currentGame.allSliderPos[3] = pColor.a - offset;
}
