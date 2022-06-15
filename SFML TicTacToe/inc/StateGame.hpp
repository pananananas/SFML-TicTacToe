#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "StateMainMenu.hpp"
#include "Algorithm.hpp"
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
    void    CheckIfGameWon(int turn);
    void    Check3PiecesForMatch(int x1, int y1, int x2,
                                 int y2, int x3, int y3,
                                 int pieceToCheck);
    void    Check4PiecesForMatch(int x1, int y1, int x2, int y2,
                                 int x3, int y3, int x4, int y4,
                                 int pieceToCheck);
    void    Check5PiecesForMatch(int x1, int y1, int x2, int y2, int x3,
                                 int y3, int x4, int y4, int x5, int y5,
                                 int pieceToCheck);
    void    Check6PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3,
                                 int x4, int y4, int x5, int y5, int x6, int y6,
                                 int pieceToCheck);
    Algorithm   AI;
public:
    
    
    StateGame(GameDataRef data, int size);
    void Init();
    void HandleInput();
    void Update(float dt);
    void Draw(float dt);
};
