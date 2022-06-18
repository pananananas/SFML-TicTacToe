#include "StatePause.hpp"
#include "StateMainMenu.hpp"
#include "Definitions.hpp"
#include <iostream>
#include <sstream>

StatePause:: StatePause(GameDataRef data, int size, int winSize, bool isPlayerX, bool VSAI): _data( data ) {
    _winSize  = winSize;
    _VSAI     = VSAI;
    _size = size; _isPlayerX = isPlayerX; }

void StatePause:: Init() {

    this -> _data -> assets.LoadTexture("Pause Background", PAUSE_BACKGROUND_FILEPATH);
    this -> _data -> assets.LoadTexture("Resume Button",    RESUME_BUTTON);
    this -> _data -> assets.LoadTexture("Home Button",      HOME_BUTTON);
    this -> _data -> assets.LoadTexture("P Title",          PAUSE_TITLE_FILEPATH);
    this -> _data -> assets.LoadTexture("Replay Button", RETRY_BUTTON );

    this -> _retryButton.setTexture( this -> _data -> assets.GetTexture("Replay Button") );
    this -> _background.setTexture(   this -> _data -> assets.GetTexture("Pause Background"));
    this -> _resumeButton.setTexture( this -> _data -> assets.GetTexture("Resume Button"));
    this -> _homeButton.setTexture(   this -> _data -> assets.GetTexture("Home Button"));
    this -> _title.setTexture(        this -> _data -> assets.GetTexture("P Title"));

    this -> _resumeButton.setPosition( this -> _data -> window.getSize().x / 2
                                     - this -> _resumeButton.getLocalBounds().width / 2 ,
                                       this -> _data -> window.getSize().y / 5 * 2
                                     - this -> _resumeButton.getLocalBounds().height / 3);

    this -> _homeButton.setPosition( this -> _data -> window.getSize().x / 2
                                   - this -> _homeButton.getLocalBounds().width / 2 ,
                                     this -> _data -> window.getSize().y / 5 * 4
                                   - this -> _homeButton.getLocalBounds().height / 2);
    
    this -> _retryButton.setPosition( this -> _data -> window.getSize().x / 2
                                   - this -> _retryButton.getLocalBounds().width / 2 ,
                                     this -> _data -> window.getSize().y / 5 * 3
                                   - this -> _retryButton.getLocalBounds().height / 2);
    
    this -> _title.setPosition((SCREEN_WIDTH/ 2) - (this -> _title.getGlobalBounds().width / 2), 0);
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
            this -> _data -> machine.AddState(StateRef(new StateMainMenu(_data, _size,_winSize, _isPlayerX, _VSAI)), true);
        }
        if ( this -> _data -> input.IsSpriteClicked(this -> _retryButton, sf::Mouse::Left, this -> _data -> window) )
            this -> _data -> machine.AddState(StateRef( new StateGame(_data, _size,_winSize, _isPlayerX, _VSAI) ), true);  // End Game
    }
}

void StatePause:: Update(float dt) {

}

void StatePause:: Draw(float dt) {

    this -> _data -> window.clear();
    this -> _data -> window.draw( this -> _background);
    this -> _data -> window.draw( this -> _resumeButton);
    this -> _data -> window.draw( this -> _homeButton);
    this -> _data -> window.draw( this -> _title);
    this -> _data -> window.draw( this -> _retryButton);
    this -> _data -> window.display();
}
