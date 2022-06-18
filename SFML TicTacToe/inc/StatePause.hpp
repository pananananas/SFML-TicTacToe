#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "StateGame.hpp"


class StatePause: public State {
    
    GameDataRef _data;
    sf::Sprite  _background;
    sf::Sprite  _resumeButton;
    sf::Sprite  _homeButton;
    sf::Sprite  _title;
    
public:
    
    int  _size;
    bool _isPlayerX;
    int  _winSize;
    bool _VSAI;
    StatePause(GameDataRef data, int size, int winSize, bool isPlayerX, bool VSAI);
    void Init();
    void HandleInput();
    void Update(float dt);
    void Draw(float dt);
};
