// Programmed by Bioticcc
//  Edited by Inventor4life
//            FloatingToa5t
//            david_ac_leon
//        
// Assignment: PA9
// File: Game.cpp
// Description:
//  Contains all functions needed to use the game class.
//     

#include "Game.h"
#include "ANSIescapeCode.h"
#include "string"


using std::endl;

#define MIN_BRUSH_SIZE 1.f
#define SLIDER_DOT_RADIUS 8.f
#define SLIDER_DOT_RESOLUTION 12.f

#define CANVAS_W 1942.0f
#define CANVAS_H 1080.0f

/*
Programmed by: Bioticcc
    Edited by: Inventor4life
               FloatingToa5t
               david_ac_leon

function:
    Gamge::Game()

description:
    Constructor for the game class. Initializes variables, loads all buttons and toolbar.

parameters:
    none

returns:
    none
*/
Game::Game() : resX(1920), resY(1080), window(sf::VideoMode(resX, resY), windowName)/*, allButtons(&window)*/ {
    if (!toolbarTexture.loadFromFile("Backgrounds/Toolbar.png")) {
        std::cerr << "Failed to load background texture\n";
    }
    toolbar.setTexture(toolbarTexture);

    // generate a completely white canvas
    canvasRenderTexture.create(1492, 1080);
    canvasRenderTexture.clear(sf::Color::White);

    canvas.setTexture(canvasRenderTexture.getTexture(), true);

    canvas.setPosition(428, 0);

    timesSaved = 0;

    allSliderPos = { 127,127,127,255 };
    this->currentColor = sf::Color(127,127,127,255);
    this->setTool(new PencilTool()); // Set default tool

    initializeButtons(*this);
}


/*
Programmed by: Bioticcc
    Edited by: Inventor4life
               FloatingToa5t
               david_ac_leon

function:
    void Game::runGame()

description:
    Entry point for the application. Launches and manages a BigHard Paint window. Returns when the window is closed.

parameters:
    none

returns:
    none
*/
void Game::runGame() {
    using std::cout; //skull emoji
    //currentTool = 1; //by default our starting tool will be 1 (select, ie standard cursor)


    //Edging Variables
    const bool PRESSED = true;
    bool mouseLeftPreviousState = false; // Stores whether the left mouse button was pressed or not in the previous frame
    bool mouseLeftCurrentState = false;
    bool mouseLeftPosEdge = false;        // True only for the frame where mouse left went not_pressed->pressed
    bool mouseLeftNegEdge = false;        // True only for the frame where mouse left went pressed->not_pressed

    // Draw Slider Dots
    sf::CircleShape sliderDot(SLIDER_DOT_RADIUS, SLIDER_DOT_RESOLUTION);
    sliderDot.setPosition(30.0f, 600.0f);
    sliderDot.setFillColor(sf::Color::Black);
    sliderDot.setOrigin(SLIDER_DOT_RADIUS, SLIDER_DOT_RADIUS);

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::Resized) {
                // Fix the scales of the universe (why 137?)
            }
        }
        // Display window info
        displayInfo();

        if (window.hasFocus()) {
            // Edging Code
            mouseLeftCurrentState = sf::Mouse::isButtonPressed(sf::Mouse::Left);
            if (mouseLeftPreviousState != mouseLeftCurrentState) { // True for changes in state. Opportunity for some horrific one-line ifs
                if (mouseLeftPreviousState == !PRESSED) {
                    mouseLeftPosEdge = true;
                }
                else {
                    mouseLeftNegEdge = true;
                }
            }
            else {
                mouseLeftPosEdge = false;
                mouseLeftNegEdge = false;
            }
            mouseLeftPreviousState = mouseLeftCurrentState;


            // Code to handle mouse clicks and motion. Undefined behavior if mouse goes off-window.
            cursorPosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
            if (canvas.getGlobalBounds().contains(cursorPosition)) { // If mouse on Canvas
                cursorCanvasPosition = cursorPosition - canvas.getPosition();
                cursorCanvasPosition.y = 1080 - cursorCanvasPosition.y;
                currentTool.get()->mouseMotion(*this, cursorPosition);

                if (mouseLeftPosEdge) {
                    //cout << "mouse pos (x,y): " << cursorCanvasPosition.x << "," << cursorCanvasPosition.y << std::endl;
                    currentTool.get()->mouseDown(*this, cursorCanvasPosition);
                    currentTool.get()->in_use = true;
                }
                else if (mouseLeftCurrentState == PRESSED && currentTool.get()->in_use) {
                    // Notice: This causes a bug where the drag stops before hitting the edge of the canvas, as the mouse was
                    //  Off-canvas in the next frame. Only noticeable on slow computers or fast canvas strokes.
                    currentTool.get()->mouseDrag(*this, cursorCanvasPosition);
                }
            }
            else if (toolbar.getGlobalBounds().contains(cursorPosition)) { // If mouse on Toolbar
                if (mouseLeftPosEdge) { // true for rising edge of click
                    //cout << "mouse pos (x,y): " << cursorPosition.x << "," << cursorPosition.y << std::endl;

                    for (Button* i : allButtons) {
                        if (i->isMouseHoveringOverButton(cursorPosition)) {
                            if (i->onClick != nullptr) i->onClick(*this); // Pass the Game object, so buttons can trigger anything.
                            i->clicked = true;
                        }
                    }
                }
                else if (mouseLeftCurrentState == PRESSED) { // Called once per frame that mouse left is held down after clicking button, while mouse is in toolbar.
                    for (Button* i : allButtons) {
                        if (i->clicked == true && i->onHold != nullptr) {
                            i->onHold(*this); // Pass the Game object, so buttons can trigger anything.
                        }
                    }
                }
            }

            if (mouseLeftNegEdge) { // True only for falling edge of click (i.e. on release)
                for (Button* i : allButtons) {
                    if (i->clicked == true) {
                        if (i->onRelease != nullptr) i->onRelease(*this);
                        i->clicked = false;
                    }
                }
                if (currentTool.get()->in_use) {
                    currentTool.get()->mouseUp(*this, cursorCanvasPosition); // Passes the last valid mouse position.
                    currentTool.get()->in_use = false;
                }

                // Save Canvas State for undo and Redo
                // Here for the reason of saving states after a full line is drawn
                if (cursorCanvasPosition.x > 0 && cursorCanvasPosition.x < CANVAS_W
                    && cursorCanvasPosition.y > 0 && cursorCanvasPosition.y < CANVAS_H) {
                    redoUndoVector.push_back(canvas);
                }
            }
            // Rendering
            window.display(); // So that changes made to window in tool can be seen.
            window.clear();
            window.draw(canvas);
            window.draw(toolbar);
            for (Button* i : allButtons) {
                i->draw(window);
            }

            // Display the Current Canvas Color
            sf::RectangleShape colorPreview;
            colorPreview.setSize(sf::Vector2f(100, 100)); // Set preview size
            colorPreview.setPosition(315.0f, 595.0f); // Position below the sliders
            colorPreview.setFillColor(currentColor); // Update the color preview
            window.draw(colorPreview);

            // Draw the Slider Dots
            for (int i = 0; i < 4; i++) {
                sliderDot.setPosition(allSliderPos[i] + 30.0f, 605.f + (40 * i));
                window.draw(sliderDot);
            }
        }
    }
}


