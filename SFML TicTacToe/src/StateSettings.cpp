#include "StateSettings.hpp"
//#include "StatePause.hpp"
#include "StateMainMenu.hpp"
#include "Definitions.hpp"
#include <iostream>
#include <sstream>

StateSettings:: StateSettings(GameDataRef data, int size): _data( data ) { _size = size; }

void StateSettings:: Init() {

    this -> _data -> assets.LoadTexture("Settings Background", SETTINGS_BACKGROUND_FILEPATH);
    this -> _data -> assets.LoadTexture("Plus Button",      PLUS_BUTTON);
    this -> _data -> assets.LoadTexture("Minus Button",     MINUS_BUTTON);
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

    this -> _background.setTexture(   this -> _data -> assets.GetTexture("Settings Background"));
    this -> _plusButton.setTexture( this -> _data -> assets.GetTexture("Plus Button"));
    this -> _minusButton.setTexture( this -> _data -> assets.GetTexture("Minus Button"));
    this -> _numberDisplay.setTexture( this -> _data -> assets.GetTexture("Number Display"));
    this -> _homeButton.setTexture(   this -> _data -> assets.GetTexture("Home Button"));

    
    
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
                                    (this -> _homeButton.getGlobalBounds().height * 0.1));
    
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
            this -> _data -> machine.AddState(StateRef(new StateMainMenu(_data, _size)), true);
        }
    }
}

void StateSettings:: Update(float dt) {

    this -> _data -> window.clear();
    this -> _data -> window.draw( this -> _background);
    this -> _data -> window.draw( this -> _plusButton);
    this -> _data -> window.draw( this -> _minusButton);
    
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
    
    this -> _data -> window.draw( this -> _numberDisplay);
    this -> _data -> window.draw( this -> _homeButton);
    this -> _data -> window.display();
}

void StateSettings:: Draw(float dt) {

    this -> _data -> window.clear();
    this -> _data -> window.draw( this -> _background);
    this -> _data -> window.draw( this -> _plusButton);
    this -> _data -> window.draw( this -> _minusButton);
    this -> _data -> window.draw( this -> _numberDisplay);
    this -> _data -> window.draw( this -> _homeButton);
    this -> _data -> window.display();
}
