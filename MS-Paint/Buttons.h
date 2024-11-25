#pragma once
#include "Button.h"
#include "Tools.h"
class Buttons : private Button
{
private:
	sf::Texture textureP;
	sf::Texture textureS;
	sf::Texture textureE;
	sf::Texture textureC;
	sf::Texture textureSA;
	sf::Texture texturePR;
	sf::Texture texturePB;
	sf::Texture texturePG;

public:
	sf::RenderWindow* window;
	vector<sf::CircleShape> inkDots;


	std::vector<Button> buttonVect;
	Button select;
	Button pencil;
	Button eraser;
	Button clear;
	Button save;
	Button pencilR;
	Button pencilB;
	Button pencilG;

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
		ink.setFillColor(sf::Color::Black);
		sf::Vector2i cursorPos = sf::Mouse::getPosition(*window);
		ink.setPosition(static_cast<float>(cursorPos.x), static_cast<float>(cursorPos.y));
		inkDots.push_back(ink); // Store the ink object in the vector
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
		for (auto it = inkDots.begin(); it != inkDots.end(); ) {
			if (ink.getGlobalBounds().intersects(it->getGlobalBounds())) {
				it = inkDots.erase(it);
			}
			else {
				++it;
			}
		}
	}

	void clearButton() {
		inkDots.clear();
		system("cls");
	}

	void saveButton() {
		cout << "taking screenshot";
		/*
		sf::Image screenshot = window->capture();
		screenshot.saveToFile("SavedDrawings/drawing1");
		*/
		sf::Texture screenshotTexture;
		screenshotTexture.create(window->getSize().x, window->getSize().y);
		screenshotTexture.update(*window);
		sf::Image screenshot = screenshotTexture.copyToImage();
		std::time_t now = std::time(nullptr);
		char timestamp[20];
		std::strftime(timestamp, sizeof(timestamp), "%Y%m%d_%H%M%S", std::localtime(&now));
		std::string filename = "SavedDrawings/drawing_" + std::string(timestamp) + ".png";
		screenshot.saveToFile(filename);
	}

	void pencilButtonR() {
		float size = 5;
		sf::CircleShape ink(size);
		ink.setFillColor(sf::Color::Red);
		sf::Vector2i cursorPos = sf::Mouse::getPosition(*window);
		ink.setPosition(static_cast<float>(cursorPos.x), static_cast<float>(cursorPos.y));
		inkDots.push_back(ink);
	}

	void pencilButtonB() {
		float size = 5;
		sf::CircleShape ink(size);
		ink.setFillColor(sf::Color::Blue);
		sf::Vector2i cursorPos = sf::Mouse::getPosition(*window);
		ink.setPosition(static_cast<float>(cursorPos.x), static_cast<float>(cursorPos.y));
		inkDots.push_back(ink);
	}

	void pencilButtonG() {
		float size = 5;
		sf::CircleShape ink(size);
		ink.setFillColor(sf::Color::Green);
		sf::Vector2i cursorPos = sf::Mouse::getPosition(*window);
		ink.setPosition(static_cast<float>(cursorPos.x), static_cast<float>(cursorPos.y));
		inkDots.push_back(ink);
	}

	void buttonConstructor() {
		textureS.loadFromFile("Buttons/select1.png");
		textureP.loadFromFile("Buttons/pencil1.png");
		textureE.loadFromFile("Buttons/eraser.png");
		textureC.loadFromFile("Buttons/clear.png");
		textureSA.loadFromFile("Buttons/save.png");
		texturePR.loadFromFile("Buttons/pencilR.png");
		texturePB.loadFromFile("Buttons/pencilB.png");
		texturePG.loadFromFile("Buttons/pencilG.png");



		select = Button(textureS, 16.0f, 13.0f, [this]() { selectButton(); }, 115.0f, 115.0f);
		pencil = Button(textureP, 218.0f, 16.0f, [this]() { pencilButton(); }, 115.0f, 115.0f);
		eraser = Button(textureE, 16.0f, 148.0f, [this]() {eraserButton(); }, 115.0f, 115.0f);
		clear = Button(textureC, 16.0f, 918.0f, [this]() {clearButton(); }, 210.0f, 100.0f);
		save = Button(textureSA, 118.0f, 785.0f, [this]() {saveButton(); }, 210.0f, 100.0f);
		pencilR = Button(texturePR, 218.0f, 150.0f, [this]() {pencilButtonR(); }, 115.0f, 115.0f);
		pencilB = Button(texturePB, 218.0f, 282.0f, [this]() {pencilButtonB(); }, 115.0f, 115.0f);
		pencilG = Button(texturePG, 218.0f, 415.0f, [this]() {pencilButtonG(); }, 115.0f, 115.0f);

		buttonVect.push_back(select);
		buttonVect.push_back(pencil);
		buttonVect.push_back(eraser);
		buttonVect.push_back(clear);
		buttonVect.push_back(save);
		buttonVect.push_back(pencilR);
		buttonVect.push_back(pencilB);
		buttonVect.push_back(pencilG);


		std::cout << "Number of buttons: " << buttonVect.size() << "\n";

		for (auto& button : buttonVect) {
			std::cout << "Button at: (" << button.getPosX() << ", " << button.getPosY() << ")\n";
			}
		}	

	void drawButtons() {
		window->draw(select.getIcon());
		window->draw(pencil.getIcon());
		window->draw(eraser.getIcon());
		window->draw(clear.getIcon());
		window->draw(save.getIcon());
		window->draw(pencilR.getIcon());
		window->draw(pencilB.getIcon());
		window->draw(pencilG.getIcon());


		for (const auto& ink : inkDots) {
			window->draw(ink);
		}

	}

};