/*
Programmed by: Bioticcc
    Edited by: Inventor4life
               FloatingToa5t
               david_ac_leon

function:
    void Game::setTool(Tool* newTool)

description:
    Sets the window's current active tool (CAT™) to the tool passed.

parameters:
    Tool* newTool - Pointer to a desired Tool object located in heap

returns:
    None
*/
void Game::setTool(Tool* newTool)
{
    if (currentTool.get() != nullptr) currentTool.get()->toolDeselect(*this);
    currentTool.reset(newTool); // Deallocates the old tool and sets it to the new one.
    currentTool.get()->toolSelect(*this);
}


/*
Programmed by: Bioticcc
    Edited by: Inventor4life
               FloatingToa5t
               david_ac_leon

function:
    Game::updateTool(void)

description:
    Calls the relevant tool toolUpdate function. 
    Should be called whenever an important value is changed (color, size) (etc...)

parameters:
    None

returns:
    None
*/
void Game::updateTool(void) {
    currentTool.get()->toolUpdate(*this);
}


/*
Programmed by: Bioticcc
    Edited by: Inventor4life
               FloatingToa5t
               david_ac_leon

function:
    Game::addButton(Button* newButton)

description:
    Calls the relevant tool toolUpdate function.
    Should be called whenever an important value is changed (color, size) (etc...)

parameters:
    None

returns:
    None
*/
void Game::addButton(Button* newButton)
{
    allButtons.push_back(newButton);
}

//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: getWindowReference
// Parameters: None
// Return Values: sf::RenderWindow& - reference to the game's main window
// Description:
// Returns a reference to the main SFML window.
//
sf::RenderWindow& Game::getWindowReference(void)
{
    return this->window;
}

//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: drawToCanvas
// Parameters: sf::Shape& toStamp
// Return Values: None
// Description:
// Draws a given shape onto the canvas' render texture and updates the canvas sprite.
//
void Game::drawToCanvas(sf::Shape& toStamp) {
    canvasRenderTexture.draw(toStamp);
    canvas.setTexture(canvasRenderTexture.getTexture());
}

//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: getColor
// Parameters: None
// Return Values: sf::Color - the current selected color
// Description:
// Returns the currently selected drawing color.
//
sf::Color Game::getColor() const
{
    return currentColor;
}

//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: getButtonCount
// Parameters: None
// Return Values: int - the number of buttons in allButtons vector
// Description:
// Returns how many buttons have been added to the game.
//
int Game::getButtonCount() const
{
    int buttonCount = 0;
    for (auto i : allButtons) {
        buttonCount++;
    }
    return buttonCount;
}

