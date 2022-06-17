#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "StateMainMenu.hpp"

class StateGame: public State {
    
    GameDataRef _data;
    sf::Sprite  _title_X_Win;
    sf::Sprite  _title_O_Win;
    sf::Sprite  _title_Draw;
    sf::Sprite  _background;
    sf::Sprite  _pauseButton;
    sf::Sprite  _replayButton;
    sf::Sprite  _grid;
    int         _size;
    int          turn;
    int          gameState;
    int          gridArray[6][6];
    sf::Sprite   gridPieces[6][6];
    void    InitGridPieces();
    void    PlacePiece();
    bool    CheckIfGameWon(int turn);
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
    
    int checkWinner();
    bool isGridFull();
    void placeTrun(int col, int row);
    void PlaceAIPiece();
    void PlaceAIPiece(int tmpGridArray[6][6], sf::Sprite gridPieces[6][6]);
    int  MiniMax(int tmpgridArray[6][6], int depth , bool max);
    
public:
    
    
    StateGame(GameDataRef data, int size);
    void Init();
    void HandleInput();
    void Update(float dt);
    void Draw(float dt);
};
