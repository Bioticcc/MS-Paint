#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>  
#include <functional>

#include "Button.h"
#include "basic_tools.h"

class Game
{

private:
    int resX;
    int resY;

    std::string windowName = "Template";
    sf::RenderWindow window;
    sf::Event event;
    sf::Sprite toolbar;
    sf::Sprite canvas;
    std::vector<Button> allButtons;

    //TODO create a canvas shape. Drawings are made by modifying the canvas texture. Saving to a file just copies
    // canvas texture

    std::unique_ptr<Tool> currentTool = std::make_unique<PencilTool>(); // Sets the default tool to be a Pencil.

    sf::Color currentColor;
    int currentBrushSize = 5;

public:


    Game();

    void runGame();

    void setTool(Tool& newTool);
   
};

#endif // !GAME_H

