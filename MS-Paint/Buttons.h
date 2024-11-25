#pragma once
#include "Button.h"
#include "Tools.h"
class Buttons : private Button
{
private:
	sf::Texture textureP;
	sf::Texture textureS;
	sf::Texture textureE;

public:
	sf::RenderWindow* window;
	vector<sf::CircleShape> inkDotsP1;
	vector<sf::CircleShape> inkDotsEr;

	std::vector<Button> buttonVect;
	Button select;
	Button pencil;
	Button eraser;
	//constructor
	Buttons(sf::RenderWindow* renderWindow) : window(renderWindow) {
		std::cout << "Buttons created!\n";

	}

	//since I seem to need it so damn much im making a function that gets me the RenderWindow ob

	//these functions should later be held within tools.
	void selectButton() {
		cout << "SELECTING!\n";
		//this is where we would call the select tool.
	}

	void pencilButton() {
		cout << "DRAWING WITH PENCIL!\n";

		//this should go in the Pencil Tool object eventually
		float size = 5;
		sf::CircleShape ink(size);
		ink.setFillColor(sf::Color::Magenta);
		sf::Vector2i cursorPos = sf::Mouse::getPosition(*window);
		ink.setPosition(static_cast<float>(cursorPos.x), static_cast<float>(cursorPos.y));
		inkDotsP1.push_back(ink); // Store the ink object in the vector
		
	}

	void eraserButton() {

		/*
		ALRIGHT so eraser is FUCKY! in case I get bored and go to sleep before I finish this, heres the new plan:
		blah blah blah nvm I dont wanna explain just remember how 
		*/


		cout << "ERASING!\n";
		float size = 5;
		sf::CircleShape ink(size);
		sf::Vector2i cursorPos = sf::Mouse::getPosition(*window);
		ink.setPosition(static_cast<float>(cursorPos.x), static_cast<float>(cursorPos.y));
		for (auto it = inkDotsP1.begin(); it != inkDotsP1.end(); ) {
			if (ink.getGlobalBounds().intersects(it->getGlobalBounds())) {
				it = inkDotsP1.erase(it);
			}
			else {
				++it;
			}
		}
	}


	void buttonConstructor() {
		textureS.loadFromFile("Buttons/select1.png");
		textureP.loadFromFile("Buttons/pencil1.png");
		textureE.loadFromFile("Buttons/eraser.png");
		select = Button(textureS, 16.0f, 13.0f, [this]() { selectButton(); }, 115.0f, 115.0f);
		pencil = Button(textureP, 218.0f, 16.0f, [this]() { pencilButton(); }, 115.0f, 115.0f);
		eraser = Button(textureE, 16.0f, 148.0f, [this]() {eraserButton(); }, 115.0f, 115.0f);
	
		buttonVect.push_back(select);
		buttonVect.push_back(pencil);
		buttonVect.push_back(eraser);
		std::cout << "Number of buttons: " << buttonVect.size() << "\n";

		for (auto& button : buttonVect) {
			std::cout << "Button at: (" << button.getPosX() << ", " << button.getPosY() << ")\n";
			}
		}	

	void drawButtons() {
		window->draw(select.getIcon());
		window->draw(pencil.getIcon());
		window->draw(eraser.getIcon());

		for (const auto& ink : inkDotsP1) {
			window->draw(ink);
		}

		for (const auto& ink : inkDotsEr) {
			window->draw(ink);
		}

	}


};

