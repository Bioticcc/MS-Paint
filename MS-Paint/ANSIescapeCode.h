#pragma once

#include <iostream>
using std::cout;

typedef enum EraseInLineMode
{
	RIGHT, // 0, erase line right of cursor
	LEFT,  // 1, erase line left of cursor
	LINE   // 2, erase line cursor is on
};

class ANSI
{
public:
	ANSI();
	~ANSI();
	// to (0,0)
	static void CursorToOrigin() {
		std::cout << "\033[0;0H";
	}
	// next line
	static void CursorToStartNextLine() {
		std::cout << "\033[E";
	}
	// next line
	static void CursorToStartNextLine(int n) {
		if (n > 0) {
			for (; n > 0; --n) {
				std::cout << "\033[E";
			}
		}
	}
	// prev line
	static void CursorToStartPrevLine() {
		std::cout << "\033[F";
	}
	// start this line
	static void CursorToStartThisLine() {
		std::cout << "\033[G";
	}
	// erase in line
	static void EraseInLine(EraseInLineMode mode/*0=right,1=left,2=line*/) {
		switch (mode) {
		case 0: // erase from cursor to end (right of Cur)
			std::cout << "\033[0K";
			break;
		case 1: // from begin to curs (left of Cur)
			std::cout << "\033[1K";
			break;
		case 2: // whole line
			std::cout << "\033[2K";
			break;
		}
	}
	static void EraseInLine(EraseInLineMode mode/*0=right,1=left,2=line*/, int eraseLength) {
		// \033[C - move cursor forward 1
		// \033[D - move cursor backward 1
		switch (mode) {
		case 0: // erase from cursor to end (right of Cur)
			for (; eraseLength; eraseLength--) {
				std::cout << " ";
				std::cout << "\033[C";
			}
			break;
		case 1: // from begin to curs (left of Cur)
			std::cout << "\033[D";
			for (; eraseLength; eraseLength--) {
				std::cout << " ";
				std::cout << "\033[D";
			}
			break;
		case 2: // whole line
			break;
		}
	}
	// save curs
	static void SaveCursorPos() {
		std::cout << "\033[s";
	}
	// load curs
	static void LoadCursorPos() {
		std::cout << "\033[u";
	}
	// hide curs
	static void HideCursor() {
		std::cout << "\033[?25l";
	}
	// show curs
	static void ShowCursor() {
		std::cout << "\033[?25h";
	}
	// move (Row, Col)
	static void RelMoveCursorRowCol(int changeRowBy, int changeColBy) {
		/*
		\033[A - Up
		\033[B - Down
		\033[C - Forward
		\033[D - Back
		*/
		// evalutate Rows
		if (changeRowBy > 0) {// should go down
			for (; changeRowBy > 0; --changeRowBy) {
				std::cout << "\033[B";
			}
		}
		else if (changeRowBy < 0) { // should go up
			for (; changeRowBy < 0; ++changeRowBy) {
				std::cout << "\033[A";
			}
		}

		// evaluate Cols
		if (changeColBy > 0) {// should go right
			for (; changeColBy > 0; --changeColBy) {
				std::cout << "\033[C";
			}
		}
		else if (changeColBy < 0) { // should go left
			for (; changeColBy < 0; ++changeColBy) {
				std::cout << "\033[D";
			}
		}
	}
	// abs move (Row, Col)
	static void AbsMoveCursorRowCol(int changeRowBy, int changeColBy) {
		/*
		\033[A - Up
		\033[B - Down
		\033[C - Forward
		\033[D - Back
		*/
		// evalutate Rows
		CursorToOrigin();
		if (changeRowBy > 0) {// should go down
			for (; changeRowBy > 0; --changeRowBy) {
				std::cout << "\033[B";
			}
		}
		else if (changeRowBy < 0) { // should go up
			for (; changeRowBy < 0; ++changeRowBy) {
				std::cout << "\033[A";
			}
		}

		// evaluate Cols
		if (changeColBy > 0) {// should go right
			for (; changeColBy > 0; --changeColBy) {
				std::cout << "\033[C";
			}
		}
		else if (changeColBy < 0) { // should go left
			for (; changeColBy < 0; ++changeColBy) {
				std::cout << "\033[D";
			}
		}
	}
private:

};

ANSI::ANSI()
{
}

ANSI::~ANSI()
{
}