#include "StateSettings.hpp"
//#include "StatePause.hpp"
#include "StateMainMenu.hpp"
#include "Definitions.hpp"
#include <iostream>
#include <sstream>

StateSettings:: StateSettings(GameDataRef data, int size, int winSize, bool isPlayerX, bool VSAI): _data( data ) {
    _winSize  = winSize;
    _VSAI     = VSAI;
    _size     = size;
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
    switch (_winSize) {                             // CHANGE THAT
        case 3:
            this -> _data -> assets.LoadTexture("Number Display2",   NUMBER_DISPLAY_3);
            break;
        case 4:
            this -> _data -> assets.LoadTexture("Number Display2",   NUMBER_DISPLAY_4);
            break;
        case 5:
            this -> _data -> assets.LoadTexture("Number Display2",   NUMBER_DISPLAY_5);
            break;
        case 6:
            this -> _data -> assets.LoadTexture("Number Display2",   NUMBER_DISPLAY_6);
            break;
        default:
            break;
    }
    this -> _data -> assets.LoadTexture("Number Display",   NUMBER_DISPLAY_3);
    this -> _data -> assets.LoadTexture("Home Button",      HOME_BUTTON);
    this -> _data -> assets.LoadTexture("X Piece",           X_WINNING_PIECE_FILEPATH);
    this -> _data -> assets.LoadTexture("O Piece",           O_WINNING_PIECE_FILEPATH);
    this -> _data -> assets.LoadTexture("AI Piece",           X_WINNING_PIECE_FILEPATH);
    this -> _data -> assets.LoadTexture("P Piece",           O_WINNING_PIECE_FILEPATH);
    

    this -> _background.setTexture(    this -> _data -> assets.GetTexture("Settings Background"));
    this -> _plusButton.setTexture(    this -> _data -> assets.GetTexture("Plus Button"));
    this -> _minusButton.setTexture(   this -> _data -> assets.GetTexture("Minus Button"));
    this -> _plusButton2.setTexture(   this -> _data -> assets.GetTexture("Plus Button"));
    this -> _minusButton2.setTexture(  this -> _data -> assets.GetTexture("Minus Button"));
    this -> _numberDisplay.setTexture( this -> _data -> assets.GetTexture("Number Display"));
    this -> _numberDisplay2.setTexture(this -> _data -> assets.GetTexture("Number Display2"));
    this -> _homeButton.setTexture(    this -> _data -> assets.GetTexture("Home Button"));
    this -> _title.setTexture(         this -> _data -> assets.GetTexture("S Title"));
    this -> _titleGS.setTexture(       this -> _data -> assets.GetTexture("GS Title"));
    this -> _XPiece.setTexture(        this -> _data -> assets.GetTexture("X Piece"));
    this -> _OPiece.setTexture(        this -> _data -> assets.GetTexture("O Piece"));
    this -> _AIPiece.setTexture(       this -> _data -> assets.GetTexture("AI Piece"));
    this -> _PPiece.setTexture(        this -> _data -> assets.GetTexture("P Piece"));
    
    
    this -> _plusButton.setPosition( this -> _data -> window.getSize().x * 3 / 4
                                     - this -> _plusButton.getLocalBounds().width / 2 ,
                                       this -> _data -> window.getSize().y / 5 * 2
                                     - this -> _plusButton.getLocalBounds().height / 2);

    this -> _numberDisplay.setPosition( this -> _data -> window.getSize().x / 2
                                   - this -> _numberDisplay.getLocalBounds().width / 2 ,
                                     this -> _data -> window.getSize().y / 5 * 2
                                   - this -> _numberDisplay.getLocalBounds().height / 2);
    
    this -> _minusButton.setPosition( this -> _data -> window.getSize().x * 1 / 4
                                   - this -> _minusButton.getLocalBounds().width / 2 ,
                                     this -> _data -> window.getSize().y / 5 * 2
                                   - this -> _minusButton.getLocalBounds().height / 2);
    
    this -> _plusButton2.setPosition( this -> _data -> window.getSize().x * 3 / 4
                                     - this -> _plusButton.getLocalBounds().width / 2 ,
                                       this -> _data -> window.getSize().y / 5 * 3
                                     - this -> _plusButton.getLocalBounds().height / 2);

    this -> _numberDisplay2.setPosition( this -> _data -> window.getSize().x / 2
                                   - this -> _numberDisplay2.getLocalBounds().width / 2 ,
                                     this -> _data -> window.getSize().y / 5 * 3
                                   - this -> _numberDisplay2.getLocalBounds().height / 2);
    
    this -> _minusButton2.setPosition( this -> _data -> window.getSize().x * 1 / 4
                                   - this -> _minusButton.getLocalBounds().width / 2 ,
                                     this -> _data -> window.getSize().y / 5 * 3
                                   - this -> _minusButton.getLocalBounds().height / 2);
    
    this -> _homeButton.setPosition((SCREEN_WIDTH/2)
                                  - (this -> _homeButton.getGlobalBounds().width / 2),
                                    (SCREEN_HEIGHT)
                                  - (this -> _homeButton.getGlobalBounds().height * 1.3));
    this -> _XPiece.setPosition((SCREEN_WIDTH) * 1 / 4
                                  - (this -> _XPiece.getGlobalBounds().width / 2),
                                    (SCREEN_HEIGHT/5*4)
                                  - (this -> _XPiece.getGlobalBounds().height * 0.5));
    this -> _OPiece.setPosition((SCREEN_WIDTH) * 1 / 4
                                  - (this -> _OPiece.getGlobalBounds().width / 2),
                                    (SCREEN_HEIGHT/5*4)
                                  - (this -> _OPiece.getGlobalBounds().height * 0.5));
    this -> _AIPiece.setPosition((SCREEN_WIDTH) * 3 / 4
                                  - (this -> _AIPiece.getGlobalBounds().width / 2),
                                    (SCREEN_HEIGHT/5*4)
                                  - (this -> _AIPiece.getGlobalBounds().height * 0.5));
    this -> _PPiece.setPosition((SCREEN_WIDTH) * 3 / 4
                                  - (this -> _PPiece.getGlobalBounds().width / 2),
                                    (SCREEN_HEIGHT/5*4)
                                  - (this -> _PPiece.getGlobalBounds().height * 0.5));
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
            else {
                --_size;
                if (_winSize > _size)
                    --_winSize;
            }
        }
        
        if ( this -> _data -> input.IsSpriteClicked(this -> _plusButton2, sf::Mouse::Left, this -> _data -> window) ) {
            if (_winSize == _size ) std::cout << " Za duży rozmiar! \n";
            else            ++_winSize;
        }
        if ( this -> _data -> input.IsSpriteClicked(this -> _minusButton2, sf::Mouse::Left, this -> _data -> window) ){
            if (_winSize == 3 ) std::cout << " Za mały rozmiar! \n";
            else            --_winSize;
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
        if ( this -> _data -> input.IsSpriteClicked(this -> _AIPiece, sf::Mouse::Left, this -> _data -> window) ) {
            if (_VSAI)      _VSAI = false;
            else            _VSAI = true;
            std:: cout << "\n ZMIANA, teraz jestem " << _VSAI;
        }
    }
}

