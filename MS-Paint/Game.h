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
    std::vector<Button*> allButtons;

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

    void addButton(Button* newButton);

    void setColor(sf::Color newColor);
    //void getColor(void);

   // void setSize(int newSize)

   
    sf::RenderWindow& getWindowReference(void);

    void drawToCanvas(sf::Sprite* toStamp);

};

#include "basic_tools.h"

void initializeButtons(Game&);

#endif // !GAME_H

