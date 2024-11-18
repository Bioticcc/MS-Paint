#pragma once
#include "Header.h"
class Game
{

private:
	int resX;
	int resY;
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


    void runGame() {
        int i = 0;

        while (window.isOpen()) {
            deltaTime = clock.restart();
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                // "spawns" a pixel object every frame (drawing pixel object to screen)
                float size = 5;
                sf::CircleShape ink(size);
                ink.setFillColor(sf::Color::Green);
                sf::Vector2i cursorPos = sf::Mouse::getPosition(window);
                ink.setPosition(static_cast<float>(cursorPos.x), static_cast<float>(cursorPos.y));
                inkDots.push_back(ink); // Store the ink object in the vector
                i++;
                std::cout << "ink#" << i << " pos: " << ink.getPosition().x << "," << ink.getPosition().y << std::endl;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                inkDots.clear(); // Clear the vector of ink objects
                window.clear();
                i = 0;
                system("cls");
            }

           // window.clear(); // Clear the window before drawing
            window.draw(background); // Draw the background

            // Draw all the ink objects
            for (const auto& ink : inkDots) {
                window.draw(ink);
            }

            window.display(); // Display the drawn frame
        }
    }




};

