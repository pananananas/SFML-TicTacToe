#include "StatePause.hpp"
#include "StateMainMenu.hpp"
#include "Definitions.hpp"
#include <iostream>
#include <sstream>

StatePause:: StatePause(GameDataRef data, int size): _data( data ) { _size = size; }

void StatePause:: Init() {

    this -> _data -> assets.LoadTexture("Pause Background", PAUSE_BACKGROUND_FILEPATH);
    this -> _data -> assets.LoadTexture("Resume Button",    RESUME_BUTTON);
    this -> _data -> assets.LoadTexture("Home Button",      HOME_BUTTON);

    this -> _background.setTexture(   this -> _data -> assets.GetTexture("Pause Background"));
    this -> _resumeButton.setTexture( this -> _data -> assets.GetTexture("Resume Button"));
    this -> _homeButton.setTexture(   this -> _data -> assets.GetTexture("Home Button"));

    this -> _resumeButton.setPosition( this -> _data -> window.getSize().x / 2
                                     - this -> _resumeButton.getLocalBounds().width / 2 ,
                                       this -> _data -> window.getSize().y / 5 * 2
                                     - this -> _resumeButton.getLocalBounds().height / 3);

    this -> _homeButton.setPosition( this -> _data -> window.getSize().x / 2
                                   - this -> _homeButton.getLocalBounds().width / 2 ,
                                     this -> _data -> window.getSize().y / 5 * 3
                                   - this -> _homeButton.getLocalBounds().height / 2);
}


void StatePause:: HandleInput() {

    sf::Event event;

    while (this -> _data -> window.pollEvent(event)) {

        if (sf::Event::Closed == event.type)
            this -> _data -> window.close();

        if ( this -> _data -> input.IsSpriteClicked(this -> _resumeButton, sf::Mouse::Left, this -> _data -> window) )
            this -> _data -> machine.RemoveState();

        if ( this -> _data -> input.IsSpriteClicked(this -> _homeButton, sf::Mouse::Left, this -> _data -> window) ) {
            this -> _data -> machine.RemoveState();
            this -> _data -> machine.AddState(StateRef(new StateMainMenu(_data, _size)), true);
        }
    }
}

void StatePause:: Update(float dt) {

}

void StatePause:: Draw(float dt) {

    this -> _data -> window.clear();
    this -> _data -> window.draw( this -> _background);
    this -> _data -> window.draw( this -> _resumeButton);
    this -> _data -> window.draw( this -> _homeButton);
    this -> _data -> window.display();
}