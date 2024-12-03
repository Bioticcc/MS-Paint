#include "Game.h"

Game::Game() : resX(1920), resY(1080), window(sf::VideoMode(resX, resY), windowName)/*, allButtons(&window)*/ {
    if (!toolbarTexture.loadFromFile("Backgrounds/Toolbar.png")) {
        std::cerr << "Failed to load background texture\n";
    }
    toolbar.setTexture(toolbarTexture);

}

void Game::runGame() {
    using std::cout;
    //currentTool = 1; //by default our starting tool will be 1 (select, ie standard cursor)
    bool mouseWasPressed = false;

    //initializeButtons(*this);

    //DEBUG - remove comment on immediate above, delete everything until END DEBUG
    Button save("Buttons/save.png", 118.0f, 785.0f, testButton, 210.0f, 100.0f);
    this->addButton(save);
    //END DEBUG

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        cursorPosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (!mouseWasPressed) { // true for rising edge of click
                cout << "mouse pos (x,y): " << cursorPosition.x << "," << cursorPosition.y << std::endl;

                for (Button& i : allButtons) {
                    if (i.isMouseHoveringOverButton(cursorPosition)) {
                        if (i.onClick != nullptr) i.onClick(*this); // Pass the Game object, so buttons can trigger anything.
                        i.clicked = true;
                    }
                    else {
                        i.clicked = false;
                    }
                }
            }
            else { // mouse was held
                if (toolbar.getGlobalBounds().contains(cursorPosition)) {
                    for (Button& i : allButtons) {
                        if (i.clicked == true && i.onHold != nullptr) {
                            i.onHold(*this); // Pass the Game object, so buttons can trigger anything.
                        }
                    }
                }
            }

        }
        else if (mouseWasPressed) { // True only for falling edge of click
            for (Button& i : allButtons) {
                i.clicked = false;
            }
        }


        mouseWasPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        // Rendering
        window.clear();
        //window.draw(toolbar);
       /* for (Button& i : allButtons) {
            i.draw(window);
        }*/
    save.draw(window);
        window.display();
    }


}

void Game::setTool(Tool* newTool)
{
    currentTool.reset(newTool); // Deallocates the old tool and sets it to the new one.
}

void Game::addButton(Button& newButton)
{
    allButtons.push_back(newButton);
}

void Game::setColor(sf::Color newColor)
{
    currentColor = newColor;
}

sf::RenderWindow& Game::getWindowReference(void)
{
    return this->window;
}

void testButton(Game& masterGame) {
    std::cout << "YEET!";
}

void initializeButtons(Game& masterGame)
{
    Button save("Buttons/save.png", 118.0f, 785.0f, testButton, 210.0f, 100.0f);
    
    //DEBUG - Remove line below
    save.draw(masterGame.getWindowReference());

    masterGame.addButton(save);
}