//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: displayInfo
// Parameters: None
// Return Values: None
// Description:
// Prints debug information to the terminal using ANSI escape codes,
// including cursor positions, brush size, color, and window size.
//
void Game::displayInfo() const
{
    using std::cout;
    /* EXAMPLE INFO DISPLAY
    SystemTime: Yadda yadda hooey hooey
    CursorPos..........| 123, 1234
    CursorCanvasPos....| 123, 1234

    BurshSize..........|   15
    BrushColor.........| R 77
              .........| G 23
              .........| B 53
              .........| a 12

    LastButtonPressed..| pencil
    LastButtonRelease..| eyeDropper
    NumberofButtons....| 9

    LastSaveTime.......| 12 / 5 / 24 / 11:35 : 00
    TimesSaved.........| 3

    WindowW............| 1920
    WindowH............| 1080
    */

    // clear the debug screen
        // all lines except where it says "print here" because the strings
        // there are printed from the button functions
    ANSI::HideCursor();
    ANSI::AbsMoveCursorRowCol(2, 22);
    for (int i = 0; i < 8; i++) {
        ANSI::EraseInLine(RIGHT);
        ANSI::RelMoveCursorRowCol(1, 0);
    };

    // Print window Size
    ANSI::AbsMoveCursorRowCol(18, 21);
   std::cout << window.getSize().x;
    ANSI::AbsMoveCursorRowCol(19, 21);
   std::cout << window.getSize().y;

    ANSI::AbsMoveCursorRowCol(1, 1); // move cursor to top left of the console
    sf::Color color = getColor(); // grab the current color


    // get the system time
    std::time_t now = std::time(nullptr);
    struct tm buf;
    localtime_s(&buf, &now);
    char timestamp[20];
    std::strftime(timestamp, sizeof(timestamp), "%Y/%m/%d-%H:%M:%S", &buf);

    cout << "SystemTime: " << timestamp << endl;
    cout << "CursorPos..........| x" << cursorPosition.x << " y" << cursorPosition.y << endl;
    cout << "CursorCanvasPos....| x" << cursorCanvasPosition.x << " y" << cursorCanvasPosition.y << endl;
    cout << endl;
    cout << "BurshSize..........| "  << brushSize << endl;
    cout << "BrushColor.........| r" << static_cast<float>(color.r) << endl;
    cout << "           ........| g" << static_cast<float>(color.g) << endl;
    cout << "            .......| b" << static_cast<float>(color.b) << endl;
    cout << "             ......| a" << static_cast<float>(color.a) << endl;
    cout << endl;
    cout << "LastButtonPressed..| " << endl; // print here at 11,22 in the button click functions
    cout << "LastButtonReleased.| " << endl; // print here at 12,22 in the button release funtions
    cout << "NumberofButtons....| " << getButtonCount() << endl;
    cout << endl;
    cout << "LastSaveTime.......| " << endl; // print here at 15,22
    cout << "TimesSaved.........| " << timesSaved << endl; // print here at 16,22
    cout << endl;
    cout << "WindowW............| " << endl; // print here at 18,22
    cout << "WindowH............| " << endl; // print here at 19,22
    cout << endl;
    cout << "CanvasStatesSaved..| " << getCanvasStatesSaved();
}

//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: getCursorPos_Vector2f
// Parameters: None
// Return Values: sf::Vector2f - current cursor position relative to window
// Description:
// Returns the current cursor position in window coordinates.
//
sf::Vector2f Game::getCursorPos_Vector2f() const
{
    return this->cursorPosition;
}

//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: getCursorCanvasPos_Vector2f
// Parameters: None
// Return Values: sf::Vector2f - current cursor position relative to the canvas
// Description:
// Returns the current cursor position mapped onto the canvas space.
//
sf::Vector2f Game::getCursorCanvasPos_Vector2f() const
{
    return this->cursorCanvasPosition;
}

//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: getCanvas
// Parameters: None
// Return Values: sf::Sprite& - reference to the current canvas sprite
// Description:
// Returns a reference to the current canvas sprite.
//
sf::Sprite& Game::getCanvas()
{
    return this->canvas;
}

//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: setCanvas
// Parameters: sf::Sprite newCanvas
// Return Values: None
// Description:
// Updates the current canvas sprite with a new sprite.
//
void Game::setCanvas(sf::Sprite newCanvas)
{
    this->canvas = newCanvas;
}

//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: getCanvasStatesSaved
// Parameters: None
// Return Values: int - number of saved canvas states
// Description:
// Returns how many states of the canvas are stored for undo functionality.
//
int Game::getCanvasStatesSaved() const
{
    int count = 0;
    for (auto i : redoUndoVector) {
        count++;
    }
    return count;
}

//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: incramentSaveCounter
// Parameters: None
// Return Values: None
// Description:
// Increments the timesSaved counter each time a drawing is saved.
//
void Game::incramentSaveCounter()
{
    timesSaved++;
}

