#include "Button.h"
// Programmed by Bioticcc
//  Edited by Inventor4life
//            FloatingToa5t
//            david_ac_leon    
//
// Assignment: PA 9
// File: Button.cpp
// Description:
//  The member functions for the Button class. The button class is meant to 
//	store the button texture, location, size, and its function. If the button
//	press triggers a change in pencil, undo, or some other thing
//	storing the function for the button and its texture allows us to 
//	encapsulate things, keep functions nice and neat and most importantly,
//	combat SFML's insitence on making textures dissapear if you go outside
//	the scope of the function it was declared in.

//Programmed by Bioticcc
//  Edited by Inventor4life
//            FloatingToa5t
//            david_ac_leon 
// Description: 
// Just the default constructor when given no arguments. Entirely pointless as its never used, but nice to have
// so the code doesnt kill itself on the offchance you DO forget your arguments
Button::Button() {
	posX = 0;
	posY = 0;
	name = "";
}

// Programmed by Bioticcc
//  Edited by Inventor4life
//            FloatingToa5t
//            david_ac_leon 
//Discussion:
// The actual constructor, the one that is used. The most important aspect of this is keeping our textures stored in
// the button class, as otherwise they would simply vanish when we left the function in witch
// they were initially set, even  if the sprite whos texture was changed WAS stored somewhere.
// Additionally, it takes in everything else the button needs to be created so we can 
// fully make a button in a single line of code, making for lots of readability and general clealiness
//
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

//Programmed by Bioticcc
//  Edited by Inventor4life
//            FloatingToa5t
//            david_ac_leon 
//Discussion:
// The copy constructor! on the off chance we need multiple of one button, this is rather handy.
//
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

//Programmed by Bioticcc
//  Edited by Inventor4life
//            FloatingToa5t
//            david_ac_leon 
//Discussion:
// Deconstructor! deconstructs.

Button::~Button() { return; }

//getters-setters

//Programmed by Bioticcc
//  Edited by Inventor4life
//            FloatingToa5t
//            david_ac_leon 
//Discussion:
//	returns the buttons X position on the screen. I believe it is specifically the top leftmost corner.

float Button::getPosX() { return posX; }

//Programmed by Bioticcc
//  Edited by Inventor4life
//            FloatingToa5t
//            david_ac_leon 
//Discussion:
//	returns the buttons Y position on the screen. I believe it is specifically the top leftmost corner.

float Button::getPosY() { return posY; }

//Programmed by Bioticcc
//  Edited by Inventor4life
//            FloatingToa5t
//            david_ac_leon 
//Discussion:
// returns the name of the button
std::string Button::getName() const { return name; }

//Programmed by Bioticcc
//  Edited by Inventor4life
//            FloatingToa5t
//            david_ac_leon 
//Discussion:
// returns the button sprite, witch SHOULD contain its texture due to us storing it within the class. 
// helpful for when we need to draw the buttons to the screen!
sf::RectangleShape& Button::getIcon() { return buttonShape; }

//Programmed by Bioticcc
//  Edited by Inventor4life
//            FloatingToa5t
//            david_ac_leon 
//Discussion:
// Sets the buttons x and y positions on the screen.
void Button::setPos(float x, float y) {
	posX = x;
	posY = y;
	buttonShape.setPosition(posX, posY);
}


//Programmed by Bioticcc
//  Edited by Inventor4life
//            FloatingToa5t
//            david_ac_leon 
//Discussion:
// Changes button texture, helpful for animations, and changing texture based on other factors.
void Button::setButtonIcon(sf::Texture texture) {
	buttonTexture = texture;
	buttonShape.setTexture(&buttonTexture);
}

//wether or not the button is being hovered

/*
Programmed by: Bioticcc
	Edited by: Inventor4life
			   FloatingToa5t
               david_ac_leon

function:
	Button::isMouseHoveringOverButton

parameters:
	const sf::Vector2f& cursorPos - Current cursor position

returns:
	True - The current mouse position is on top of the button
	False - otherwise
*/
bool Button::isMouseHoveringOverButton(const sf::Vector2f& cursorPos) {
	
	if (buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(cursorPos))) {
		//mouse is hovering over button!
		return true;
	}
	else return false;
}

//Programmed by Bioticcc
//  Edited by Inventor4life
//            FloatingToa5t
//            david_ac_leon 
//Discussion:
// Draws the button icon to the window address given

void Button::draw(sf::RenderWindow& window) {
	window.draw(buttonShape);
}

//Programmed by FloatingToa5t
//  Edited by Inventor4life
//            david_ac_leon 
//Discussion:
// does a fancy lil animation by changing the buttons texture on press, then changing it back!

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
