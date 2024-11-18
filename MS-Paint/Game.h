#pragma once
#include "Header.h"
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
	//Entity player;
	std::string playerFileLoc = "Entities/player.png";
	std::string backgroundFileLoc = "Backgrounds/background.jpg";

	sf::Clock clock;
	sf::Time deltaTime;
	sf::CircleShape ink;

	std::vector<sf::CircleShape> inkDots;

public:

	Game() : resX(1920), resY(1080), window(sf::VideoMode(resX, resY), windowName) {
		if (!backgroundT.loadFromFile(backgroundFileLoc)) {
			std::cerr << "Failed to load background texture\n";
		}
		background.setTexture(backgroundT);
	}

    //cursor functions

    //draw
    void draw() {
        int i = 0;
        // "spawns" a pixel object every frame (drawing pixel object to screen)
        float size = 5;
        sf::CircleShape ink(size);
        ink.setFillColor(sf::Color::Green);
        sf::Vector2i cursorPos = sf::Mouse::getPosition(window);
        ink.setPosition(static_cast<float>(cursorPos.x), static_cast<float>(cursorPos.y));
        inkDots.push_back(ink); // Store the ink object in the vector
        i++;
        std::cout << "ink#" << i << " pos: " << ink.getPosition().x << "," << ink.getPosition().y << std::endl;
        // Draw all the ink objects
        
    }

    void runGame() {
        while (window.isOpen()) {
            deltaTime = clock.restart();
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                //mouse functions:
                //Draw:
                draw();

            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                inkDots.clear(); // Clear the vector of ink objects
                window.clear();
                system("cls");
            }

            window.draw(background); // Draw the background

            for (const auto& ink : inkDots) {
                window.draw(ink);
            }

            window.display(); // Display the drawn frame
        }
    }




};