// Below are callback functions for buttons and the initializeButtons function.
// They are all considered non-member functions and thus need block comments as well.

//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: saveButtonClick
// Parameters: Game& masterGame
// Return Values: None
// Description:
// Called when the save button is clicked. Animates the button and prints info to the console.
//
void saveButtonClick(Game& masterGame) {
    // print button on info screen
    ANSI::AbsMoveCursorRowCol(11, 21);
    ANSI::EraseInLine(RIGHT);
   std::cout << "SAVE";

    //animate button
    masterGame.allButtons[0]->animatePress(PRESS);
}

//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: saveButtonHold
// Parameters: Game& masterGame
// Return Values: None
// Description:
// Called each frame the save button is held. Currently does nothing.
//
void saveButtonHold(Game& masterGame) {
}

//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: saveButtonRelease
// Parameters: Game& masterGame
// Return Values: None
// Description:
// On release of save button, saves the current canvas to a file and updates timestamp.
//
void saveButtonRelease(Game& masterGame) {

    // Capture Canvas and Save to file
    /*sf::Texture screenshotTexture;
    screenshotTexture.create(masterGame.getWindowReference().getSize().x, masterGame.getWindowReference().getSize().y);
    screenshotTexture.update(masterGame.getWindowReference());*/
    // Under the grace our Lord and Savior Ethan Goode, he has figured out how
    // to take screenshots on the canvas only rather than the entire window
    // using the getCanvas() func which returns a reference
    sf::Image screenshot = masterGame.getCanvas().getTexture()->copyToImage();
    std::time_t now = std::time(nullptr);
    struct tm buf;
    localtime_s(&buf, &now);
    char timestamp[20];
    std::strftime(timestamp, sizeof(timestamp), "%Y%m%d%H%M%S", &buf);
    std::string filename = "SavedDrawings/drawing_" + std::string(timestamp) + ".png";
    screenshot.saveToFile(filename);

    // incrament counter & Write Save Time Stamp
    masterGame.incramentSaveCounter();
    ANSI::AbsMoveCursorRowCol(15, 21);
    std::strftime(timestamp, sizeof(timestamp), "%Y/%m/%d-%H:%M:%S", &buf);
   std::cout << timestamp;

    //animate button
    masterGame.allButtons[0]->animatePress(RELEASE);
}
/*
Programmed by: FloatingToa5t
Scope: All Button click,hold,release functionality 
       excluding: Save Basic_Eraser, Basic_Pencil, RGBA Sliders
*/
//==========default pencil, Black==========
void pencilButtonClick(Game& masterGame) {
    // print button on info screen
    ANSI::AbsMoveCursorRowCol(11, 21);
    ANSI::EraseInLine(RIGHT);
   std::cout << "BLACK PENCIL";

    // Change Color
    masterGame.currentColor = sf::Color::Black;
    masterGame.setTool(new PencilTool());

    // animate press
    masterGame.allButtons[1]->animatePress(PRESS);
    // MAKE SURE THE ELEME^NT HERE MATCHES IN THE ORDER IT WAS ADDED TO THE VECTOR
    // I wanna add a public element to the buttons so I can search and return buttons such that we could
    // give buttons an string member to search for them by thus getting rid of this hardcoding
}


void pencilButtonHold(Game& mastergame) {
}

//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: pencilButtonRelease
// Parameters: Game& masterGame
// Return Values: None
// Description:
// On release of the black pencil button, updates info and returns to unpressed texture.
//
void pencilButtonRelease(Game& masterGame) {
    ANSI::AbsMoveCursorRowCol(12, 21);
    ANSI::EraseInLine(RIGHT);
   std::cout << "BLACK PENCIL";

    // change texture to UnPressed
    masterGame.allButtons[1]->animatePress(RELEASE);
}


//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: pencilRedButtonClick
// Parameters: Game& masterGame
// Return Values: None
// Description:
// Selects a red pencil and sets the tool color to red on click.
//
//==========default pencil, Red==========
void pencilRedButtonClick(Game& masterGame) {
    // print button on info screen
    ANSI::AbsMoveCursorRowCol(11, 21);
    ANSI::EraseInLine(RIGHT);
   std::cout << "RED PENCIL";

    // change color to black
    masterGame.currentColor = sf::Color::Red;
    masterGame.setTool(new PencilTool());

    // change texture to pressed
    masterGame.allButtons[2]->animatePress(PRESS);
}

// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: pencilRedButtonRelease
// Parameters: Game& masterGame
// Return Values: None
// Description:
// On release of the red pencil button, updates info and returns to unpressed texture.
//
void pencilRedButtonHold(Game& mastergame) {
    //std::cout << "RED HOLDING" << std::endl;
}

//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: undoButtonClick
// Parameters: Game& masterGame
// Return Values: None
// Description:
// On clicking undo, revert to the last canvas state if available, and animate the button.
//
void pencilRedButtonRelease(Game& masterGame) {
    // print button on info screen
    ANSI::AbsMoveCursorRowCol(12, 21);
    ANSI::EraseInLine(RIGHT);
   std::cout << "RED PENCIL";

    // change texture to UnPressed
    masterGame.allButtons[2]->animatePress(RELEASE);
}


