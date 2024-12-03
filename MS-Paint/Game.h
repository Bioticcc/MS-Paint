#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include <functional>
#include <iostream>  
#include <string>

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
    sf::Texture toolbarTexture;
    sf::Sprite toolbar;
    sf::Sprite canvas;
    std::vector<Button> allButtons;

    sf::Vector2f cursorPosition;
    sf::Vector2f cursorCanvasPosition;

    //TODO create a canvas shape. Drawings are made by modifying the canvas texture. Saving to a file just copies
    // canvas texture

    std::unique_ptr<Tool> currentTool = std::make_unique<PencilTool>(); // Sets the default tool to be a Pencil.

    sf::Color currentColor;
    int currentBrushSize = 5;

public:

    Game();

    void runGame();

    void setTool(Tool* newTool);

    void addButton(Button& newButton);

    void setColor(sf::Color newColor);
   
    sf::RenderWindow& getWindowReference(void);

};

void initializeButtons(Game&);
void testButton(Game& masterGame);

#endif // !GAME_H

