//#include "Header.h"
#include "Game.h"
#include "TestCases.h"

int main(void) {

	TestCases T;
	T.testSave();
	T.testPickTool();
	T.testDraw();
	T.testChangeColor();
	T.testAddButton();
	
	std::cout << std::endl << std::endl;
	std::cout << "!!!!Make Sure to Click into the Window!!!!" << std::endl;
	std::cout << "PRESS ANY KEY TO CONTINUE...";
	system("pause > nul");
	system("cls");

	Game G;
	G.runGame();
}
