#include "Game.h"

inline Game::Game() : resX(1920), resY(1080), window(sf::VideoMode(resX, resY), windowName)/*, allButtons(&window)*/ {
    if (!backgroundT.loadFromFile("Backgrounds/background1.png")) {
        std::cerr << "Failed to load background texture\n";
    }
    background.setTexture(backgroundT);
    framesSinceSizeIncrease = 30;
}

inline void Game::runGame() {
    using std::cout;
    //currentTool = 1; //by default our starting tool will be 1 (select, ie standard cursor)
    bool wasMousePressed = false;
    while (window.isOpen()) {
        buttonHasBeenPressed = false;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        sf::Vector2i cursorPos = sf::Mouse::getPosition(window);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !wasMousePressed) {
            cout << "mouse pos (x,y): " << cursorPos.x << "," << cursorPos.y << std::endl;
            
            //TODO fix.
            /*
            if (!buttonHasBeenPressed) {
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

                else if (allButtons.clear.isHovering(cursorPos)) {
                    cout << "clear pressed\n";
                    allButtons.clear.buttonFunction();
                    buttonHasBeenPressed = true;
                }

                else if (allButtons.save.isHovering(cursorPos)) {
                    cout << "save pressed\n";
                    allButtons.save.buttonFunction();
                    buttonHasBeenPressed = true;
                }

                else if (allButtons.pencilR.isHovering(cursorPos)) {
                    cout << "pencil RED pressed\n";
                    currentTool = 4;
                    buttonHasBeenPressed = true;
                }

                else if (allButtons.pencilB.isHovering(cursorPos)) {
                    cout << "pencil BLUE pressed\n";
                    currentTool = 5;
                    buttonHasBeenPressed = true;
                }

                else if (allButtons.pencilG.isHovering(cursorPos)) {
                    cout << "pencil GREEN pressed\n";
                    currentTool = 6;
                    buttonHasBeenPressed = true;
                }

                else if (allButtons.increase.isHovering(cursorPos) && framesSinceSizeIncrease >= 30) {
                    cout << "INCREASE INKN SIZE pressed";
                    allButtons.increase.buttonFunction();
                    framesSinceSizeIncrease = 0;
                }

                else if (allButtons.decrease.isHovering(cursorPos) && framesSinceSizeIncrease >= 30) {
                    cout << "DECREASE INKN SIZE pressed";
                    allButtons.decrease.buttonFunction();
                    framesSinceSizeIncrease = 0;
                }


            }

        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (cursorPos.x > 425.0f) {
                switch (currentTool) {
                case 1:
                    allButtons.select.buttonFunction();
                    break;
                case 2:
                    allButtons.pencil.buttonFunction();
                    break;
                case 3:
                    allButtons.eraser.buttonFunction();
                    break;
                case 4:
                    allButtons.pencilR.buttonFunction();
                    break;
                case 5:
                    allButtons.pencilB.buttonFunction();
                    break;
                case 6:
                    allButtons.pencilG.buttonFunction();
                    break;
                }
            }
            */

        }
        wasMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        framesSinceSizeIncrease++;
        // Rendering
        window.clear();
        window.draw(background);
        //allButtons.drawButtons();
        window.display();
    }


}