//==========UNDO ACTION==========
void undoButtonClick(Game& masterGame) {
    // print button on info screen
    ANSI::AbsMoveCursorRowCol(11, 21);
    ANSI::EraseInLine(RIGHT);

    // Go to last board state (no redo so use wisely)
    if (!masterGame.redoUndoVector.empty()) {
       /* sf::RectangleShape undidCanvas;
        undidCanvas.setSize(sf::Vector2f(CANVAS_W,CANVAS_H));
        undidCanvas.setOrigin(sf::Vector2f(CANVAS_W, CANVAS_H));
        undidCanvas.rotate(180);
        undidCanvas.setTexture(masterGame.redoUndoVector.back().getTexture());
        masterGame.drawToCanvas(undidCanvas);
        masterGame.redoUndoVector.pop_back();*/
       std::cout << "UNDO " << masterGame.getCanvasStatesSaved();
    }
    else {
       std::cout << "UNDO (EMPTY)";
    }


    // Silly spin animation
    /*float buttonSize = masterGame.allButtons[3]->getIcon().getSize().x;
    masterGame.allButtons[3]->getIcon().setOrigin(buttonSize / 2, buttonSize / 2);*/
    
    // change texture to pressed
    masterGame.allButtons[3]->animatePress(PRESS);

}
void undoButtonHold(Game& mastergame) {

    //mastergame.allButtons[3]->getIcon().rotate(1);
}

//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: undoButtonRelease
// Parameters: Game& masterGame
// Return Values: None
// Description:
// On release of the undo button, updates info and reverts button texture.
//
void undoButtonRelease(Game& masterGame) {
    // print button on info screen
    ANSI::AbsMoveCursorRowCol(12, 21);
    ANSI::EraseInLine(RIGHT);

    // change texture to UnPressed
    masterGame.allButtons[3]->animatePress(RELEASE);
}

//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: clearCanvasButtonClick
// Parameters: Game& masterGame
// Return Values: None
// Description:
// Clears the entire canvas when this button is clicked.
//
//==========clearCanvas==========
void clearCanvasButtonClick(Game& masterGame) {
    // print button on info screen
    ANSI::AbsMoveCursorRowCol(11, 21);
    ANSI::EraseInLine(RIGHT);
   std::cout << "CLEAR CANVAS";

    // Clear the Screen
    sf::RectangleShape bigAssSquare(sf::Vector2f(3000,3000));
    bigAssSquare.setFillColor(sf::Color::White);
    masterGame.drawToCanvas(bigAssSquare);

    // change texture to pressed
    masterGame.allButtons[4]->animatePress(PRESS);
}
void clearCanvasButtonHold(Game& mastergame) {
}


//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: clearCanvasButtonRelease
// Parameters: Game& masterGame
// Return Values: None
// Description:
// On release of the clear canvas button, updates info and resets button texture.
//
void clearCanvasButtonRelease(Game& masterGame) {
    // print button on info screen
    ANSI::AbsMoveCursorRowCol(12, 21);
    ANSI::EraseInLine(RIGHT);
   std::cout << "CLEAR CANVAS";
   
    // change texture to UnPressed
    masterGame.allButtons[4]->animatePress(RELEASE);
}

//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: eraserButtonClick
// Parameters: Game& masterGame
// Return Values: None
// Description:
// Switches the tool to EraserTool and updates display.
//
//==========default eraser==========
void eraserButtonClick(Game& masterGame) {
    // print button on info screen
    ANSI::AbsMoveCursorRowCol(11, 21);
    ANSI::EraseInLine(RIGHT);
   std::cout << "ERASER";

    // change to eraser tool
    masterGame.setTool(new EraserTool());
    
    // change texture to pressed
    masterGame.allButtons [5] ->animatePress(PRESS);
}


void eraserButtonHold(Game& masterGame) {
}

//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: eraserButtonRelease
// Parameters: Game& masterGame
// Return Values: None
// Description:
// On release of the eraser button, updates info and reverts texture.
//
void eraserButtonRelease(Game& masterGame) {
    // print button on info screen
    ANSI::AbsMoveCursorRowCol(12, 21);
    ANSI::EraseInLine(RIGHT);
   std::cout << "ERASER";

    // change texture to UnPressed
    masterGame.allButtons[5]->animatePress(RELEASE);
}

//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: sizeIncreaseButtonClick
// Parameters: Game& masterGame
// Return Values: None
// Description:
// Increases brush size slightly on click and updates the tool.
//
//==========default brush size increase==========
void sizeIncreaseButtonClick(Game& masterGame) {
    // print button on info screen
    ANSI::AbsMoveCursorRowCol(11, 21);
    ANSI::EraseInLine(RIGHT);
   std::cout << "SIZE INCREASE";

    masterGame.brushSize += .75;
    masterGame.updateTool();
    
    // change texture to UnPressed
    masterGame.allButtons[6]->animatePress(PRESS);
}

