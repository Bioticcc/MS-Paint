#pragma once
#ifndef BUTTON_H
#define BUTTON_H
// Programmed by Bioticcc
//  Edited by Inventor4life
//            FloatingToa5t
//            david_ac_leon    
//
// Assignment: PA 9
// File: Button.h
// Description:
//  The button class header. contains function definitons for the button class,
//	and variables stored within the function
//
#include <SFML/Graphics.hpp>

#include <iostream>
#include <functional>
#include <vector> 

typedef enum CLICKSTATE {
	PRESS,
	RELEASE
};
// Not sure if this should be abstract or use function ptrs...

//// Programmed by Bioticcc
//  Edited by Inventor4life
//            FloatingToa5t
//            david_ac_leon    
//
//	Description:
//	The button class! stores all the information related to a button, 
//	for the purpose of encapsulation and ease of access. We have many button objects needed,
//	so making a class for them seemed like the right way to go
//
class Button
{
private:
	//button visuals
	sf::Texture buttonTexture;
	sf::Texture buttonTexturePressed;
	sf::RectangleShape buttonShape;

	//button position on screen
	float posX, posY;
	sf::Vector2f size;
	std::string name;
public:
	bool clicked = false;

	// I've had enough of abstract classes today.
	std::function<void(class Game&)> onClick;
	std::function<void(class Game&)> onHold;
	std::function<void(class Game&)> onRelease;

	//default constructor
	Button();
	//constructor
	
	Button(std::string name, const std::string& textureFilePath, const std::string& texturePressedFilePath, float X, float Y, float sizeX, float sizeY, std::function<void(class Game&)> newOnClick = nullptr, std::function<void(class Game&)> newOnHold = nullptr, std::function<void(class Game&)> newOnRelease = nullptr);
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
	std::string getName() const;
	sf::RectangleShape& getIcon();
	void setPos(float x, float y);

	void setButtonIcon(sf::Texture texture);
	//wether or not the button is being hovered
	bool isMouseHoveringOverButton(const sf::Vector2f& cursorPos);

	void draw(sf::RenderWindow& window);

	void animatePress(CLICKSTATE action);


};



#endif // !BUTTON_H

