#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"


class StateMainMenu: public State {
    
    GameDataRef _data;
    sf::Sprite  _background;
    sf::Sprite  _playButton;
    sf::Sprite  _playButtonOuter;
    sf::Sprite  _title;
    
public:
    
    StateMainMenu(GameDataRef data);
    void Init();
    void HandleInput();
    void Update(float dt);
    void Draw(float dt);
};
