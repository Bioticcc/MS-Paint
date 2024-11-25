#pragma once
#include "Button.h"
class Buttons : private Button
{
private:
	sf::Texture textureP;
	sf::Texture textureS;
	sf::Texture textureTest;
public:
	std::vector<Button> buttonVect;
	Button select;
	Button pencil;
	Button test;
	//constructor
	Buttons() {
		std::cout << "Buttons created!\n";

	}

	void selectButton() {
		cout << "select pressed!\n";
	}

	void pencilButton() {
		cout << "pencil pressed!\n";
		
		std::vector<sf::CircleShape> inkDots;

		/*
		for (const auto& ink : inkDots) {
			window.draw(ink);
		}*

		draw
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
	   */
	}

	void testButton() {
		cout << "test";
	}

	void buttonConstructor() {
		textureS.loadFromFile("Buttons/select.png");
		textureP.loadFromFile("Buttons/pencil.png");
		//textureTest.loadFromFile("Buttons/test.jpg");
		select = Button(textureS, 22.0f, 18.0f, [this]() { selectButton(); });
		pencil = Button(textureP, 300.0f, 18.0f, [this]() { pencilButton(); });
		//test = Button(textureTest, 100.0f, 18.0f, [this]() {testButton(); });

	
    buttonVect.push_back(select);
    buttonVect.push_back(pencil);
	//buttonVect.push_back(test);
	std::cout << "Number of buttons: " << buttonVect.size() << "\n";

	for (auto& button : buttonVect) {
		std::cout << "Button at: (" << button.getPosX() << ", " << button.getPosY() << ")\n";
		}
	}	

	void drawButtons(sf::RenderWindow& window) {
		
		// doesnt work for some reason, fuck if i know why lmao
		
		
		window.draw(select.getIcon());
		window.draw(pencil.getIcon());
		//window.draw(test.getIcon());

	}


};

