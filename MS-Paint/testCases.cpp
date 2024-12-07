#pragma once

#include "TestCases.h"
#include "Button.h"
#include "Game.h"

TestCases::TestCases()
{
}

TestCases::~TestCases()
{
}

// Programmed by FloatingToa5t
//  Edited by Inventor4life
//            david_ac_leon
//            bioticc
// 
// Class - TestCase
// Name: testSave()
// Testing Func: Game::saveCanvasToFile()
// Description: tests the function of the saveToFile function
//				by looking at the bool returned
// Application is only launched in:
//      main.cpp
void TestCases::testSave()
{
	Game G;
	sf::Image t;
	if (G.saveCanvasToFile() == true) // TESTED FUNCTION
	{
		std::cout << "\033[1;HSave Image Test - task successful";
	}
	else {
		std::cout << "\033[1;HSave Image Test - task failed";
	}
}

// Programmed by FloatingToa5t
//  Edited by Inventor4life
//            david_ac_leon
//            bioticc
// 
// Class - TestCase
// Name: testPickTool()
// Testing Func: Game::setTool()
// Description: tests the setToolby setting the current tool to a new
//				pencil tool and checking if the unique_ptr<Tool>
//				currentTool member is indeed allocated
// Application is only launched in:
//      main.cpp
void TestCases::testPickTool()
{
	Game G;
	// TESTED FUNCTION
	G.setTool(new PencilTool()); // set game tool to PencilTool
	if (dynamic_cast<PencilTool*>(G.currentTool.get()) != nullptr) 
	{
		std::cout << "\033[2;HChange Tool Test - task successful";
	}
	else {
		std::cout << "\033[2;HChange Tool Test - task failed";
	}
}

// Programmed by FloatingToa5t
//  Edited by Inventor4life
//            david_ac_leon
//            bioticc
// 
// Class - TestCase
// Name: testDraw()
// Testing Func: Game::drawToCanvas()
// Description: creates a black dot and draws it to the canvas
//				using drawToCanvas. The canvas is initialized as
//				white so the only black pixels are where the dot is.
//				Checks that the pixels where the dot was drawn are
//				indeed black.
// Application is only launched in:
//      main.cpp
void TestCases::testDraw()
{
	Game G; // canvas is white
	sf::CircleShape testDot;
	testDot.setFillColor(sf::Color::Black);
	testDot.setRadius(50);
	testDot.setOrigin(50, 50);
	testDot.setPosition(100, 100);
	G.drawToCanvas(testDot); // TESTED FUNCTION
	if (G.canvas.getTexture()->copyToImage().getPixel(100,1080-100) == sf::Color::Black)
	{
		std::cout << "\033[3;HDraw Test - task successful";
	}
	else {
		std::cout << "\033[3;HDraw Test - task failed";
	}
}

// Programmed by FloatingToa5t
//  Edited by Inventor4life
//            david_ac_leon
//            bioticc
// 
// Class - TestCase
// Name: testChangeColor()
// Testing Func: sf::Color =operator
// Description: changes the games current brush color then
//				checks if the member was changed to that new color
// Application is only launched in:
//      main.cpp
void TestCases::testChangeColor()
{
	Game G;
	G.currentColor = sf::Color::Red;
	if (G.currentColor == sf::Color::Red) {
		std::cout << "\033[4;HChange Color Test - task successful";
	}
	else {
		std::cout << "\033[4;HChange Color Test - task failed";
	}
}

// Programmed by FloatingToa5t
//  Edited by Inventor4life
//            david_ac_leon
//            bioticc
// 
// Class - TestCase
// Name: testChangeColor()
// Testing Func: Game::addButton()
// Description: creates a new test button which is added
//				to the allButtons list in G. There are 13 buttons
//				when a Game type is initialized so to find the most 
//				recent, we look at element size - 1. if that most
//				recent element is the test button, its a success
// Application is only launched in:
//      main.cpp
void TestCases::testAddButton()
{
	Game G;
	Button* test = new Button();
	G.addButton(test);

	if (G.allButtons[G.getButtonCount() - 1] == test) {
		std::cout << "\033[5;HAdd Button Test - task successful";
	}
	else {
		std::cout << "\033[5;HAdd Button Test - task failed";
	}
}