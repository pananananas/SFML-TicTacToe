#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"


class StateSplash : public State {
    GameDataRef _data;
    sf::Clock   _clock;
    sf::Sprite  _background;
    
public:
    
    StateSplash(GameDataRef data);
    
    void Init();
    void HandleInput();
    void Update(float dt);
    void Draw(float dt);
    
};
