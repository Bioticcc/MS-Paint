// Programmed by Bioticcc
//  Edited by Inventor4life
//            FloatingToa5t
//            david_ac_leon
//		
// Assignment: PA9
// File: Game.h
// Description:
//  Contains the game class and all function prototypes needed to use it.
//	    

#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include <functional>
#include <iostream>  
#include <string>

#include "Button.h"

//Game class won't work without these forward declarations.
//Including basic_tools.h on top directly causes circular dependencies, and forward declaring Game class
// prevents us from calling Game related methods (AFAIK)
class Tool;
class TestCases;

// Programmed by Bioticcc
//  Edited by Inventor4life
//            FloatingToa5t
//            david_ac_leon
// 
// Game class:
//  Contains the main application methods and data.
//  Application is launched by using:
//      G newApp;
//      newApp.runApp();
//		
class Game
{

private:
    int resX;
    int resY;

    std::string windowName = "BHP: Big Hard Paint";
    sf::RenderWindow window;

    sf::Event event;
    
    sf::Texture toolbarTexture;
    sf::Sprite toolbar;

    sf::RenderTexture canvasRenderTexture;
    sf::Sprite canvas;

    sf::Vector2f cursorPosition;
    sf::Vector2f cursorCanvasPosition;

    std::unique_ptr<Tool> currentTool = nullptr; // Sets the default tool nullptr

    int timesSaved;
    friend TestCases;
public:
    std::vector<Button*> allButtons;
    sf::Color currentColor;
    std::vector<float> allSliderPos;
    std::vector<sf::Sprite> redoUndoVector;

    float brushSize = 5;

    Game();

    void runGame();

    void setTool(Tool* newTool);
    void updateTool(void);

    void addButton(Button* newButton);
   
    sf::RenderWindow& getWindowReference(void);

    void drawToCanvas(sf::Shape& toStamp);

    sf::Color getColor() const;
    int getButtonCount() const;
    void displayInfo() const;

    sf::Vector2f getCursorPos_Vector2f() const;
    sf::Vector2f getCursorCanvasPos_Vector2f() const;

    sf::Sprite& getCanvas();
    void setCanvas(sf::Sprite newCanvas);

    int getCanvasStatesSaved() const;
    void incramentSaveCounter();


};

#include "basic_tools.h" // F***** up 6OD9^MN circular inheritance weird SH|T. Won't compile without this line

// Programmed by Bioticcc
//  Edited by Inventor4life
//            FloatingToa5t
//            david_ac_leon
// 
// function:
//  void initializeButtons( Game& thisGame )
// 
// description:
//  creates all application buttons and inserts them into the allButtons vector
// 
// parameters:
//  Game& thisGame - Reference to game to insert buttons for.
// 
// returns:
//  nothing
//
void initializeButtons(Game& thisGame);

#endif // !GAME_H