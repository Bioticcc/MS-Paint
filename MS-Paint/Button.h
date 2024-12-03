#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

#include <iostream>
#include <functional>
#include <vector> 

// Not sure if this should be abstract or use function ptrs...
class Button
{
private:
	//button visuals
	sf::Texture buttonTexture;
	sf::RectangleShape buttonShape;

	//button position on screen
	float posX, posY;
	sf::Vector2f size;

public:
	bool clicked = false;

	// I've had enough of abstract classes today.
	std::function<void(class Game&)> onClick;
	std::function<void(class Game&)> onHold;
	std::function<void(class Game&)> onRelease;

	//default constructor
	Button();
	//constructor
	
	Button(const std::string& textureFilePath, float X, float Y, float sizeX, float sizeY, std::function<void(class Game&)> newOnClick = nullptr, std::function<void(class Game&)> newOnHold = nullptr, std::function<void(class Game&)> newOnRelease = nullptr);
	/*
	Button(const std::string& textureFilePath, float X, float Y, std::function<void()> functionPtr) {
		if (!buttonIconTexture.loadFromFile(textureFilePath)) {
			std::cerr << "Failed to load texture from: " << textureFilePath << "\n";
		}
		else {
			buttonIcon.setTexture(&buttonIconTexture); 
		}
		buttonIcon.setSize(sf::Vector2f(buttonIconTexture.getSize().x, buttonIconTexture.getSize().y));
		buttonIcon.setTexture(&buttonIconTexture);
		buttonIcon.setPosition(X, Y);
		buttonFunction = functionPtr;
		posX = X;
		posY = Y;
	}*/


	//copy constructor
	Button(const Button& B);

	//deconstructor
	~Button();

	//getters-setters
	float getPosX();
	float getPosY();
	sf::RectangleShape getIcon();
	void setPos(float x, float y);

	void setButtonIcon(sf::Texture texture);
	//wether or not the button is being hovered
	bool isMouseHoveringOverButton(const sf::Vector2f& cursorPos);

	void draw(sf::RenderWindow& window);

};



#endif // !BUTTON_H

