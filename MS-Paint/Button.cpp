#include "Button.h"

//default constructor

inline Button::Button() {
	posX = 0;
	posY = 0;
}

inline Button::Button(sf::Texture& texture, float X, float Y, std::function<void()> functionPtr, float sizeX, float sizeY) {
	buttonIcon.setTexture(&texture);
	//buttonIcon.setSize(sf::Vector2f(texture.getSize().x, texture.getSize().y));
	size.x = sizeX;
	size.y = sizeY;
	buttonIcon.setSize(size);
	buttonIcon.setPosition(X, Y);
	posX = X;
	posY = Y;
	buttonFunction = functionPtr;
	clicked = false;
}

//copy constructor

inline Button::Button(const Button& B) {
	buttonIconTexture = B.buttonIconTexture;
	posX = B.posX;
	posY = B.posY;
	buttonFunction = B.buttonFunction;
}

//deconstructor

inline Button::~Button() {}

//getters-setters

inline float Button::getPosX() { return posX; }

inline float Button::getPosY() { return posY; }

inline std::function<void()> Button::getFuncPtr() { return buttonFunction; }

inline sf::RectangleShape Button::getIcon() { return buttonIcon; }

inline void Button::setPos(float x, float y) {
	posX = x;
	posY = y;
	buttonIcon.setPosition(posX, posY);
}

inline void Button::setFuncPtr(std::function<void()>& funcPtr) { buttonFunction = funcPtr; }

inline void Button::setButtonIcon(sf::Texture texture) {
	buttonIconTexture = texture;
	buttonIcon.setTexture(&buttonIconTexture);
}

//wether or not the button is being hovered

inline bool Button::isHovering(const sf::Vector2i& cursorPos) {
	//because for some damn reason mouse pos is taken by INT values by default?? sfml is on drugs 
	sf::Vector2f cursorPosF(static_cast<float>(cursorPos.x), static_cast<float>(cursorPos.y));
	if (buttonIcon.getGlobalBounds().contains(cursorPosF)) {
		//mouse is hovering button!
		return true;
	}
	else return false;
}

//wether or not the button is being pressed

inline bool Button::isPressed(const sf::Vector2i& cursorPos) {
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

inline void Button::draw(sf::RenderWindow& window) {
	window.draw(buttonIcon);
}
