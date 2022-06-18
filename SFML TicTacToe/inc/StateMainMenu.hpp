#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"


class StateMainMenu: public State {
    
    GameDataRef _data;
    sf::Sprite  _background;
    sf::Sprite  _playButton;
    sf::Sprite  _playButtonOuter;
    sf::Sprite  _settingsButton;
    sf::Sprite  _title;
    
public:
    
    int _size;
    bool _isPlayerX;
    int  _winSize;
    bool _VSAI;
    StateMainMenu(GameDataRef data, int size, int winSize, bool isPlayerX, bool VSAI);
    void Init();
    void HandleInput();
    void Update(float dt);
    void Draw(float dt);
};
