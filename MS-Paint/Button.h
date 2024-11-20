#include "Header.h"
#include "Game.h"
class Button : private Game
{
private:
	//button visuals
	sf::Texture buttonIconTexture;
	sf::RectangleShape buttonIcon;

	//button position on screen
	float posX, posY;


	//function pointers for class fuynctionality
	std::function<void()> buttonFunction;

public:
	
	//constructor
	Button(sf::Texture& texture, float X, float Y, std::function<void()> functionPtr) :
		buttonIconTexture(texture), posX(X), posY(Y), buttonFunction(functionPtr) {
		buttonIcon.setPosition(X, Y);
		buttonIcon.setTexture(&buttonIconTexture);
	}

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

	void setPos(float x, float y) {
		posX = x;
		posY = y;
		buttonIcon.setPosition(posX, posY);
	}

	void setFuncPtr(std::function<void()>& funcPtr) { buttonFunction = funcPtr; }
	
	//wether or not the button is being hovered
	bool isHovering() {
		//because for some damn reason mouse pos is taken by INT values by default?? sfml is on drugs 
		sf::Vector2f cursorPosF(static_cast<float>(cursorPos.x), static_cast<float>(cursorPos.y));
		if (buttonIcon.getGlobalBounds().contains(cursorPosF)) {
			//mouse is hovering button!
			return true;
		}
		else return false;
	}

	//wether or not the button is being pressed
	bool isPressed() {
		if (isHovering()) {
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
