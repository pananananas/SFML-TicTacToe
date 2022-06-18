#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "StateMainMenu.hpp"


class StateSettings: public State {
    
    GameDataRef _data;
    sf::Sprite  _title;
    sf::Sprite  _titleGS;
    sf::Sprite  _background;
    sf::Sprite  _plusButton;
    sf::Sprite  _minusButton;
    sf::Sprite  _plusButton2;
    sf::Sprite  _minusButton2;
    sf::Sprite  _homeButton;
    sf::Sprite  _numberDisplay;
    sf::Sprite  _numberDisplay2;
    sf::Sprite  _AIPiece;
    sf::Sprite  _PPiece;
    sf::Sprite  _XPiece;
    sf::Sprite  _OPiece;
    
    
public:
    
    int _size;
    bool _isPlayerX;
    int  _winSize;
    bool _VSAI;
    StateSettings(GameDataRef data, int size, int winSize, bool isPlayerX, bool VSAI);
    void Init();
    void HandleInput();
    void Update(float dt);
    void Draw(float dt);
};
