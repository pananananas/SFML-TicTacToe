#include "StateSettings.hpp"
//#include "StatePause.hpp"
#include "StateMainMenu.hpp"
#include "Definitions.hpp"
#include <iostream>
#include <sstream>

StateSettings:: StateSettings(GameDataRef data, int size, int winSize, bool isPlayerX, bool VSAI): _data( data ) {
    _winSize  = winSize;
    _VSAI     = VSAI;
    _size = size;
    _isPlayerX = isPlayerX;
}

void StateSettings:: Init() {

    this -> _data -> assets.LoadTexture("Settings Background", SETTINGS_BACKGROUND_FILEPATH);
    this -> _data -> assets.LoadTexture("Plus Button",         PLUS_BUTTON);
    this -> _data -> assets.LoadTexture("Minus Button",        MINUS_BUTTON);
    this -> _data -> assets.LoadTexture("S Title",             SETTINGS_TITLE_FILEPATH);
    this -> _data -> assets.LoadTexture("GS Title",            GRID_SIZE_TITLE_FILEPATH);
    switch (_size) {
        case 3:
            this -> _data -> assets.LoadTexture("Number Display",   NUMBER_DISPLAY_3);
            break;
        case 4:
            this -> _data -> assets.LoadTexture("Number Display",   NUMBER_DISPLAY_4);
            break;
        case 5:
            this -> _data -> assets.LoadTexture("Number Display",   NUMBER_DISPLAY_5);
            break;
        case 6:
            this -> _data -> assets.LoadTexture("Number Display",   NUMBER_DISPLAY_6);
            break;
        default:
            break;
    }
    this -> _data -> assets.LoadTexture("Number Display",   NUMBER_DISPLAY_3);
    this -> _data -> assets.LoadTexture("Home Button",      HOME_BUTTON);
    this -> _data -> assets.LoadTexture("X Piece",           X_WINNING_PIECE_FILEPATH);
    this -> _data -> assets.LoadTexture("O Piece",           O_WINNING_PIECE_FILEPATH);
    

    this -> _background.setTexture(    this -> _data -> assets.GetTexture("Settings Background"));
    this -> _plusButton.setTexture(    this -> _data -> assets.GetTexture("Plus Button"));
    this -> _minusButton.setTexture(   this -> _data -> assets.GetTexture("Minus Button"));
    this -> _numberDisplay.setTexture( this -> _data -> assets.GetTexture("Number Display"));
    this -> _homeButton.setTexture(    this -> _data -> assets.GetTexture("Home Button"));
    this -> _title.setTexture(         this -> _data -> assets.GetTexture("S Title"));
    this -> _titleGS.setTexture(       this -> _data -> assets.GetTexture("GS Title"));
    this -> _XPiece.setTexture(        this -> _data -> assets.GetTexture("X Piece"));
    this -> _OPiece.setTexture(        this -> _data -> assets.GetTexture("O Piece"));
    
    
    this -> _plusButton.setPosition( this -> _data -> window.getSize().x * 3 / 4
                                     - this -> _plusButton.getLocalBounds().width / 2 ,
                                       this -> _data -> window.getSize().y / 2
                                     - this -> _plusButton.getLocalBounds().height / 2);

    this -> _numberDisplay.setPosition( this -> _data -> window.getSize().x / 2
                                   - this -> _numberDisplay.getLocalBounds().width / 2 ,
                                     this -> _data -> window.getSize().y / 2
                                   - this -> _numberDisplay.getLocalBounds().height / 2);
    
    this -> _minusButton.setPosition( this -> _data -> window.getSize().x * 1 / 4
                                   - this -> _minusButton.getLocalBounds().width / 2 ,
                                     this -> _data -> window.getSize().y / 2
                                   - this -> _minusButton.getLocalBounds().height / 2);
    this -> _homeButton.setPosition((SCREEN_WIDTH/2)
                                  - (this -> _homeButton.getGlobalBounds().width / 2),
                                    (SCREEN_HEIGHT)
                                  - (this -> _homeButton.getGlobalBounds().height * 1.3));
    this -> _XPiece.setPosition((SCREEN_WIDTH/2)
                                  - (this -> _XPiece.getGlobalBounds().width / 2),
                                    (SCREEN_HEIGHT/4*3)
                                  - (this -> _XPiece.getGlobalBounds().height * 0.5));
    this -> _OPiece.setPosition((SCREEN_WIDTH/2)
                                  - (this -> _OPiece.getGlobalBounds().width / 2),
                                    (SCREEN_HEIGHT/4*3)
                                  - (this -> _OPiece.getGlobalBounds().height * 0.5));
    this -> _title.setPosition(0, 0);
    this -> _titleGS.setPosition(0, 0);
}