//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: sizeIncreaseButtonRelease
// Parameters: Game& masterGame
// Return Values: None
// Description:
// On release, updates info and reverts texture of size increase button.
//
void sizeIncreaseButtonHold(Game& masterGame) {
    masterGame.brushSize += .1;
    masterGame.updateTool();

    // Show Changing Size
    sf::CircleShape sizeIndicator;
    sizeIndicator.setPosition(1180, 540);
    sizeIndicator.setRadius((float)masterGame.brushSize);
    sizeIndicator.setFillColor(sf::Color::Transparent);
    sizeIndicator.setOutlineColor(sf::Color::Black);
    sizeIndicator.setOutlineThickness(1.0);
    sizeIndicator.setOrigin(sizeIndicator.getRadius(), sizeIndicator.getRadius());
    masterGame.getWindowReference().draw(sizeIndicator);
}

//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: sizeDecreaseButtonClick
// Parameters: Game& masterGame
// Return Values: None
// Description:
// Decreases brush size on click if above minimum.
//
void sizeIncreaseButtonRelease(Game& masterGame) {
    // print button on info screen
    ANSI::AbsMoveCursorRowCol(12, 21);
    ANSI::EraseInLine(RIGHT);
   std::cout << "SIZE INCREASE";

    // change texture to UnPressed
    masterGame.allButtons[6]->animatePress(RELEASE);
}

//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: sizeDecreaseButtonRelease
// Parameters: Game& masterGame
// Return Values: None
// Description:
// On release, updates info and restores texture for size decrease button.
//
//==========efault brush size decrease==========
void sizeDecreaseButtonClick(Game& masterGame) {
    // print button on info screen
    ANSI::AbsMoveCursorRowCol(11, 21);
    ANSI::EraseInLine(RIGHT);
   std::cout << "SIZE DECREASE";

    if (masterGame.brushSize > MIN_BRUSH_SIZE) {
        masterGame.brushSize -= .75;
        masterGame.updateTool();
    }
    
    // change texture to UnPressed
    masterGame.allButtons[7]->animatePress(PRESS);
}


void sizeDecreaseButtonHold(Game& masterGame) {
    if (masterGame.brushSize > MIN_BRUSH_SIZE) {
        masterGame.brushSize -= 0.1f;
        masterGame.updateTool();
    }
    else {
        masterGame.brushSize = MIN_BRUSH_SIZE;
    }

    // Show Changing Size
    sf::CircleShape sizeIndicator;
    sizeIndicator.setPosition(1180, 540);
    sizeIndicator.setRadius((float)masterGame.brushSize);
    sizeIndicator.setFillColor(sf::Color::Transparent);
    sizeIndicator.setOutlineColor(sf::Color::Black);
    sizeIndicator.setOutlineThickness(1.0);
    sizeIndicator.setOrigin(sizeIndicator.getRadius(), sizeIndicator.getRadius());
    masterGame.getWindowReference().draw(sizeIndicator);
}
void sizeDecreaseButtonRelease(Game& masterGame) {
    // print button on info screen
    ANSI::AbsMoveCursorRowCol(12, 21);
    ANSI::EraseInLine(RIGHT);
   std::cout << "SIZE DECREASE";

    // change texture to UnPressed
    masterGame.allButtons[7]->animatePress(RELEASE);
}

//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: sizeEyeDropperButtonClick
// Parameters: Game& masterGame
// Return Values: None
// Description:
// Switches the tool to the EyeDropper to pick colors from the canvas.
//
//==========Eye Droppper Tool==========
void sizeEyeDropperButtonClick(Game& masterGame) {
    // print button on info screen
    ANSI::AbsMoveCursorRowCol(11, 21);
    ANSI::EraseInLine(RIGHT);
   std::cout << "EYEDROPPER";
    
    // Change Tool to EyeDropper
    masterGame.setTool(new EyeDropper());

    // change texture to UnPressed
    masterGame.allButtons[8]->animatePress(PRESS);
}
void sizeEyeDropperButtonHold(Game& masterGame) {

}

//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: sizeEyeDropperButtonRelease
// Parameters: Game& masterGame
// Return Values: None
// Description:
// On release, updates info and restores EyeDropper button texture.
//
void sizeEyeDropperButtonRelease(Game& masterGame) {
    // print button on info screen
    ANSI::AbsMoveCursorRowCol(12, 21);
    ANSI::EraseInLine(RIGHT);
   std::cout << "EYEDROPPER";
   
    // change texture to UnPressed
    masterGame.allButtons[8]->animatePress(RELEASE);
    
}

