#include "Header.h"

class Button
{
private:
	//button visuals
	sf::Texture buttonIconTexture;
	sf::RectangleShape buttonIcon;

	//button position on screen
	float posX, posY;



public:
	std::function<void()> buttonFunction;

	//default constructor
	Button() {
		posX = 0;
		posY = 0;
	}
	//constructor
	
	Button(sf::Texture& texture, float X, float Y, std::function<void()> functionPtr) {
		buttonIcon.setTexture(&texture);
		buttonIcon.setSize(sf::Vector2f(texture.getSize().x, texture.getSize().y));
		buttonIcon.setPosition(X, Y);
		posX = X;
		posY = Y;
		buttonFunction = functionPtr;
	}
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
	Button(const Button& B) {
		buttonIconTexture = B.buttonIconTexture;
		posX = B.posX;
		posY = B.posY;
		buttonFunction = B.buttonFunction;
	}

	//deconstructor
	~Button() {}

	//getters-setters
	float getPosX() { return posX; }
	float getPosY() { return posY; }
	std::function<void()> getFuncPtr() { return buttonFunction; }
	sf::RectangleShape getIcon() { return buttonIcon; }
	void setPos(float x, float y) {
		posX = x;
		posY = y;
		buttonIcon.setPosition(posX, posY);
	}

	void setFuncPtr(std::function<void()>& funcPtr) { buttonFunction = funcPtr; }
	void setButtonIcon(sf::Texture texture) { 
		buttonIconTexture = texture; 
		buttonIcon.setTexture(&buttonIconTexture);
	}
	//wether or not the button is being hovered
	bool isHovering(const sf::Vector2i& cursorPos) {
		//because for some damn reason mouse pos is taken by INT values by default?? sfml is on drugs 
		sf::Vector2f cursorPosF(static_cast<float>(cursorPos.x), static_cast<float>(cursorPos.y));
		if (buttonIcon.getGlobalBounds().contains(cursorPosF)) {
			//mouse is hovering button!
			return true;
		}
		else return false;
	}

	//wether or not the button is being pressed
	bool isPressed(const sf::Vector2i& cursorPos) {
		if (isHovering(cursorPos)) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				//button has been pressed! if this returns true, we call the buttons function in the Buttons class!
				
				cout << "button pressed!\n";
				return true;
			}
			else return false;
		}
	}

	void draw(sf::RenderWindow& window) {
		window.draw(buttonIcon);
	}

};
