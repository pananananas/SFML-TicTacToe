#include "StateSplash.hpp"
#include "StateMainMenu.hpp"
#include "Definitions.hpp"
#include <iostream>
#include <sstream>


StateSplash:: StateSplash(GameDataRef data) : _data(data) { }

void StateSplash::Init() {
    
    this -> _data -> assets.LoadTexture("Splash State Background", SPLASH_SCENE_BACKGROUND_FILEPATH);
    
    _background.setTexture(this -> _data -> assets.GetTexture("Splash State Background"));
}

void StateSplash::HandleInput() {
    
    sf::Event event;
    
    while (this -> _data -> window.pollEvent(event))
        if (sf::Event::Closed == event.type)
            this -> _data -> window.close();
}

void StateSplash::Update(float dt) {
    
    if (this -> _clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME) {
        
        // Switch to the Main Menu
        this -> _data -> machine.AddState(StateRef(new StateMainMenu(_data, 3) ), true);
    }
}

void StateSplash::Draw(float dt) {
    
    this -> _data -> window.clear(sf::Color::Red);
    this -> _data -> window.draw(this ->_background);
    this -> _data -> window.display();
}