//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: redSliderButtonClick
// Parameters: Game& masterGame
// Return Values: None
// Description:
// Sets the red component of the current color based on slider click position.
//
//==========Red Slider Tool==========
void redSliderButtonClick(Game& masterGame) {
    // Handle red slider click logic
    sf::Vector2f mousePos = masterGame.getCursorPos_Vector2f();
    float xMin = 30.0f;
    float xMax = 30.0f + 255.0f;
    if (mousePos.x >= xMin && mousePos.x <= xMax) {
        float normalized = (mousePos.x - xMin) / (xMax - xMin);
        masterGame.currentColor.r = static_cast<sf::Uint8>(normalized * 255);
        //std::cout << "Red Value: " << static_cast<int>(masterGame.currentColor.r) << std::endl;
        masterGame.allSliderPos[0] = masterGame.getCursorPos_Vector2f().x - 30.0f; // Adjust the dot for the slider
    }
    masterGame.setTool(new PencilTool());
}


void redSliderButtonHold(Game& masterGame) {
    redSliderButtonClick(masterGame); // Same logic as click for dragging
}

void redSliderButtonRelease(Game& masterGame) {
    // Nothing extra needed for release
}

//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: greenSliderButtonClick
// Parameters: Game& masterGame
// Return Values: None
// Description:
// Adjusts the green component of the current color using the slider position.
//
//==========Green Slider Tool==========
void greenSliderButtonClick(Game& masterGame) {
    // Handle green slider click logic
    sf::Vector2f mousePos = masterGame.getCursorPos_Vector2f();
    float xMin = 30.0f;
    float xMax = 30.0f + 255.0f;
    if (mousePos.x >= xMin && mousePos.x <= xMax) {
        float normalized = (mousePos.x - xMin) / (xMax - xMin);
        masterGame.currentColor.g = static_cast<sf::Uint8>(normalized * 255);
        //std::cout << "Green Value: " << static_cast<int>(masterGame.currentColor.g) << std::endl;
        masterGame.allSliderPos[1] = masterGame.getCursorPos_Vector2f().x - 30.0f; // Adjust the dot for the slider
    }
    masterGame.setTool(new PencilTool());
}

void greenSliderButtonHold(Game& masterGame) {
    greenSliderButtonClick(masterGame); // Same logic as click for dragging
}

void greenSliderButtonRelease(Game& masterGame) {
    // Nothing extra needed for release
}


//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: blueSliderButtonClick
// Parameters: Game& masterGame
// Return Values: None
// Description:
// Updates the blue component of the current color based on slider interaction.
//
//==========Blue Slider Tool==========
void blueSliderButtonClick(Game& masterGame) {
    // Handle blue slider click logic
    sf::Vector2f mousePos = masterGame.getCursorPos_Vector2f();
    float xMin = 30.0f;
    float xMax = 30.0f + 255.0f;
    if (mousePos.x >= xMin && mousePos.x <= xMax) {
        float normalized = (mousePos.x - xMin) / (xMax - xMin);
        masterGame.currentColor.b = static_cast<sf::Uint8>(normalized * 255);
        //std::cout << "Blue Value: " << static_cast<int>(masterGame.currentColor.b) << std::endl;
        masterGame.allSliderPos[2] = masterGame.getCursorPos_Vector2f().x - 30.0f; // Adjust the dot for the slider
    }
    masterGame.setTool(new PencilTool());
}

void blueSliderButtonHold(Game& masterGame) {
    blueSliderButtonClick(masterGame); // Same logic as click for dragging
}

void blueSliderButtonRelease(Game& masterGame) {
    // Nothing extra needed for release
}

//
// Programmed by Bioticcc
// Edited by Inventor4life
// FloatingToa5t
// david_ac_leon
//
// Function: alphaSliderButtonClick
// Parameters: Game& masterGame
// Return Values: None
// Description:
// Adjusts the alpha (transparency) of the current color based on the slider position.
//
//==========Alpha Slider Tool==========
void alphaSliderButtonClick(Game& masterGame) {
    // Handle alpha slider click logic
    sf::Vector2f mousePos = masterGame.getCursorPos_Vector2f();
    float xMin = 30.0f;  // Minimum X position of the slider
    float xMax = 30.0f + 255.0f; // Maximum X position of the slider (slider width)
    if (mousePos.x >= xMin && mousePos.x <= xMax) {
        float normalized = (mousePos.x - xMin) / (xMax - xMin);
        masterGame.currentColor.a = static_cast<sf::Uint8>(normalized * 255);
        //std::cout << "Alpha Value: " << static_cast<int>(masterGame.currentColor.a) << std::endl;
        masterGame.allSliderPos[3] = masterGame.getCursorPos_Vector2f().x - 30.0f; // Adjust the dot for the slider
    }
    masterGame.setTool(new PencilTool());
}

void alphaSliderButtonHold(Game& masterGame) {
    // Same logic as click for dragging
    alphaSliderButtonClick(masterGame);
}

void alphaSliderButtonRelease(Game& masterGame) {
    // Nothing extra needed for release
}

