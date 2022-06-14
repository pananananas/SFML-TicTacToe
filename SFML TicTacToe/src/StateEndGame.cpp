#include "StateEndGame.hpp"
#include "StatePause.hpp"
#include "StateMainMenu.hpp"
#include "Definitions.hpp"
#include <iostream>
#include <sstream>

StateEndGame:: StateEndGame(GameDataRef data, int size): _data( data ) { _size = size; }

void StateEndGame:: Init() {

    
    this -> _data -> assets.LoadTexture("Retry Button",    RETRY_BUTTON);
    this -> _data -> assets.LoadTexture("Home Button",      HOME_BUTTON);
    this -> _data -> assets.LoadTexture("Grid",      HOME_BUTTON);
    
    
    this -> _retryButton.setTexture( this -> _data -> assets.GetTexture("Retry Button"));
    this -> _homeButton.setTexture(   this -> _data -> assets.GetTexture("Home Button"));

    this -> _retryButton.setPosition( this -> _data -> window.getSize().x / 2
                                     - this -> _retryButton.getLocalBounds().width / 2 ,
                                       this -> _data -> window.getSize().y / 5 * 2
                                     - this -> _retryButton.getLocalBounds().height / 3);

    this -> _homeButton.setPosition( this -> _data -> window.getSize().x / 2
                                   - this -> _homeButton.getLocalBounds().width / 2 ,
                                     this -> _data -> window.getSize().y / 5 * 3
                                   - this -> _homeButton.getLocalBounds().height / 2);
}


void StateEndGame:: HandleInput() {

    sf::Event event;

    while (this -> _data -> window.pollEvent(event)) {

        if (sf::Event::Closed == event.type)
            this -> _data -> window.close();

        if ( this -> _data -> input.IsSpriteClicked(this -> _retryButton, sf::Mouse::Left, this -> _data -> window) ){
            
            this -> _data -> machine.AddState(StateRef(new StateGame(_data, _size)), true);
            
            
        }
        if ( this -> _data -> input.IsSpriteClicked(this -> _homeButton, sf::Mouse::Left, this -> _data -> window) ) {
            
            this -> _data -> machine.AddState(StateRef(new StateMainMenu(_data, _size)), true);
        }
    }
}

void StateEndGame:: Update(float dt) {

}

void StateEndGame:: Draw(float dt) {

    this -> _data -> window.clear( sf::Color::Red);
    
    this -> _data -> window.draw( this -> _retryButton);
    this -> _data -> window.draw( this -> _homeButton);
    
    this -> _data -> window.display();
}

