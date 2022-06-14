#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "StateMainMenu.hpp"
static int _size;

class StateGame: public State {
    
    GameDataRef _data;
    sf::Sprite  _background;
    sf::Sprite  _pauseButton;
    sf::Sprite  _grid;
    int          turn;
    int          gameState;
    int         _size;
    int          gridArray[6][6];
    sf::Sprite   gridPieces[6][6];
    void InitGridPieces();
    
public:
    
    
    StateGame(GameDataRef data, int size);
    void Init();
    void HandleInput();
    void Update(float dt);
    void Draw(float dt);
};