void StateSettings:: Update(float dt) {

    this -> _data -> window.clear();
    this -> _data -> window.draw( this -> _background);
    this -> _data -> window.draw( this -> _plusButton);
    this -> _data -> window.draw( this -> _minusButton);
    this -> _data -> window.draw( this -> _plusButton2);
    this -> _data -> window.draw( this -> _minusButton2);
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
                                     this -> _data -> window.getSize().y / 5 * 2
                                   - this -> _numberDisplay.getLocalBounds().height / 2);
    
    switch (_winSize) {                             // CHANGE THAT
        case 3:
            this -> _data -> assets.LoadTexture("Number Display2",   NUMBER_DISPLAY_3);
            break;
        case 4:
            this -> _data -> assets.LoadTexture("Number Display2",   NUMBER_DISPLAY_4);
            break;
        case 5:
            this -> _data -> assets.LoadTexture("Number Display2",   NUMBER_DISPLAY_5);
            break;
        case 6:
            this -> _data -> assets.LoadTexture("Number Display2",   NUMBER_DISPLAY_6);
            break;
        default:
            break;
    }
    this -> _numberDisplay2.setTexture( this -> _data -> assets.GetTexture("Number Display2"));
    this -> _numberDisplay2.setPosition( this -> _data -> window.getSize().x / 2
                                   - this -> _numberDisplay2.getLocalBounds().width / 2 ,
                                     this -> _data -> window.getSize().y / 5 * 3
                                   - this -> _numberDisplay2.getLocalBounds().height / 2);
    
    
    if (_isPlayerX)     this -> _data -> window.draw( this -> _XPiece);
    else                this -> _data -> window.draw( this -> _OPiece);
    
    if (_VSAI)          this -> _data -> window.draw( this -> _AIPiece);
    else                this -> _data -> window.draw( this -> _PPiece);
    
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
    this -> _data -> window.draw( this -> _plusButton2);
    this -> _data -> window.draw( this -> _minusButton2);
    this -> _data -> window.draw( this -> _numberDisplay2);
    this -> _data -> window.draw( this -> _homeButton);
    
    if (_isPlayerX)     this -> _data -> window.draw( this -> _XPiece);
    else                this -> _data -> window.draw( this -> _OPiece);
    
    if (_VSAI)          this -> _data -> window.draw( this -> _AIPiece);
    else                this -> _data -> window.draw( this -> _PPiece);
    
    this -> _data -> window.display();
}
