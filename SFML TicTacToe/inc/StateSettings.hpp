#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "StateMainMenu.hpp"


class StateSettings: public State {
    
    GameDataRef _data;
    sf::Sprite  _background;
    sf::Sprite  _plusButton;
    sf::Sprite  _minusButton;
    sf::Sprite  _homeButton;
    sf::Sprite  _numberDisplay;
    
public:
    
    int _size;
    
    StateSettings(GameDataRef data, int size);
    void Init();
    void HandleInput();
    void Update(float dt);
    void Draw(float dt);
};
