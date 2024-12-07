#include "Game.h"
#include "ANSIescapeCode.h"
#include "string"

using std::cout;
using std::endl;

#define MIN_BRUSH_SIZE 1.f
#define SLIDER_DOT_RADIUS 8.f
#define SLIDER_DOT_RESOLUTION 12.f

#define CANVAS_W 1942.0f
#define CANVAS_H 1080.0f

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

void Game::setTool(Tool* newTool)
{
    if (currentTool.get() != nullptr) currentTool.get()->toolDeselect(*this);
    currentTool.reset(newTool); // Deallocates the old tool and sets it to the new one.
    currentTool.get()->toolSelect(*this);
}

void Game::updateTool(void) {
    currentTool.get()->toolUpdate(*this);
}

void Game::addButton(Button* newButton)
{
    allButtons.push_back(newButton);
}

sf::RenderWindow& Game::getWindowReference(void)
{
    return this->window;
}

void Game::drawToCanvas(sf::Shape& toStamp) {
    canvasRenderTexture.draw(toStamp);
    canvas.setTexture(canvasRenderTexture.getTexture());
}

sf::Color Game::getColor() const
{
    return currentColor;
}

int Game::getButtonCount() const
{
    int buttonCount = 0;
    for (auto i : allButtons) {
        buttonCount++;
    }
    return buttonCount;
}

