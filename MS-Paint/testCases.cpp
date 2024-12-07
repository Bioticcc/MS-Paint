#pragma once

#include "TestCases.h"
#include "Game.h"

TestCases::TestCases()
{
}

TestCases::~TestCases()
{
}

void TestCases::testSave()
{
	Game G;
}

void TestCases::testPickTool()
{
	Game G; // brush is grey 
	G.setTool(new PencilTool()); // pencil with white color
	if (dynamic_cast<PencilTool*>(G.currentTool.get()) != nullptr) // canvas brush will be white with eraser tool
	{
		std::cout << "Change Tool Test - task successful";
	}
	else {
		std::cout << "Change Tool Test - task failed" << std::endl;
	}
}

void TestCases::testDraw()
{
	Game G; 
}

void TestCases::testChangeColor()
{
	Game G;
}

void TestCases::testButtonPress()
{
	Game G;
}
