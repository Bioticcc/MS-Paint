#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>  
#include <functional>

#include "Buttons.h"

class Game
{

private:
    int resX;
    int resY;
    int action;

    std::string windowName = "Template";
    sf::RenderWindow window;
    sf::Event event;
    sf::Texture backgroundT;
    sf::Sprite background;
    sf::Clock clock;
    sf::Time deltaTime;
    sf::CircleShape ink;
    int currentTool;
    std::vector<Button> allButtons;
    bool drawMode;
    bool buttonHasBeenPressed;
    int framesSinceSizeIncrease;
public:


    Game();



    void runGame();
   
};

#endif // !GAME_H
