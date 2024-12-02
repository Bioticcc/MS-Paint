#include "Button.h"


//default constructor

Button::Button() {
	posX = 0;
	posY = 0;
}

Button::Button(sf::Texture& texture, float X, float Y, std::function<void(class Game&)> functionPtr, float sizeX, float sizeY) {
	buttonShape.setTexture(&texture);
	//buttonIcon.setSize(sf::Vector2f(texture.getSize().x, texture.getSize().y));
	size.x = sizeX;
	size.y = sizeY;
	buttonShape.setSize(size);
	buttonShape.setPosition(X, Y);
	posX = X;
	posY = Y;
	onClick = functionPtr;
	clicked = false;
}

//copy constructor

Button::Button(const Button& B) {
	buttonTexture = B.buttonTexture;
	posX = B.posX;
	posY = B.posY;
	onClick = B.onClick;
}

//deconstructor

Button::~Button() { return; }

//getters-setters

float Button::getPosX() { return posX; }

float Button::getPosY() { return posY; }

sf::RectangleShape Button::getIcon() { return buttonShape; }

void Button::setPos(float x, float y) {
	posX = x;
	posY = y;
	buttonShape.setPosition(posX, posY);
}


void Button::setButtonIcon(sf::Texture texture) {
	buttonTexture = texture;
	buttonShape.setTexture(&buttonTexture);
}

//wether or not the button is being hovered

bool Button::isHovering(const sf::Vector2i& cursorPos) {
	//because for some damn reason mouse pos is taken by INT values by default?? sfml is on drugs 
	if (buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(cursorPos))) {
		//mouse is hovering button!
		return true;
	}
	else return false;
}

//wether or not the button is being pressed

bool Button::isPressed(const sf::Vector2i& cursorPos) {
	if (isHovering(cursorPos)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (!clicked) { // Check if the button is not already clicked
				clicked = true; // Mark as clicked
				cout << "button pressed!\n";
				return true;
			}
		}
		else {
			clicked = false; // Reset on mouse release
		}
	}
	return false;
}

void Button::draw(sf::RenderWindow& window) {
	window.draw(buttonShape);
}