void StateSettings:: HandleInput() {

    sf::Event event;

    while (this -> _data -> window.pollEvent(event)) {

        if (sf::Event::Closed == event.type)
            this -> _data -> window.close();

        if ( this -> _data -> input.IsSpriteClicked(this -> _plusButton, sf::Mouse::Left, this -> _data -> window) ) {
            if (_size == 6 ) std::cout << " Za duży rozmiar! \n";
            else            ++_size;
        }
        if ( this -> _data -> input.IsSpriteClicked(this -> _minusButton, sf::Mouse::Left, this -> _data -> window) ){
            if (_size == 3 ) std::cout << " Za mały rozmiar! \n";
            else            --_size;
        }
        if ( this -> _data -> input.IsSpriteClicked(this -> _homeButton, sf::Mouse::Left, this -> _data -> window) ) {
            this -> _data -> machine.RemoveState();
            this -> _data -> machine.AddState(StateRef(new StateMainMenu(_data, _size,_winSize, _isPlayerX, _VSAI)), true);
        }
        if ( this -> _data -> input.IsSpriteClicked(this -> _XPiece, sf::Mouse::Left, this -> _data -> window) ) {
            if (_isPlayerX) _isPlayerX = false;
            else            _isPlayerX = true;
            std:: cout << "\n ZMIANA, teraz jestem " << _isPlayerX;
        }
//        if ( this -> _data -> input.IsSpriteClicked(this -> _OPiece, sf::Mouse::Left, this -> _data -> window) ) {
//            if (_isPlayerX) _isPlayerX = false;
//            else            _isPlayerX = true;
//            std:: cout << "\n ZMIANA, teraz jestem " << _isPlayerX;
//        }
    }
}

void StateSettings:: Update(float dt) {

    this -> _data -> window.clear();
    this -> _data -> window.draw( this -> _background);
    this -> _data -> window.draw( this -> _plusButton);
    this -> _data -> window.draw( this -> _minusButton);
    this -> _data -> window.draw( this -> _title);
//    this -> _data -> window.draw( this -> _titleGS);
    switch (_size) {

        case 3:
            this -> _data -> assets.LoadTexture("Number Display",   NUMBER_DISPLAY_3);
            break;
        case 4:
            this -> _data -> assets.LoadTexture("Number Display",   NUMBER_DISPLAY_4);
            break;
        case 5:
            this -> _data -> assets.LoadTexture("Number Display",   NUMBER_DISPLAY_5);
            break;
        case 6:
            this -> _data -> assets.LoadTexture("Number Display",   NUMBER_DISPLAY_6);
            break;
        default:
            break;
    }
    this -> _numberDisplay.setTexture( this -> _data -> assets.GetTexture("Number Display"));
    this -> _numberDisplay.setPosition( this -> _data -> window.getSize().x / 2
                                   - this -> _numberDisplay.getLocalBounds().width / 2 ,
                                     this -> _data -> window.getSize().y / 2
                                   - this -> _numberDisplay.getLocalBounds().height / 2);
    
    if (_isPlayerX)     this -> _data -> window.draw( this -> _XPiece);
    else                this -> _data -> window.draw( this -> _OPiece);
    
    this -> _data -> window.draw( this -> _numberDisplay);
    this -> _data -> window.draw( this -> _homeButton);
    this -> _data -> window.display();
}

void StateSettings:: Draw(float dt) {
    this -> _data -> window.clear();
    this -> _data -> window.draw( this -> _background);
    this -> _data -> window.draw( this -> _title);
//    this -> _data -> window.draw( this -> _titleGS);
    this -> _data -> window.draw( this -> _plusButton);
    this -> _data -> window.draw( this -> _minusButton);
    this -> _data -> window.draw( this -> _numberDisplay);
    this -> _data -> window.draw( this -> _homeButton);
    
    if (_isPlayerX)     this -> _data -> window.draw( this -> _XPiece);
    else                this -> _data -> window.draw( this -> _OPiece);
    
    this -> _data -> window.display();
}
