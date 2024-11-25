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
    bool drawMode;
    bool buttonHasBeenPressed;

public:


    Game() : resX(1920), resY(1080), window(sf::VideoMode(resX, resY), windowName), allButtons(&window) {
        if (!backgroundT.loadFromFile("Backgrounds/background1.png")) {
            std::cerr << "Failed to load background texture\n";
        }
        background.setTexture(backgroundT);
        allButtons.buttonConstructor(); // Initialize buttons in the constructor
    }



    void runGame() {
        //currentTool = 1; //by default our starting tool will be 1 (select, ie standard cursor)
        while (window.isOpen()) {
            buttonHasBeenPressed = false;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            sf::Vector2i cursorPos = sf::Mouse::getPosition(window);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
               // cout << "mouse pos (x,y): " << cursorPos.x << "," << cursorPos.y << std::endl;
                // Handle mouse click events (optional)

                //this is if the mouse is clicking a button! 
               
                if (!buttonHasBeenPressed) {//IDEA FOR IMPROVEMENT: Make this a loop that goes through the vector of Button objects in allButtons, rather then a bunch of if statements!
                    if (allButtons.select.isHovering(cursorPos)) {
                        cout << "select pressed\n";
                        currentTool = 1;
                        buttonHasBeenPressed = true;
                    }

                    else if (allButtons.pencil.isHovering(cursorPos)) {
                        cout << "pencil pressed\n";
                        currentTool = 2;
                        buttonHasBeenPressed = true;
                    }

                    else if (allButtons.eraser.isHovering(cursorPos)) {
                        cout << "eraser pressed\n";
                        currentTool = 3;
                        buttonHasBeenPressed = true;
                    }
                }
                //if the mouse is NOT clicking a button, and is hovering the drawing space, we do the functions the button provides. (with the exception of the select button, witch works EVERYWHERE!
                if (cursorPos.x > 425.0f) {
                    //we are in the draw screen! time for some drawing to occur with our given tool!
                    switch (currentTool) {
                    case 1: 
                        allButtons.select.buttonFunction();
                        break;
                        //select tool, as of now nothing happens. Just means we aint doin DIDDLY to the screen
                    case 2:
                        //pencil tool! now we will call the pencil tools function, draw! 
                         allButtons.pencil.buttonFunction();
                         break;
                    case 3:
                        allButtons.eraser.buttonFunction();
                        break;

                    }
                }
            }
                

            // Rendering
            window.clear();
            window.draw(background);
            allButtons.drawButtons();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                allButtons.inkDotsP1.clear();

                system("cls");
            }

            window.display();
        }

           
    }
   
};

