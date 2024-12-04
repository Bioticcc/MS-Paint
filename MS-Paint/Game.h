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

public:
    std::vector<Button*> allButtons;
    sf::Color currentColor;
    int brushSize = 5;

    Game();

    void runGame();

    void setTool(Tool* newTool);
    void updateTool(void);

    void addButton(Button* newButton);
   
    sf::RenderWindow& getWindowReference(void);

    void drawToCanvas(sf::Shape& toStamp);

};

#include "basic_tools.h" // F***** up 6OD9^MN circular inheritance weird SH|T

void initializeButtons(Game&);

#endif // !GAME_H

