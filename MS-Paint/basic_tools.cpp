#include "basic_tools.h"
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Assignment: PA9
// File: basic_tools.cpp
// Description:
// Implements the methods for SelectionTool, EraserTool, PencilTool, and EyeDropper.
// Each tool defines how it interacts with the canvas and responds to user input.
//
//
//Unused func

SelectionTool::~SelectionTool()
{
}
//Unused func
void SelectionTool::toolSelect(Game& currentGame)
{
}
//Unused func

void SelectionTool::toolUpdate(Game& currentGame)
{
}
//Unused func

void SelectionTool::toolDeselect(Game& currentGame)
{
}
//Unused func

void SelectionTool::mouseDown(Game& currentGame, const sf::Vector2f mousePosition)
{
}
//Unused func

void SelectionTool::mouseDrag(Game& currentGame, const sf::Vector2f mousePosition)
{
}
//Unused func

void SelectionTool::mouseMotion(Game& currentGame, const sf::Vector2f mousePosition)
{
}
//Unused func

void SelectionTool::mouseUp(Game& currentGame, const sf::Vector2f mousePosition)
{
}
//Unused func

EraserTool::~EraserTool()
{
}
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: ~EraserTool (Destructor)
// Parameters: None
// Return Values: None
// Description:
// Cleans up EraserTool resources upon destruction.
//
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
//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: toolUpdate
// Parameters: Game& currentGame
// Return Values: None
// Description:
// Updates the eraser size if the brush size changes.
//
void EraserTool::toolUpdate(Game& currentGame)
{
	dot.setRadius((float)currentGame.brushSize);
	dot.setOrigin(dot.getRadius(), dot.getRadius());

	sizeIndicator.setRadius((float)currentGame.brushSize);
	sizeIndicator.setOrigin(dot.getRadius(), dot.getRadius());
}
//unused func
void EraserTool::toolDeselect(Game& currentGame)
{
}
//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: mouseDown
// Parameters: Game& currentGame, const sf::Vector2f mousePosition
// Return Values: None
// Description:
// When mouse is pressed, a white dot is drawn at the clicked position to erase canvas content.
//
void EraserTool::mouseDown(Game& currentGame, const sf::Vector2f mousePosition)
{
	dot.setPosition(mousePosition);
	currentGame.drawToCanvas(dot);
	lastPosition = mousePosition;
}
//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: mouseDrag
// Parameters: Game& currentGame, const sf::Vector2f mousePosition
// Return Values: None
// Description:
// While the mouse is dragged, draw a white line to emulate erasing. Connects last position to current.
//
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
//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: mouseMotion
// Parameters: Game& currentGame, const sf::Vector2f mousePosition
// Return Values: None
// Description:
// Displays a size indicator at the mouse position while moving without drawing.
//
void EraserTool::mouseMotion(Game& currentGame, const sf::Vector2f mousePosition)
{
	sizeIndicator.setPosition(mousePosition);
	currentGame.getWindowReference().draw(sizeIndicator);
}
//unused
void EraserTool::mouseUp(Game& currentGame, const sf::Vector2f mousePosition)
{
}
//unused

PencilTool::~PencilTool()
{
}
//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: toolSelect
// Parameters: Game& currentGame
// Return Values: None
// Description:
// Initializes pencil shapes and size indicators when the pencil tool is selected.
//
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
//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: toolUpdate
// Parameters: Game& currentGame
// Return Values: None
// Description:
// Updates pencil properties (e.g., size, color) when brush size or color changes.
//
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

//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: mouseDown
// Parameters: Game& currentGame, const sf::Vector2f mousePosition
// Return Values: None
// Description:
// Draws a dot at the mouse down position to start a pencil stroke.
//
void PencilTool::mouseDown(Game& currentGame, const sf::Vector2f mousePosition)
{
	dot.setPosition(mousePosition);
	currentGame.drawToCanvas(dot);
	lastPosition = mousePosition;
}

//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: mouseDrag
// Parameters: Game& currentGame, const sf::Vector2f mousePosition
// Return Values: None
// Description:
// Draws a line connecting the last position to the current position as the mouse drags.
//
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

//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: mouseMotion
// Parameters: Game& currentGame, const sf::Vector2f mousePosition
// Return Values: None
// Description:
// Shows a size indicator around the cursor when moving the mouse without drawing.
//
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
//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: toolSelect
// Parameters: Game& currentGame
// Return Values: None
// Description:
// Prepares the EyeDropper tool by setting up a color indicator.
//
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
//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: mouseDown
// Parameters: Game& currentGame, const sf::Vector2f mousePosition
// Return Values: None
// Description:
// Picks the current color from the indicator when the mouse is pressed.
//
void EyeDropper::mouseDown(Game& currentGame, const sf::Vector2f mousePosition)
{
	currentGame.currentColor = colorIndicator.getFillColor();
}

void EyeDropper::mouseDrag(Game& currentGame, const sf::Vector2f mousePosition)
{
}
//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: mouseMotion
// Parameters: Game& currentGame, const sf::Vector2f mousePosition
// Return Values: None
// Description:
// Updates the color indicator to match the pixel under the cursor.
//
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
//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: mouseUp
// Parameters: Game& currentGame, const sf::Vector2f mousePosition
// Return Values: None
// Description:
// On mouse release, the EyeDropper switches tool back to a PencilTool.
//
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
