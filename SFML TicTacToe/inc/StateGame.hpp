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
    void    InitGridPieces();
    void    PlacePiece();
    void    CheckIfPlayerWon(int turn);
    void    Check3PiecesForMatch(int x1, int y1,
                                 int x2, int y2,
                                 int x3, int y3,
                                 int pieceToCheck);
    
public:
    
    
    StateGame(GameDataRef data, int size);
    void Init();
    void HandleInput();
    void Update(float dt);
    void Draw(float dt);
};
