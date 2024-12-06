#include "Button.h"

//default constructor

Button::Button() {
	posX = 0;
	posY = 0;
	name = "";
}

Button::Button(std::string name, const std::string& textureFilePath, const std::string& texturePressedFilePath, float X, float Y, float sizeX, float sizeY, std::function<void(class Game&)> newOnClick, std::function<void(class Game&)> newOnHold, std::function<void(class Game&)> newOnRelease) {
	std::cout << "\033[25;1H";
	if (!buttonTexture.loadFromFile(textureFilePath)) {
		std::cerr << "Failed to load texture from: " << textureFilePath << "\n";
	}
	else {
		buttonShape.setTexture(&buttonTexture);
	}
	
	if (!buttonTexturePressed.loadFromFile(texturePressedFilePath)) {
		std::cerr << "Failed to load texture from: " << texturePressedFilePath << "\n";
	}

	//buttonIcon.setSize(sf::Vector2f(texture.getSize().x, texture.getSize().y));
	name = name;
	size.x = sizeX;
	size.y = sizeY;
	buttonShape.setSize(size);
	buttonShape.setPosition(X, Y);
	posX = X;
	posY = Y;
	onClick = newOnClick;
	onHold = newOnHold;
	onRelease = newOnRelease;
	clicked = false;
}

//copy constructor

Button::Button(const Button& B) {
	name = B.name;
	buttonTexture= B.buttonTexture;
	buttonShape = B.buttonShape;
	posX = B.posX;
	posY = B.posY;
	size = B.size;
	clicked = B.clicked;
	onClick = B.onClick;
	onHold = B.onHold;
	onRelease = B.onRelease;
}

//deconstructor

Button::~Button() { return; }

//getters-setters

float Button::getPosX() { return posX; }

float Button::getPosY() { return posY; }

std::string Button::getName() const { return name; }

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

/*
Programmed by: Bioticcc
	Edited by: Inventor4life

	returns true if the mouse position is within the bounds of the button.
*/
bool Button::isMouseHoveringOverButton(const sf::Vector2f& cursorPos) {
	
	if (buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(cursorPos))) {
		//mouse is hovering over button!
		return true;
	}
	else return false;
}

void Button::draw(sf::RenderWindow& window) {
	window.draw(buttonShape);
}

void Button::animatePress(CLICKSTATE action)
{
	switch (action) {
	case PRESS:
		buttonShape.setTexture(&buttonTexturePressed);
		break;
	case RELEASE:
		buttonShape.setTexture(&buttonTexture);
		break;
	}
}
