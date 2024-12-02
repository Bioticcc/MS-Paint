#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

#include <vector> 
#include <iostream>
#include <functional>

using std::cout;
using std::vector;

class Button
{
private:
	//button visuals
	sf::Texture buttonIconTexture;
	sf::RectangleShape buttonIcon;

	//button position on screen
	float posX, posY;
	sf::Vector2f size;

	bool clicked;

public:
	std::function<void()> buttonFunction;

	//default constructor
	Button();
	//constructor
	
	Button(sf::Texture& texture, float X, float Y, std::function<void()> functionPtr, float sizeX, float sizeY);
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
	std::function<void()> getFuncPtr();
	sf::RectangleShape getIcon();
	void setPos(float x, float y);

	void setFuncPtr(std::function<void()>& funcPtr);
	void setButtonIcon(sf::Texture texture);
	//wether or not the button is being hovered
	bool isHovering(const sf::Vector2i& cursorPos);

	//wether or not the button is being pressed
	bool isPressed(const sf::Vector2i& cursorPos);

	void draw(sf::RenderWindow& window);

};



#endif // !BUTTON_H
