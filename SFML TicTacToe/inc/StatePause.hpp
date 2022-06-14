#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "StateGame.hpp"


class StatePause: public State {
    
    GameDataRef _data;
    sf::Sprite  _background;
    sf::Sprite  _resumeButton;
    sf::Sprite  _homeButton;
    
public:
    
    int _size;
    
    StatePause(GameDataRef data, int size);
    void Init();
    void HandleInput();
    void Update(float dt);
    void Draw(float dt);
};