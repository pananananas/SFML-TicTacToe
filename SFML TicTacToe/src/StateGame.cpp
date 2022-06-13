#include "StateGame.hpp"
#include "StatePause.hpp"
#include "Definitions.hpp"
#include <iostream>
#include <sstream>

StateGame:: StateGame(GameDataRef data): _data( data ) { }

void StateGame:: Init() {

    gameState = STATE_PLAYING;
    turn      = PLAYER_PIECE;

    this -> _data -> assets.LoadTexture( "Game Background", PAUSE_BACKGROUND_FILEPATH);
    this -> _data -> assets.LoadTexture( "Pause Button", PAUSE_BUTTON );

    _background.setTexture(  this -> _data -> assets.GetTexture("Game Background") );
    _pauseButton.setTexture( this -> _data -> assets.GetTexture("Pause Button") );

    _pauseButton.setPosition( this -> _data -> window.getSize().x / 2
                           - _pauseButton.getLocalBounds().width  / 2,
                             _pauseButton.getPosition().y );

}

void StateGame:: HandleInput() {

    sf::Event event;

    while (this -> _data -> window.pollEvent(event)) {

        if (sf::Event::Closed == event.type)
            this -> _data -> window.close();

        if ( this -> _data -> input.IsSpriteClicked(this -> _pauseButton, sf::Mouse::Left, this -> _data -> window) )
            this -> _data -> machine.AddState(StateRef( new StatePause(_data) ), false); // Pause
                                                                              // false cuz we dont want to replace current state, we only want to pause this one
    }
}

void StateGame:: Update(float dt) {

}

void StateGame:: Draw(float dt) {

    this -> _data -> window.clear();
    this -> _data -> window.draw( this -> _background);
    this -> _data -> window.draw( this -> _pauseButton);
    this -> _data -> window.display();
}


