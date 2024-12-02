#pragma once
#ifndef BUTTONS_H
#define BUTTONS_H // TODO rename to be less similar to BUTTON_H

#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include "Button.h"
#include "Tool.h"


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
	sf::Texture texturePLUS;
	sf::Texture textureMINUS;
	float size;
public:
	sf::RenderWindow* window;
	std::vector<sf::CircleShape> inkDots;

	std::vector<Button> buttonVect;
	Button select;
	Button pencil;
	Button eraser;
	Button clear;
	Button save;
	Button pencilR;
	Button pencilB;
	Button pencilG;
	Button increase;
	Button decrease;


	//constructor
	Buttons(sf::RenderWindow* renderWindow);

	//since I seem to need it so damn much im making a function that gets me the RenderWindow ob

	//these functions should later be held within tools.
	void selectButton();

	void pencilButton();

	void eraserButton();

	void clearButton();

	void saveButton();

	void pencilButtonR();

	void pencilButtonB();

	void pencilButtonG();

	void increaseSize();
	void decreaseSize();

	void buttonConstructor();

	void drawButtons();

};

#endif // !BUTTONS_H
