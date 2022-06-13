#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "StateMainMenu.hpp"


class StateGame: public State {
    
    GameDataRef _data;
    sf::Sprite  _background;
    sf::Sprite  _pauseButton;
    int          turn;
    int          gameState;
    
public:
    
    StateGame(GameDataRef data);
    void Init();
    void HandleInput();
    void Update(float dt);
    void Draw(float dt);
};