void Game::displayInfo() const
{
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
    cout << window.getSize().x;
    ANSI::AbsMoveCursorRowCol(19, 21);
    cout << window.getSize().y;

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

sf::Vector2f Game::getCursorPos_Vector2f() const
{
    return this->cursorPosition;
}

sf::Vector2f Game::getCursorCanvasPos_Vector2f() const
{
    return this->cursorCanvasPosition;
}

sf::Sprite& Game::getCanvas()
{
    return this->canvas;
}

void Game::setCanvas(sf::Sprite newCanvas)
{
    this->canvas = newCanvas;
}

int Game::getCanvasStatesSaved() const
{
    int count = 0;
    for (auto i : redoUndoVector) {
        count++;
    }
    return count;
}

void Game::incramentSaveCounter()
{
    timesSaved++;
}

bool Game::saveCanvasToFile()
{
    // create the image of the canvas
    sf::Image screenshot = getCanvas().getTexture()->copyToImage();
    std::time_t now = std::time(nullptr);
    struct tm buf;
    localtime_s(&buf, &now);
    char timestamp[20];
    std::strftime(timestamp, sizeof(timestamp), "%Y%m%d%H%M%S", &buf);
    std::string filename = "SavedDrawings/drawing_" + std::string(timestamp) + ".png";

    // incrament counter & Write Save Time Stamp
    incramentSaveCounter();
    ANSI::AbsMoveCursorRowCol(15, 21);
    std::strftime(timestamp, sizeof(timestamp), "%Y/%m/%d-%H:%M:%S", &buf);
    cout << timestamp;

    // save the file and return success bool
    return screenshot.saveToFile(filename);
}

void saveButtonClick(Game& masterGame) {
    // print button on info screen
    ANSI::AbsMoveCursorRowCol(11, 21);
    ANSI::EraseInLine(RIGHT);
    cout << "SAVE";

    masterGame.saveCanvasToFile();

    //animate button
    masterGame.allButtons[0]->animatePress(PRESS);
}

void saveButtonHold(Game& masterGame) {
}

void saveButtonRelease(Game& masterGame) {

    // Capture Canvas and Save to file
    /*sf::Texture screenshotTexture;
    screenshotTexture.create(masterGame.getWindowReference().getSize().x, masterGame.getWindowReference().getSize().y);
    screenshotTexture.update(masterGame.getWindowReference());*/
    // Under the grace our Lord and Savior Ethan Goode, he has figured out how
    // to take screenshots on the canvas only rather than the entire window
    // using the getCanvas() func which returns a reference

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
    cout << "BLACK PENCIL";

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

void pencilButtonRelease(Game& masterGame) {
    ANSI::AbsMoveCursorRowCol(12, 21);
    ANSI::EraseInLine(RIGHT);
    cout << "BLACK PENCIL";

    // change texture to UnPressed
    masterGame.allButtons[1]->animatePress(RELEASE);
}

//==========default pencil, Red==========
void pencilRedButtonClick(Game& masterGame) {
    // print button on info screen
    ANSI::AbsMoveCursorRowCol(11, 21);
    ANSI::EraseInLine(RIGHT);
    cout << "RED PENCIL";

    // change color to black
    masterGame.currentColor = sf::Color::Red;
    masterGame.setTool(new PencilTool());

    // change texture to pressed
    masterGame.allButtons[2]->animatePress(PRESS);
}
void pencilRedButtonHold(Game& mastergame) {
    //std::cout << "RED HOLDING" << std::endl;
}
void pencilRedButtonRelease(Game& masterGame) {
    // print button on info screen
    ANSI::AbsMoveCursorRowCol(12, 21);
    ANSI::EraseInLine(RIGHT);
    cout << "RED PENCIL";

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
        cout << "UNDO " << masterGame.getCanvasStatesSaved();
    }
    else {
        cout << "UNDO (EMPTY)";
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

void undoButtonRelease(Game& masterGame) {
    // print button on info screen
    ANSI::AbsMoveCursorRowCol(12, 21);
    ANSI::EraseInLine(RIGHT);

    // change texture to UnPressed
    masterGame.allButtons[3]->animatePress(RELEASE);
}

//==========clearCanvas==========
void clearCanvasButtonClick(Game& masterGame) {
    // print button on info screen
    ANSI::AbsMoveCursorRowCol(11, 21);
    ANSI::EraseInLine(RIGHT);
    cout << "CLEAR CANVAS";

    // Clear the Screen
    sf::RectangleShape bigAssSquare(sf::Vector2f(3000,3000));
    bigAssSquare.setFillColor(sf::Color::White);
    masterGame.drawToCanvas(bigAssSquare);

    // change texture to pressed
    masterGame.allButtons[4]->animatePress(PRESS);
}
void clearCanvasButtonHold(Game& mastergame) {
}

void clearCanvasButtonRelease(Game& masterGame) {
    // print button on info screen
    ANSI::AbsMoveCursorRowCol(12, 21);
    ANSI::EraseInLine(RIGHT);
    cout << "CLEAR CANVAS";
   
    // change texture to UnPressed
    masterGame.allButtons[4]->animatePress(RELEASE);
}

//==========default eraser==========
void eraserButtonClick(Game& masterGame) {
    // print button on info screen
    ANSI::AbsMoveCursorRowCol(11, 21);
    ANSI::EraseInLine(RIGHT);
    cout << "ERASER";

    // change to eraser tool
    masterGame.setTool(new EraserTool());
    
    // change texture to pressed
    masterGame.allButtons [5] ->animatePress(PRESS);
}
void eraserButtonHold(Game& masterGame) {
}

void eraserButtonRelease(Game& masterGame) {
    // print button on info screen
    ANSI::AbsMoveCursorRowCol(12, 21);
    ANSI::EraseInLine(RIGHT);
    cout << "ERASER";

    // change texture to UnPressed
    masterGame.allButtons[5]->animatePress(RELEASE);
}

//==========default brush size increase==========
void sizeIncreaseButtonClick(Game& masterGame) {
    // print button on info screen
    ANSI::AbsMoveCursorRowCol(11, 21);
    ANSI::EraseInLine(RIGHT);
    cout << "SIZE INCREASE";

    masterGame.brushSize += .75;
    masterGame.updateTool();
    
    // change texture to UnPressed
    masterGame.allButtons[6]->animatePress(PRESS);
}
void sizeIncreaseButtonHold(Game& masterGame) {
    masterGame.brushSize += .2;
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
void sizeIncreaseButtonRelease(Game& masterGame) {
    // print button on info screen
    ANSI::AbsMoveCursorRowCol(12, 21);
    ANSI::EraseInLine(RIGHT);
    cout << "SIZE INCREASE";

    // change texture to UnPressed
    masterGame.allButtons[6]->animatePress(RELEASE);
}

//==========efault brush size decrease==========
void sizeDecreaseButtonClick(Game& masterGame) {
    // print button on info screen
    ANSI::AbsMoveCursorRowCol(11, 21);
    ANSI::EraseInLine(RIGHT);
    cout << "SIZE DECREASE";

    if (masterGame.brushSize > MIN_BRUSH_SIZE) {
        masterGame.brushSize -= .75;
        masterGame.updateTool();
    }
    
    // change texture to UnPressed
    masterGame.allButtons[7]->animatePress(PRESS);
}
void sizeDecreaseButtonHold(Game& masterGame) {
    if (masterGame.brushSize > MIN_BRUSH_SIZE) {
        masterGame.brushSize -= 0.2f;
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
    cout << "SIZE DECREASE";

    // change texture to UnPressed
    masterGame.allButtons[7]->animatePress(RELEASE);
}

//==========Eye Droppper Tool==========
void sizeEyeDropperButtonClick(Game& masterGame) {
    // print button on info screen
    ANSI::AbsMoveCursorRowCol(11, 21);
    ANSI::EraseInLine(RIGHT);
    cout << "EYEDROPPER";
    
    // Change Tool to EyeDropper
    masterGame.setTool(new EyeDropper());

    // change texture to UnPressed
    masterGame.allButtons[8]->animatePress(PRESS);
}
void sizeEyeDropperButtonHold(Game& masterGame) {

}
void sizeEyeDropperButtonRelease(Game& masterGame) {
    // print button on info screen
    ANSI::AbsMoveCursorRowCol(12, 21);
    ANSI::EraseInLine(RIGHT);
    cout << "EYEDROPPER";
   
    // change texture to UnPressed
    masterGame.allButtons[8]->animatePress(RELEASE);
    
}

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

/*
Programmed by: Inventor4life
    Creates and initializes all buttons.
*/
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

