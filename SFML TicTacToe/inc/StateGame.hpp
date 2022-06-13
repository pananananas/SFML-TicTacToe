#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "StateMainMenu.hpp"


class StateGame: public State {
    
    GameDataRef _data;
    sf::Sprite  _background;
    sf::Sprite  _pauseButton;
    sf::Sprite  _grid;
    int          turn;
    int          gameState;
    sf::Sprite   gridPieces[3][3];
    void InitGridPiece();
    
public:
    
    int  _size;
    StateGame(GameDataRef data, int size);
    void Init();
    void HandleInput();
    void Update(float dt);
    void Draw(float dt);
};
