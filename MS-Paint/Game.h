#pragma once
#include "Header.h"
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
    Buttons allButtons;

public:


    Game() : resX(1920), resY(1080), window(sf::VideoMode(resX, resY), windowName) {
        if (!backgroundT.loadFromFile("Backgrounds/background.jpg")) {
            std::cerr << "Failed to load background texture\n";
        }
        background.setTexture(backgroundT);
        allButtons.buttonConstructor(); // Initialize buttons in the constructor
    }



    void runGame() {
        while (window.isOpen()) {
            // Process events
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            // Handle inputs
            sf::Vector2i cursorPos = sf::Mouse::getPosition(window);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                //cout << "mouse pos (x,y): " << cursorPos.x << "," << cursorPos.y << std::endl;
                // Handle mouse click events (optional)

                if (allButtons.select.isHovering(cursorPos)) {
                    allButtons.select.buttonFunction();
                    currentTool = 1;
                }

                if (allButtons.pencil.isHovering(cursorPos)) {
                    allButtons.pencil.buttonFunction();
                    currentTool = 2;
                }
            }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                // Optional clear logic
                window.clear();
                system("cls");
                }   

            // Rendering
            window.clear();
            window.draw(background);
            allButtons.drawButtons(window);

            window.display();
        }

           
    }
   
};

