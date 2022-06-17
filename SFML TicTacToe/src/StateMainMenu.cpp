#include "StateMainMenu.hpp"
#include "Definitions.hpp"
#include "StateGame.hpp"
#include "StateSettings.hpp"
#include <iostream>
#include <sstream>

StateMainMenu:: StateMainMenu(GameDataRef data, int size): _data( data ) { _size = size; }

void StateMainMenu:: Init() {
    
    // Getting all elements from IU folder and adding it to Sptires
    this -> _data -> assets.LoadTexture("Background", MAIN_MENU_BACKGROUND_FILEPATH);
    this -> _data -> assets.LoadTexture("Play Button", MAIN_MENU_PLAY_BUTTON);
    this -> _data -> assets.LoadTexture("Play Button Outer", MAIN_MENU_PLAY_BUTTON_OUTER);
    this -> _data -> assets.LoadTexture("Game Title", MAIN_MENU_TITLE_FILEPATH);
    this -> _data -> assets.LoadTexture("Settings Button", MAIN_MENU_SETTINGS_BUTTON);

    this -> _background.setTexture(     this -> _data -> assets.GetTexture("Background"));
    this -> _playButton.setTexture(     this -> _data -> assets.GetTexture("Play Button"));
    this -> _playButtonOuter.setTexture(this -> _data -> assets.GetTexture("Play Button Outer"));
    this -> _title.setTexture(          this -> _data -> assets.GetTexture("Game Title"));
    this -> _settingsButton.setTexture( this -> _data -> assets.GetTexture("Settings Button"));
    
    
    // Positioning UI elements
    this -> _playButton.setPosition((SCREEN_WIDTH/ 2)
                                  - (this -> _playButton.getGlobalBounds().width / 2),
                                    (SCREEN_HEIGHT/ 2)
                                  - (this -> _playButton.getGlobalBounds().height / 2));
    this -> _playButtonOuter.setPosition((SCREEN_WIDTH/ 2)
                                  - (this -> _playButtonOuter.getGlobalBounds().width / 2),
                                    (SCREEN_HEIGHT/ 2)
                                  - (this -> _playButtonOuter.getGlobalBounds().height / 2));
    this -> _title.setPosition((SCREEN_WIDTH/ 2) - (this -> _title.getGlobalBounds().width / 2), 0);
    this -> _settingsButton.setPosition((SCREEN_WIDTH/2)
                                  - (this -> _settingsButton.getGlobalBounds().width / 2),
                                    (SCREEN_HEIGHT)
                                  - (this -> _settingsButton.getGlobalBounds().height * 1.1));
}

void StateMainMenu:: HandleInput() {

    sf::Event event;

    while (this -> _data -> window.pollEvent(event)) {

        if (sf::Event::Closed == event.type)
            this -> _data -> window.close();

        if ( this -> _data -> input.IsSpriteClicked(this -> _playButton, sf::Mouse::Left, this -> _data -> window) ) {

            // Go to Game Screen
            this -> _data -> machine.AddState(StateRef( new StateGame(_data, _size) ), true);
        }
        if ( this -> _data -> input.IsSpriteClicked(this -> _settingsButton, sf::Mouse::Left, this -> _data -> window) ) {
            
            // Go to Settings
            this -> _data -> machine.AddState(StateRef( new StateSettings(_data, _size) ), true);
        }
    }
}

void StateMainMenu:: Update(float dt) {

}

void StateMainMenu:: Draw(float dt) {

    this -> _data -> window.clear();

    this -> _data -> window.draw( this -> _background);
    this -> _data -> window.draw( this -> _title);
//    this -> _data -> window.draw( this -> _playButtonOuter);
    this -> _data -> window.draw( this -> _playButton);
    this -> _data -> window.draw( this -> _settingsButton);
    
    this -> _data -> window.display();
}