// Programmed by Bioticcc
//  Edited by Inventor4life
//            FloatingToa5t
//            david_ac_leon
// 
// function:
//  void initializeButtons( Game& thisGame )
// 
// description:
//  creates all application buttons and inserts them into the allButtons vector
// 
// parameters:
//  Game& thisGame - Reference to game to insert buttons for.
// 
// returns:
//  nothing
//
void initializeButtons(Game& masterGame)
{
    /*
    How to create a new button:
        1.) Create a button pointer with an appropriate name.
        2.) Following the template below, specify the cover image, location, and size
        3.) Define any necessary functions (see above). Function must accept Game& and have void return type.
        4.) Display the button pointer using masterGame.addButton
        
        Three optional functions (in order): 
            onClick - Executes when button is clicked
            onHold  - Executes when button is held (once per frame after initial click)
            onRelease - Executes when button is released.

        UPGRADE:
            Modify button to be base class w/virtual functions (not pure!). This will allow
            buttons to change their textures and make it easier to add different button types.
    
    */
    float rowFactor = 132;
    float colFactor = 132;

    //BASIC BUTTONS
    Button* save = new Button("save","Buttons/save.png","Buttons/savePressed.png", 118.0f, 785.0f, 210.0f, 100.0f, saveButtonClick, saveButtonHold, saveButtonRelease);
    masterGame.addButton(save);

    Button* pencil = new Button("pencil", "Buttons/pencil1.png", "Buttons/pencil1Pressed.png", 148.0f, 16.0f, 115.0f, 115.0f, pencilButtonClick, pencilButtonHold, pencilButtonRelease);
    masterGame.addButton(pencil);

    Button* pencilRed = new Button("pencilRed", "Buttons/pencilR.png", "Buttons/pencilRPressed.png", 148.0f, 148.0f, 115.0f, 115.0f, pencilRedButtonClick, pencilRedButtonHold, pencilRedButtonRelease);
    masterGame.addButton(pencilRed);

    Button* undo = new Button("undo", "Buttons/undo.png", "Buttons/undoPressed.png", 148.0f, 280.0f, 115.0f, 115.0f, undoButtonClick, undoButtonHold, undoButtonRelease);
    masterGame.addButton(undo);

    Button* clearCanvas = new Button("clearCanvas","Buttons/bombYourHardWork.png", "Buttons/bombYourHardWorkPressed.png", 148.0f, 412.0f, 115.0f, 115.0f , clearCanvasButtonClick, clearCanvasButtonHold, clearCanvasButtonRelease);
    masterGame.addButton(clearCanvas);

    Button* eraser = new Button("eraser", "Buttons/eraser.png", "Buttons/eraserPressed.png", 16.0f, 148.0f, 115.0f, 115.0f, eraserButtonClick, eraserButtonHold, eraserButtonRelease);
    masterGame.addButton(eraser);

    Button* increase = new Button("increase", "Buttons/increase.png", "Buttons/increasePressed.png", 14.0f, 280.0f, 115.0f, 115.0f, sizeIncreaseButtonClick, sizeIncreaseButtonHold , sizeIncreaseButtonRelease);
    masterGame.addButton(increase);

    Button* decrease = new Button("decrease", "Buttons/decrease.png", "Buttons/decreasePressed.png", 14.0f, 414.0f, 115.0f, 115.0f, sizeDecreaseButtonClick, sizeDecreaseButtonHold, sizeDecreaseButtonRelease);
    masterGame.addButton(decrease);

    Button*  eyeDropper = new Button("eyeDropper","Buttons/eyeDropper.png", "Buttons/eyeDropperPressed.png", 16.0f, 16.0f, 115.0f, 115.0f, sizeEyeDropperButtonClick, sizeEyeDropperButtonHold, sizeEyeDropperButtonRelease);
    masterGame.addButton(eyeDropper);

    Button* redSlider = new Button("redSlider", "Buttons/redSlider.png", "Buttons/redSliderPressed.png", 30.0f, 600.0f, 255.0f, 10.0f, redSliderButtonClick, redSliderButtonHold, redSliderButtonRelease);
    masterGame.addButton(redSlider);

    Button* greenSlider = new Button("greenSlider", "Buttons/greenSlider.png", "Buttons/greenSliderPressed.png", 30.0f, 640.0f, 255.0f, 10.0f, greenSliderButtonClick, greenSliderButtonHold, greenSliderButtonRelease);
    masterGame.addButton(greenSlider);

    Button* blueSlider = new Button("blueSlider", "Buttons/blueSlider.png", "Buttons/blueSliderPressed.png", 30.0f, 680.0f, 255.0f, 10.0f, blueSliderButtonClick, blueSliderButtonHold, blueSliderButtonRelease);
    masterGame.addButton(blueSlider);

    Button* alphaSlider = new Button("alphaSldier", "Buttons/alphaSlider.png", "Buttons/alphaSliderPressed.png", 30.0f, 720.0f, 255.0f, 10.0f, alphaSliderButtonClick, alphaSliderButtonHold, alphaSliderButtonRelease);
    masterGame.addButton(alphaSlider);

    //PRESSED BUTTONS
}

