#include "Game.h"

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

    this->currentColor = sf::Color::Black;
    this->setTool(new PencilTool()); // Set default tool

}

void Game::runGame() {
    using std::cout; //skull emoji
    //currentTool = 1; //by default our starting tool will be 1 (select, ie standard cursor)

    initializeButtons(*this);

    //Edging Variables
    const bool PRESSED = true;
    bool mouseLeftPreviousState = false; // Stores whether the left mouse button was pressed or not in the previous frame
    bool mouseLeftCurrentState = false;
    bool mouseLeftPosEdge = false;        // True only for the frame where mouse left went not_pressed->pressed
    bool mouseLeftNegEdge = false;        // True only for the frame where mouse left went pressed->not_pressed


    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

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
                    if(i->onRelease != nullptr) i->onRelease(*this);
                    i->clicked = false;
                }
            }
            if (currentTool.get()->in_use) {
                currentTool.get()->mouseUp(*this, cursorCanvasPosition); // Passes the last valid mouse position.
                currentTool.get()->in_use = false;
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

void saveButtonClick(Game& masterGame) {
    std::cout << "SAVE!";
}

// default pencil, Black
void pencilButtonClick(Game& masterGame) {
    masterGame.currentColor = sf::Color::Black;
    masterGame.setTool(new PencilTool());
    std::cout << "BLACK SELECTED" << std::endl;
    sf::Texture pressedTexture;
    pressedTexture.loadFromFile("Buttons/pencil1Pressed.png");
    masterGame.allButtons[1]->setButtonIcon(pressedTexture);
    // MAKE SURE THE ELEME^NT HERE MATCHES IN THE ORDER IT WAS ADDED TO THE VECTOR
    // I wanna add a public element to the buttons so I can search and return buttons such that we could
    // give buttons an string member to search for them by thus getting rid of this hardcoding
}
void pencilButtonHold(Game& mastergame) {
    std::cout << "BLACK HOLDING" << std::endl;
}
void pencilButtonRelease(Game& masterGame) {
    std::cout << "BLACK RELEASED" << std::endl;
    sf::Texture defaultTexture;
    defaultTexture.loadFromFile("Buttons/pencil1.png");
    masterGame.allButtons[1]->setButtonIcon(defaultTexture);
}

// default pencil, Red
void pencilRedButtonClick(Game& masterGame) {
    masterGame.currentColor = sf::Color::Red;
    masterGame.setTool(new PencilTool());
    std::cout << "RED SELECTED" << std::endl;
    sf::Texture pressedTexture;
    pressedTexture.loadFromFile("Buttons/pencilRPressed.png");
    masterGame.allButtons[2]->setButtonIcon(pressedTexture);
}
void pencilRedButtonHold(Game& mastergame) {
    std::cout << "RED HOLDING" << std::endl;
}
void pencilRedButtonRelease(Game& masterGame) {
    std::cout << "RED RELEASED" << std::endl;
    sf::Texture defaultTexture;
    defaultTexture.loadFromFile("Buttons/pencilR.png");
    masterGame.allButtons[2]->setButtonIcon(defaultTexture);
}

// default pencil, Green
void pencilGreenButtonClick(Game& masterGame) {
    masterGame.currentColor = sf::Color::Green;
    masterGame.setTool(new PencilTool());
    std::cout << "GREEN SELECTED" << std::endl;
    sf::Texture pressedTexture;
    pressedTexture.loadFromFile("Buttons/pencilGPressed.png");
    masterGame.allButtons[3]->setButtonIcon(pressedTexture);
}
void pencilGreenButtonHold(Game& mastergame) {
    std::cout << "GREEN HOLDING" << std::endl;
}
void pencilGreenButtonRelease(Game& masterGame) {
    std::cout << "GREEN RELEASED" << std::endl;
    sf::Texture defaultTexture;
    defaultTexture.loadFromFile("Buttons/pencilG.png");
    masterGame.allButtons[3]->setButtonIcon(defaultTexture);
}

// default pencil, Blue
void pencilBlueButtonClick(Game& masterGame) {
    masterGame.currentColor = sf::Color::Blue;
    masterGame.setTool(new PencilTool());
    std::cout << "BLUE SELECTED" << std::endl;
    sf::Texture pressedTexture;
    pressedTexture.loadFromFile("Buttons/pencilBPressed.png");
    masterGame.allButtons[4]->setButtonIcon(pressedTexture);
}
void pencilBlueButtonHold(Game& mastergame) {
    std::cout << "BLUE HOLDING" << std::endl;
}
void pencilBlueButtonRelease(Game& masterGame) {
    std::cout << "BLUE RELEASED" << std::endl;
    sf::Texture defaultTexture;
    defaultTexture.loadFromFile("Buttons/pencilB.png");
    masterGame.allButtons[4]->setButtonIcon(defaultTexture);
}

// default eraser
void eraserButtonClick(Game& masterGame) {
    masterGame.setTool(new EraserTool());
    sf::Texture pressedTexture;
    pressedTexture.loadFromFile("Buttons/eraserPressed.png");
    masterGame.allButtons[5]->setButtonIcon(pressedTexture);
}
void eraserButtonHold(Game& masterGame) {
    //masterGame.setTool(new EraserTool());
}
void eraserButtonRelease(Game& masterGame) {
    masterGame.setTool(new EraserTool());
    sf::Texture defaultTexture;
    defaultTexture.loadFromFile("Buttons/eraser.png");
    masterGame.allButtons[5]->setButtonIcon(defaultTexture);
}

// default brush size increase
void sizeIncreaseButtonClick(Game& masterGame) {
    masterGame.brushSize += 5;
    masterGame.updateTool();
    sf::Texture pressedTexture;
    pressedTexture.loadFromFile("Buttons/increasePressed.png");
    masterGame.allButtons[6]->setButtonIcon(pressedTexture);
}
void sizeIncreaseButtonHold(Game& masterGame) {
    masterGame.brushSize += .5;
    masterGame.updateTool();
    // hold code does not actually apply each frame, curious indeed
}
void sizeIncreaseButtonRelease(Game& masterGame) {
    sf::Texture defaultTexture;
    defaultTexture.loadFromFile("Buttons/increase.png");
    masterGame.allButtons[6]->setButtonIcon(defaultTexture);
}

//default brush size decrease
void sizeDecreaseButtonClick(Game& masterGame) {
    if (masterGame.brushSize > 5) {
        masterGame.brushSize -= 5;
        masterGame.updateTool();
    }
    sf::Texture pressedTexture;
    pressedTexture.loadFromFile("Buttons/decreasePressed.png");
    masterGame.allButtons[7]->setButtonIcon(pressedTexture);
}
void sizeDecreaseButtonHold(Game& masterGame) {
    if (masterGame.brushSize > 5) {
        masterGame.brushSize -= -5;
        masterGame.updateTool();
    }
}
void sizeDecreaseButtonRelease(Game& masterGame) {
    sf::Texture defaultTexture;
    defaultTexture.loadFromFile("Buttons/decrease.png");
    masterGame.allButtons[7]->setButtonIcon(defaultTexture);
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
    Button* save = new Button("Buttons/save.png", 118.0f, 785.0f, 210.0f, 100.0f, saveButtonClick/*, saveButtonHold, saveButtonRelease*/);
    masterGame.addButton(save);

    Button* pencil = new Button("Buttons/pencil1.png", 148.0f, 16.0f, 115.0f, 115.0f, pencilButtonClick, pencilButtonHold, pencilButtonRelease);
    masterGame.addButton(pencil);

    Button* pencilRed = new Button("Buttons/pencilR.png", 148.0f, 148.0f, 115.0f, 115.0f, pencilRedButtonClick, pencilRedButtonHold, pencilRedButtonRelease);
    masterGame.addButton(pencilRed);

    Button* pencilGreen = new Button("Buttons/pencilG.png", 148.0f, 280.0f, 115.0f, 115.0f, pencilGreenButtonClick, pencilGreenButtonHold, pencilGreenButtonRelease);
    masterGame.addButton(pencilGreen);

    Button* pencilBlue = new Button("Buttons/pencilB.png", 148.0f, 412.0f, 115.0f, 115.0f , pencilBlueButtonClick, pencilBlueButtonHold, pencilBlueButtonRelease);
    masterGame.addButton(pencilBlue);

    Button* eraser = new Button("Buttons/eraser.png", 16.0f, 148.0f, 115.0f, 115.0f, eraserButtonClick, eraserButtonHold, eraserButtonRelease);
    masterGame.addButton(eraser);

    Button* increase = new Button("Buttons/increase.png", 14.0f, 280.0f, 115.0f, 115.0f, sizeIncreaseButtonClick, sizeIncreaseButtonHold , sizeIncreaseButtonRelease);
    masterGame.addButton(increase);

    Button* decrease = new Button("Buttons/decrease.png", 14.0f, 414.0f, 115.0f, 115.0f, sizeDecreaseButtonClick, sizeDecreaseButtonHold, sizeDecreaseButtonRelease);
    masterGame.addButton(decrease);

    //PRESSED BUTTONS
}

