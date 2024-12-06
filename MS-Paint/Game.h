#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include <functional>
#include <iostream>  
#include <string>

#include "Button.h"

//Extremely unprofessional, game class won't work without these forward declarations.
//Including basic_tools.h directly causes circular dependencies, and forward declaring Game class
// prevents us from calling Game related methods (AFAIK)
class Tool;
class Game
{

private:
    int resX;
    int resY;

    std::string windowName = "Template";
    sf::RenderWindow window;

    sf::Event event;
    
    sf::Texture toolbarTexture;
    sf::Sprite toolbar;

    sf::RenderTexture canvasRenderTexture;
    sf::Sprite canvas;

    sf::Vector2f cursorPosition;
    sf::Vector2f cursorCanvasPosition;

    std::unique_ptr<Tool> currentTool = nullptr; // Sets the default tool to be a Pencil.

    int timesSaved;
public:
    std::vector<Button*> allButtons;
    sf::Color currentColor;

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

    void incramentSaveCounter();
};

#include "basic_tools.h" // F***** up 6OD9^MN circular inheritance weird SH|T

void initializeButtons(Game&);

#endif // !GAME_H