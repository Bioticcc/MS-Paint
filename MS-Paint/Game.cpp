#include "Game.h"

Game::Game() : resX(1920), resY(1080), window(sf::VideoMode(resX, resY), windowName)/*, allButtons(&window)*/ {
    sf::Texture toolbarTexture;
    
    if (!toolbarTexture.loadFromFile("Backgrounds/Toolbar.png")) {
        std::cerr << "Failed to load background texture\n";
    }
    toolbar.setTexture(toolbarTexture);

}

void Game::runGame() {
    using std::cout;
    //currentTool = 1; //by default our starting tool will be 1 (select, ie standard cursor)
    bool wasMousePressed = false;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        sf::Vector2i cursorPos = sf::Mouse::getPosition(window);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !wasMousePressed) { // Check for 
            cout << "mouse pos (x,y): " << cursorPos.x << "," << cursorPos.y << std::endl;
            
            //TODO implement button pressing logic.
            /*
            
            */

        }
        wasMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        // Rendering
        window.clear();
        window.draw(toolbar);
        for (Button& i : allButtons) {
            i.draw(window);
        }
        window.display();
    }


}

void Game::setTool(Tool& newTool)
{
    currentTool.reset(&newTool);
}
